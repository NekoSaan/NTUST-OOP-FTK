#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Entity.h"
#include "Object.h"

class Enemy : public Entity, public Object {
private:
	int chosenIndex;
	void combatSupport(Role* role); //find enemy and role around, then start combat
	void exitActiveEvent(Role* role) override;

public:
	Enemy();
	int Enemy::selectTarget(std::vector<Entity* > role, std::vector<Entity* > enemy);
	virtual int selectAction(std::vector<Entity*> role, std::vector<Entity*> enemy);
	virtual void normalAttack(std::vector<Entity*> role, std::vector<Entity*> enemy);
	virtual void skillAttack(std::vector<Entity*> role, std::vector<Entity*> enemy);

	//Object's virtual function
	void active(Role* role) override;
	void chooseActiveUP() override;
	void chooseActiveDown() override;
	vector<string> getAllChoose() override;
	int getChosenIndex() override;
	vector<string> getDescription() override;
};

#endif // _ENEMY_H_
