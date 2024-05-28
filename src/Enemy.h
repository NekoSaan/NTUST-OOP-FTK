#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Entity.h"
#include "Object.h"

class Enemy : public Entity, public Object {
private:
	int chosenIndex;
	void combatSupport(Role* role); //find enemy and role around, then start combat

public:
	Enemy();

	virtual int selectAction(std::vector<Entity*> role, std::vector<Entity*> enemy);
	virtual void normalAttack(std::vector<Entity*> role, std::vector<Entity*> enemy);
	virtual void skillAttack(std::vector<Entity*> role, std::vector<Entity*> enemy);

	//Object's virtual function
	void active(Role* role);
	void chooseActiveUP();
	void chooseActiveDown();
	vector<string> getAllChoose();
	int getChosenIndex();
	vector<string> getDescription();
};

#endif // _ENEMY_H_
