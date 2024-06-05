#ifndef _SPRINTEVENT_H_
#define _SPRINTEVENT_H_

#include "Event.h"

class SpringEvent : public Event
{
private:
	//Event virtual function
	void startEvent(Role* role);

public:
	// Sprint event construct
	SpringEvent();

	//Event virtual function
	void updateDescription();
};

#endif // _SPRINTEVENT_H_