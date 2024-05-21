#pragma once
#include "Event.h"

class ChestEvent : public Event {
public:
	ChestEvent();

	//Event virtual function
	void startEvent(Role* role);
};