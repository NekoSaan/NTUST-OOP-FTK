#pragma once
#include"Entity.h"
class Buff {

	int stage;
	int duration;
public:
	virtual string effect(Entity* role, string stage) {
		return "NULL";
	}
	virtual int getSpeed(int speed) {
		return 0;
	}
};