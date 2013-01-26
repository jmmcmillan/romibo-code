// romibotest.ino : A simple user program that plays a simple tag game
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
// This sketch is intended to be a game of tag played by Romibo:
// Romibo will wander until it detects motion.
// Upon decting motion, Romibo will turn 180 degrees and 'run away'.
// While running away, Romibo will avoid walls.
// If pet while running away, romibo will stop and respond to being pet.

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
//SoundLibrary functions
extern const char *random_play_sound(void);
extern const char *random_happy_sound(void);
extern const char *random_angry_sound(void);
extern const char *random_beckon_sound(void);
extern const char *random_sad_sound(void);

extern const char *random_question_sound(void);
extern const char *random_greeting_sound(void);



#define COLOR_RED   255,0,0
#define COLOR_GREEN 0,255,0
#define COLOR_BLUE  0,0,255

#define EYES_OPEN (95)
#define EYES_HALF (60)
#define EYES_CLOSED (5)

#define RUN_SPEED (100)

/* "wait state" functions */
void initiateWaitState ()
{
  Romibo.setNeutralHeadPosition ();
  Romibo.setAntennaColor ( COLOR_RED );
  Romibo.playSoundNamed ( "HAPPY2" );
  Romibo.setEyelid ( EYES_HALF );
}
// makes a beckoning sound
void beckon ()
{
  Romibo.waitForSoundToFinish ();
  Romibo.playSoundNamed ( random_beckon_sound() );
}

// drives until a wall is detected
void driveToWall (int drivetime)
{
  int beginningprox = Romibo.obstacleProximity ();
  
  if (beginningprox == ROMIBO_CLOSE) {
    return;
  }
  
  Romibo.driveForward (RUN_SPEED - 20);
  ElapsedTimer drivetimer = ElapsedTimer ();
  drivetimer.reset ();
  while ( (drivetimer.elapsedMilliseconds () < drivetime)
       && (Romibo.obstacleProximity() == beginningprox) ) {
    if (Romibo.touchSwitches() != 0) {
      Romibo.stop();
      return;
    }

  }
  Romibo.stop();
  return;
}
// Turns toward approximate direction of most light
void turnTowardLight (int turntime)
{
  int startLightAngle = Romibo.frontLightHeading ();
  
  if (startLightAngle < 20 && startLightAngle > -20) {
    return;
  }
  
  int turnDirection = 1;
  
  if (startLightAngle < 0) {
    turnDirection = -1;
  }

  ElapsedTimer drivetimer = ElapsedTimer ();
  drivetimer.reset ();
  Romibo.spinInPlace (RUN_SPEED * turnDirection);
  while ( (drivetimer.elapsedMilliseconds () < turntime)
       && (Romibo.frontLightHeading () > 20 || Romibo.frontLightHeading () < -20) ) {
    if (Romibo.touchSwitches() != 0) {
      Romibo.stop();
      return;
    }
  }
  Romibo.stop();
  return;
  
}

// A wander function that turns toward light and drives.
void wander ()
{
  Romibo.waitForSoundToFinish ();
  turnTowardLight (4000);
  driveToWall (3000);
  
}

void reactToTouch ()
{
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed ( "HAPPY3" );
  bobHappily();
  bobHappily();
  delay (2000);
  Romibo.playSoundNamed ("QUEST2");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed ("HAPPY3");
}

void waitState ()
{
  int beckons = 1;
  ElapsedTimer timewaiting = ElapsedTimer();
  timewaiting.reset();
  while (true) {
    // beckon every two seconds
    if (timewaiting.elapsedSeconds() > 6 * beckons ) {
      beckons ++;
      beckon ();
      if (beckons > 5) {
        Romibo.setEyelid (EYES_CLOSED);
      }
    }
    // TODO: detect motion rather than obstacle proximity
    if (Romibo.obstacleProximity() == 0) {
      // escapes the loop, thus moving to the run state
      return;
    }
    if (Romibo.touchSwitches() != 0) {
      reactToTouch ();
    }

  }
  
}

/* "run state" functions */
void initiateRunState ()
{
  Romibo.tiltHeadForward ();
  Romibo.setAntennaColor ( COLOR_GREEN );
  Romibo.playSoundNamed ( "HAPPY1" );
  Romibo.setEyelid ( EYES_OPEN );
}
// turns approximately 180 degrees
void turnAround () {
  Romibo.spinInPlace (RUN_SPEED);
  Romibo.delay (1500);
  Romibo.stop ();
}
void turnRandomly () {
  //not so random right now...
  Romibo.playSoundNamed ( "HAPPY1" );
  Romibo.spinInPlace (-1 * RUN_SPEED);
  Romibo.delay (1000 + random(500));
  Romibo.stop ();
  Romibo.delay (400);
}
void runState () {
  turnAround ();
  Romibo.driveForward (RUN_SPEED);
  int turns = 0;
  while (true) {
    
    Romibo.poll();
    
    // TODO: better obstacle avoidance
    if (Romibo.obstacleProximity () < 1) {
      turnRandomly ();
      Romibo.driveForward (RUN_SPEED);
      turns ++;
      if (turns > 8) {
        return;
      }
    }
    
    // when caught, we return, thus going to the caught state
    if (Romibo.touchSwitches() != 0) {
      return;
    }
  }
  
}

/* "caught state" functions */
void initiateCaughtState ()
{
  Romibo.stop ();
  Romibo.setHeadPosition (90,90);
  Romibo.setAntennaColor ( COLOR_BLUE );
  Romibo.setEyelid ( EYES_CLOSED );
}
void bobHappily ()
{
  Romibo.delay (300);
  Romibo.setHeadPosition (0,0);
  Romibo.delay (400);
  Romibo.setHeadPosition (95,95);
}
void caughtState ()
{
  Romibo.playSoundNamed ( "HAPPY3" );
  bobHappily();
  bobHappily();
  delay (2000);
  Romibo.playSoundNamed ("QUEST2");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed ("HAPPY3");
  delay (3000);
  return;
}

void setup(void) 
{
  // Not sure what this is for...
  Serial.begin(57600);
  Serial1.begin(9600);

  // Initialize the Romibo system and attach it to the hardware.
  Romibo.begin();

  // Add the low-level variables to the user interface for debugging.
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());
  
  Romibo.setAntennaColor (255,255,255);
  Romibo.delay (500);
  //Romibo.playSoundNamed ("AWESOME");
  //Romibo.waitForSoundToFinish ();
}

  // Loops indefinitely. Simply calls each state in order
void loop( void )
{
  initiateWaitState();
  waitState();
  
  initiateRunState();
  runState();
  
  initiateCaughtState();
  caughtState();
}
