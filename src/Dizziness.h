
#pragma once
#include"Buff.h"

class Dizziness :public Buff {
public:
	virtual std::string effect(Entity* role, std::string stage) {
		return "Dizziness";
	}
};
