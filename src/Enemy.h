#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy(void) : Entity() {};
	virtual void selectAction(std::vector<Entity* > role, std::vector<Entity* > enemy);
	virtual void normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy);
};

#endif // _ENEMY_H_
