#pragma once
#include"Entity.h"
class Buff {
	int stage;
	int duration;
public:
	virtual void effect(Entity* role);
};