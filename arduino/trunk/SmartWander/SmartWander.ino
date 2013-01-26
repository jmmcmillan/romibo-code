// SmartWander.ino : An implementation of "Smart Wander" behavior, where
//   Romibo wanders randomly while avoiding walls and moving toward light.
// Copyright (c) 2012 John Frens
// ##BEGIN_LICENSE##
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this file; if not, write to the Free Software Foundation,
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
// ##END_LICENSE##
/****************************************************************/
/****************************************************************/

#include <RomiboSound.h>  
#include <RomiboRobot.h>
#include <ConsoleOutput.h>
/****************************************************************/
// Declare the default parameter table object.
#include <Parameters.h>
Parameters parameters( NULL, 0 );

// Define a polled serial output stream.
ConsoleOutput Console;  

/****************************************************************/

#define DRIVESPEED 75
#define TURNSPEED 85
#define SLOWSPEED 65

#define THRESH_FAR 350
#define THRESH_CLOSE 200
#define THRESH_TOO_CLOSE 120

#define PROX_FAR 2
#define PROX_MEDIUM 1
#define PROX_CLOSE 0
#define PROX_TOO_CLOSE -1

#define NUM_HAPPY_SOUNDS 7
#define NUM_EXPLORING_SOUNDS 4
static const char *happy_sounds[] = {
  "HAPPY1",
  "HAPPY2",
  "HAPPY3",
  "BECKON3",
  "BEKON4",
  "BECKON6",
  "QUEST2"
};

static const char *exploring_sounds[] = {
  "HAPPY3",
  "BECKON1",
  "BECKON6",
  "QUEST1"
};

//Runs once at startup
void setup(void) 
{
  // Not sure what this is for...
  Serial.begin(57600);
  Serial1.begin(9600);

  // Initialize the Romibo system and attach it to the hardware.
  Romibo.begin();

  // Add the low-level variables to the user interface for debugging.
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());

  Romibo.setEyelid (90);
  Romibo.setNeutralHeadPosition ();
  Romibo.setAntennaColor (255, 255, 255);
  
  Romibo.delay(1000);

}

const char * randomHappySound ()
{
  return happy_sounds [random(NUM_HAPPY_SOUNDS)];
}

static int last_happy_sound = 0;
const char * nextHappySound ()
{
  return happy_sounds [(last_happy_sound++) % NUM_HAPPY_SOUNDS];
}

const char * randomExploringSound ()
{
  return exploring_sounds [random(NUM_EXPLORING_SOUNDS)]; 
}

void playRandomHappySound ()
{
  Romibo.waitForSoundToFinish ();
  Romibo.playSoundNamed ( randomHappySound() );
}

void playNextHappySound ()
{
  Romibo.waitForSoundToFinish ();
  Romibo.playSoundNamed ( nextHappySound () );
}

void playRandomExploringSound ()
{
  Romibo.waitForSoundToFinish ();
  Romibo.playSoundNamed (randomExploringSound() ); 
}

void bob ()
{
  Romibo.setHeadPosition (0,0);
  Romibo.delay (500);
  Romibo.setHeadPosition (100,100);
  Romibo.delay (400);
}

//blinks, sometimes.
void blink ()
{
  if (random (4) > 1) {
    Romibo.delay (100);
    Romibo.setNeutralHeadPosition ();
    Romibo.setEyelid (random(70));
    Romibo.delay (200 + random(150));
    Romibo.setEyelid (90);
  }
}

void blinkmaybe ()
{
  if (random (1000) > 996) {
    blink();
  }
}

// Bobs once and makes a random happy sound, or, after enough calls has a longer reaction
void happyReaction ()
{
  Romibo.setAntennaColor (50, 50, 255);
  playNextHappySound ();
  bob ();
  bob ();
  Romibo.setAntennaColor (255, 255, 255);
}

static int last_wifi_command_count = 0;
// Returns true if Romibo is recieving commands via wifi
bool wifiCommandRecieved ()
{
  return (get_command_count () > last_wifi_command_count);
}

void updateWifiCommandCount ()
{
  last_wifi_command_count = get_command_count ();
}

// Returns true if any of Romibo's buttons are pressed
bool buttonPressed ()
{
  return !(0 == Romibo.touchSwitches());
}

void reactToButtons ()
{
  if (buttonPressed ()) {
    Romibo.stop ();
    happyReaction ();
  }
  
}

