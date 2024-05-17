#ifndef _ROLE_H_
#define _ROLE_H_
#include "Entity.h"
#include "Object.h"
#include "Enemy.h"
#include "Buff.h"
#include <vector>

class Object;
class Entity;

class Role : public Entity, public Object {
public:
	Role() : Entity() {};
	void move(int y, int x);

	// Object's virtual funtion
	void active(Role* role);
	void chooseActiveUP();
	void chooseActiveDown();
	vector<string> getAllChoose();
	int getChosenIndex();

	//attack

};

#endif // _ROLE_H_
