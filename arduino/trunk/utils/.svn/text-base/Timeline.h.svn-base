/* This file defines a class meant for setting up and executing function calls on a timeline. */
#ifndef __TIMELINE_H_INCLUDED__
#define __TIMELINE_H_INCLUDED__

#define TIMELINE_DEFAULT_SIZE 10

typedef struct {
  int entries; //the number of events in the timeline
  long * times; //a pointer to the list of times
  void ** funs; //a pointer to the list of functions to call

} timelineEvents;

class Timeline
{
#include <ElapsedTimer.h>

protected:
  ElapsedTimer timer;
  
  
public:
  //default constructor, used to create a new timeline
  Timeline() {
    timer = ElapsedTimer();
	
  }

}



#endif