// Begins turn in dir (-1 for left, 1 for right) direction while moving slightly backwards
void backTurn (int dir)
{
  if (dir >= 0) {
    Romibo.drive (TURNSPEED / 3, -1 * (TURNSPEED));
  }  else {
    Romibo.drive (-1 * (TURNSPEED), TURNSPEED / 3);
  }
}

// Begins turn in dir (-1 for left, 1 for right) direction while moving slightly forwards
void forTurn (int dir)
{
  if (dir >= 0) {
    Romibo.drive (TURNSPEED, TURNSPEED / 3);
  } else {
    Romibo.drive (TURNSPEED / 3, TURNSPEED);
  }
}

int proximity ()
{
  int range = Romibo.frontRangeDistance();
  if (range < THRESH_TOO_CLOSE) return PROX_TOO_CLOSE;
  if (range < THRESH_CLOSE) return PROX_CLOSE;
  if (range > THRESH_FAR) return PROX_FAR;
  return PROX_MEDIUM;
}

// returns true if proximity sensor detects a possible wall
bool wallDetected (int relativeprox)
{
  int currprox = proximity ();
  
  if ((currprox < relativeprox || currprox <= PROX_CLOSE) && (currprox < PROX_MEDIUM)) {
    return true;
  } else return false;  
}

// returns 1 if light is to the right and -1 if light is to the left. Returns 0 if lights are equal.
int estimateLightDirection () {
  int lLight = Romibo.leftFrontLightLevel ();
  int rLight = Romibo.rightFrontLightLevel ();
  
  if (lLight > rLight) {return -1;}
  if (lLight < rLight) {return 1;}
  
  return 0;
}

int estimateLightDifference () {
  int lLight = Romibo.leftFrontLightLevel ();
  int rLight = Romibo.rightFrontLightLevel ();
  
  return rLight - lLight;
}

int randomDirection () {
  return (random (3) - 1);
}

void avoidWall ()
{
  int turnattempts = 2;
  int turnDirection = randomDirection ();
  
  backTurn (turnDirection);
  
  for (int i = turnattempts; i > 0 && wallDetected (PROX_FAR); i--) {
    if (buttonPressed () || wifiCommandRecieved ()) {
      return;
    }
    // total delay of 800
    for (int j = 0; j < 800 / 20; j++) {
      Romibo.delay (20);
      if (buttonPressed () || wifiCommandRecieved ()) {
        return;
      }
    }
    forTurn (turnDirection);
  }
  
  Romibo.delay (100);
  
}

// Drives forward, stopping when a wall is detected or drivetime has elapsed
void smartDrive (int drivetime)
{
  int beginningprox = proximity ();
   
  Romibo.driveForward (DRIVESPEED);
  ElapsedTimer drivetimer = ElapsedTimer ();
  drivetimer.reset ();
  
  int wallCount = 0;
  int lightdiff = 0;
  
  while ( drivetimer.elapsedMilliseconds () < drivetime ) {
    Romibo.delay (20);
    if (wallDetected (beginningprox)) {
      avoidWall ();
      beginningprox = proximity ();
      lightdiff = estimateLightDifference ();
      //Romibo.driveForward (DRIVESPEED);
      Romibo.drive(DRIVESPEED + lightdiff, DRIVESPEED - lightdiff);
      drivetimer.reset ();
      drivetime -= 1000;
      wallCount++;
      if (wallCount > 4) {
        Romibo.playSoundNamed ("ANGRY1");
        break;
      }
    }
    if (buttonPressed () || wifiCommandRecieved ()) {
      return;
    }
  }
  
  Romibo.stop();
  return;
}

void turnTowardLight (int turntime)
{
  int startLightDirection = estimateLightDirection ();
  
  Romibo.setAntennaColor (0,0,0);
  if (startLightDirection == 0) {
    Romibo.setAntennaColor (100, 0, 100);
    Romibo.delay (200);
    return;
  }
  
  ElapsedTimer drivetimer = ElapsedTimer ();
  drivetimer.reset ();
  if (startLightDirection > 0) {
    //Romibo.drive (TURNSPEED / 3 * 2, -1 * (TURNSPEED));
    backTurn (1);
  }
  if (startLightDirection < 0) {
    //Romibo.drive (-1 * (TURNSPEED), TURNSPEED / 3 * 2);
    backTurn (-1);
  }
  Romibo.delay (200);
  while ( (drivetimer.elapsedMilliseconds () < turntime)
       && (estimateLightDirection () == startLightDirection) ) {
    Romibo.delay (10);
    if (buttonPressed ()) {
      Romibo.stop ();
      return;
    }
    if (wifiCommandRecieved ()) {
      return;
    }
  }
  Romibo.stop();
  Romibo.delay (100);
  return;
  
}

