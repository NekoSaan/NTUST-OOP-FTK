#ifndef _CHESTEVENT_H_
#define _CHESTEVENT_H_
#include "Event.h"

class ChestEvent : public Event 
{
private:
	//Event virtual function
	void startEvent(Role* role);

public:
	ChestEvent();

	//Event virtual function
	vector<string> getDescription();
};

#endif _CHESTEVENT_H_