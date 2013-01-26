// RomiboSuperEngage.ino : A two minute demo to engage children with romibo.
// Copyright (c) 2012 John Frens & Laxman Dhulipala
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
#include <RomiboSound.h>  
#include <RomiboRobot.h>
#include "ConsoleOutput.h"
#include <RomiboAction.h>

/****************************************************************/
// Declare the default parameter table object.
#include <Parameters.h>
Parameters parameters( NULL, 0 );

// Define a polled serial output stream.
ConsoleOutput Console;  

/****************************************************************/
#define NUM_HAPPY_SOUNDS 7
static const char *happy_sounds[] = {
  "HAPPY1",
  "HAPPY2",
  "HAPPY3",
  "BECKON3",
  "BEKON4",
  "BECKON6",
  "QUEST2"
};

const char * randomHappySound ()
{
  return happy_sounds [random(NUM_HAPPY_SOUNDS)];
}

void playRandomHappySound ()
{
  Romibo.waitForSoundToFinish ();
  Romibo.playSoundNamed ( randomHappySound() );
}

void blinkmaybe ()
{
  if (random (1000) > 996) {
    Romibo.delay (100);
    Romibo.setNeutralHeadPosition ();
    Romibo.setEyelid (10);
    Romibo.delay (200);
    Romibo.setEyelid (90);
  }
}

void blinksometimes ()
{
  if (random (1000) > 900) {
    Romibo.delay (100);
    Romibo.setNeutralHeadPosition ();
    Romibo.setEyelid (10);
    Romibo.delay (200);
    Romibo.setEyelid (90);
  }  
}

void waitforpets () {
  ElapsedTimer timewaiting = ElapsedTimer();
  timewaiting.reset();
  int timetowait = 60; //we will wait 60 seconds to be pet.
  while (timewaiting.elapsedSeconds () < timetowait) {
    Romibo.delay (10);
    blinkmaybe ();
    if (!(0 == Romibo.touchSwitches())) {
      playRandomHappySound();
      RomiboAct.bob();
      Romibo.waitForSoundToFinish();
      RomiboAct.blink();
      if (timetowait > 20) timetowait = 20;
    }
  }  
}

void hugsequence () {
  RomiboAct.blink();
  RomiboAct.setAntenna (ROA_GREEN);
  Romibo.setEyelid (100);
  Romibo.playSoundNamed ("BECKON1");
  RomiboAct.approach (300);
  
  // Hug sequence
  int time = 2000; // twenty seconds
  int minrange = 0;
  int maxrange = 120;
  RomiboAct.waitForTargetRange (time, minrange, maxrange);
  Romibo.playSoundNamed ("SAD1");
  RomiboAct.setAntenna (ROA_RED);
  Romibo.setHeadPosition (0, 100);
  Romibo.delay (4000);
  Romibo.setNeutralHeadPosition();  
}

void dance() {
  RomiboAct.setAntenna (ROA_BLUE);
  for (int i = 0; i < 5; i++) {
    Romibo.setHeadPosition (0, 100);
    RomiboAct.driveForwardTimed (50);
    Romibo.delay (200);
    blinksometimes ();
    Romibo.setHeadPosition (100, 0);
    RomiboAct.driveBackwardTimed (50);
    Romibo.delay (200);
    blinksometimes ();
  }
  RomiboAct.turnRight (50);
  blinksometimes ();
  RomiboAct.turnLeft (50);
  blinksometimes ();
  RomiboAct.turnRight (100);
  blinksometimes ();
  Romibo.playSoundNamed ("HAPPY3"); 
}

void setup(void) 
{
  Serial.begin(57600);
  Serial1.begin(9600);

  // Initialize the Romibo system and attach it to the hardware.
  Romibo.begin();

  // Add the low-level variables to the user interface for debugging.
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());

  Serial.println("INITIALIZED");
  
  Serial.println("Begin Step 1");
  
  // Step one, wake up
  // Human actor should introduce the child to the robot. "This is Romibo, isn't he cool!"
  Romibo.setEyelid (75);
  Romibo.delay (300);
  RomiboAct.blink();
  Romibo.playSoundNamed ("HAPPY1");
  RomiboAct.setAntenna (ROA_YELLOW);
  Romibo.delay (500);

  Serial.println("Begin Step 2");
  
  // Step two, petting
  // Human actor should ask the child to pet the robot. "Romibo loves being pet. Try petting him!"
  
  waitforpets();
  
  Serial.println("Begin Step 3");

  // Step 3, Romibo becomes more excited
  // Human actor should tell the child to hug Romibo. "Romibo likes you! Give him a Hug!"
  //hugsequence();
  
  //waitforpets();
  
  Serial.println("Begin Step 4");
  
  RomiboAct.driveBackwardTimed (100);
  // Step 4, Dance!
  //dance ();
  //YAY, done.
  
  Serial.println("RomiboSuperEngage Complete!");
  
}

void loop( void )
{
  wander ();
  if (buttonPressed () || wifiCommandRecieved ()) {
    stayinplace (20000);
  } else {
    stayinplace (1000);
  }
}
