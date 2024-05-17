#pragma once
#include"Buff.h"

class SpeedUp :public Buff {
public:
	virtual int getSpeed(int speed) {
		return speed / 2;
	}
};
