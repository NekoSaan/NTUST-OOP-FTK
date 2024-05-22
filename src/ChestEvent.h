#ifndef _CHESTEVENT_H_
#define _CHESTEVENT_H_
#include "Event.h"

class ChestEvent : public Event 
{
public:
	ChestEvent();

	//Event virtual function
	void startEvent(Role* role);
};

#endif _CHESTEVENT_H_