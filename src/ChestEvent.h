#ifndef _CHESTEVENT_H_
#define _CHESTEVENT_H_
#include "Event.h"

// Chest event Class, inherti Event Class
class ChestEvent : public Event
{
private:
	// Event virtual function
	void startEvent(Role* role);

public:
	// Default Constructor
	ChestEvent(void);

	// Event virtual function
	void updateDescription();
};

#endif _CHESTEVENT_H_
