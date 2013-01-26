// RomiboActions.h : A simple control library for the Romibo robot,
// which focuses on simple behaviors.
// Copyright (c) 2011 John Frens

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

// This library is intended to provide convienient, simple behavior
// calls. All functions are implemented in the abstract, relying on
// calls to RomiboRobot.cpp rather than any direct calls to hardware methods.

// This library is intended to be sequential, simple, and user friendly. Note
// that some of the functions may be redundant with RomiboRobot.cpp

// RomiboActions.h is not included by any of the other libraries and therefore
// must be included by the user if applicable.

#ifndef __ROMIBOACTION_H_INCLUDED__
#define __ROMIBOACTION_H_INCLUDED__

enum romiboaction_color_t { ROA_RED, ROA_YELLOW,
	ROA_GREEN, ROA_AQUA, ROA_BLUE, ROA_VIOLET };
  
enum romiboaction_button_t {ROA_TOP, ROA_RIGHT,
	ROA_LEFT, ROA_BOTTOM, ROA_ANY};

class RomiboAction
{

public:

  void bob();

  void bobs (int numbobs);  

  void nod();
  
  void nods (int numnods);

  void blink();

  void blinks(int numblinks);

  void maintainDistance(int dist);

  void approach (int dist);

  //time in 1/100 sec
  void driveForwardTimed(int time);
  
  //time in 1/100 sec
  void driveBackwardTimed(int time);
  
  void turnRight (int time);
  
  void turnLeft (int time);
  
  void turnTowardLight ();
  
  void driveTowardLight(int time);
  
  void driveAwayFromLight(int time);

  void setAntenna (romiboaction_color_t color);
  
  void waitForButton (int max_time, romiboaction_button_t button);
  
  void waitForTargetRange (int max_time, int min_range, int max_range);
  
};
  
//Global object for accessing the RomiboAction library
extern RomiboAction RomiboAct;

#endif //__ROMIBOACTION_H_INCLUDED__
