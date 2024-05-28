#pragma once
#include "Event.h"

class SpringEvent : public Event
{
private:
	//Event virtual function
	void startEvent(Role* role);

public:
	SpringEvent();

	//Event virtual function
	void updateDescription();
};