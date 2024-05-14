#pragma once
#include "Role.h"
class Buff {
	int stage;
	int duration;
public:
	virtual void effect(Role* role);
};