void wander ()
{
  turnTowardLight(1200);
  playRandomExploringSound ();
  Romibo.delay(200);
  smartDrive(5000);
}

// Moves forward until rangefinder reports 'distance', returns true if able to move to target range
bool approach (int distance)
{
  Romibo.waitForSoundToFinish ();
  Romibo.playSoundNamed ("QUEST2");
  
  Romibo.driveForward (SLOWSPEED);
  
  int time = 2500;
  ElapsedTimer approachtimer = ElapsedTimer ();
  approachtimer.reset ();
  while ( approachtimer.elapsedMilliseconds () < time) {
    if (Romibo.frontRangeDistance () < distance) {
      Romibo.stop ();
      Romibo.waitForSoundToFinish ();
      Romibo.playSoundNamed ("HAPPY1");
      return true;
    }
    Romibo.delay (20);
    if (buttonPressed ()) {
      Romibo.stop ();
      return true;
    }
    if (wifiCommandRecieved ()) {
      return false;
    }
  }
  Romibo.stop();
  return false;
}

// Moves backward until rangefinder reports 'distance', returns true if able to move to target range
bool keepdistance (int distance)
{
  Romibo.playSoundNamed ("SAD1");
  
  Romibo.driveBackward (SLOWSPEED);
  
  int time = 2500;
  ElapsedTimer approachtimer = ElapsedTimer ();
  approachtimer.reset ();
  while ( approachtimer.elapsedMilliseconds () < time) {
    if (Romibo.frontRangeDistance () > distance) {
      Romibo.stop ();
      return true;
    }
    Romibo.delay (20);
    if (buttonPressed ()) {
      Romibo.stop ();
      return false;
    }
    if (wifiCommandRecieved ()) {
      return true;
    }
  }
  
  return false;
}

void waitforwifi (int time)
{
  ElapsedTimer staytimer = ElapsedTimer ();
  staytimer.reset ();
  updateWifiCommandCount ();
  while ( staytimer.elapsedMilliseconds () < time ) {
    Romibo.delay (20);
    if (wifiCommandRecieved ()) {
      updateWifiCommandCount ();
      staytimer.reset ();
    }
    if (buttonPressed ()) return;

  }
}

// Stops and reacts to button presses until [time] milliseconds elapses without any interaction.
void stayinplace (int time)
{
  reactToButtons();
  ElapsedTimer staytimer = ElapsedTimer ();
  staytimer.reset ();
  int initprox = proximity ();
  int petcount = 1;
  
  while ( staytimer.elapsedMilliseconds () < time ) {
    Romibo.delay (20);
    blinkmaybe ();
    if (wifiCommandRecieved ()) {
      waitforwifi (5000);
    }
    int currprox = proximity ();
    if (currprox > initprox && currprox > PROX_MEDIUM) {
      approach (240);
      initprox = proximity ();
      staytimer.reset ();
      time -= 1000;
    } else if (currprox == PROX_TOO_CLOSE) {
      blink ();
      blink ();
      keepdistance (180);
      initprox = proximity (); 
      staytimer.reset ();
      time -= 1000;
    }
    
    if (buttonPressed ()) {
      petcount ++;
      initprox = proximity ();
      reactToButtons ();
      if (petcount == 2) {
        blink ();
      }
      if (petcount == 3) {
        Romibo.waitForSoundToFinish();
        Romibo.playSoundNamed ("QUEST2");
      }
      if (petcount == 5) {
        blink ();
        Romibo.setAntennaColor (0, 0, 0);
        delay (100);
        bob ();
        Romibo.setAntennaColor (255, 0, 0);
        delay (100);
        bob ();
        Romibo.setAntennaColor (0, 0, 0);
        bob ();
        Romibo.setAntennaColor (255, 0, 0);
      }
      staytimer.reset ();
    }
  } 
}

  // Loops indefinitely. Nothing here for now.
void loop( void )
{
  wander ();
  if (buttonPressed () || wifiCommandRecieved ()) {
    stayinplace (20000);
  } else {
    stayinplace (1000);
  }
}
