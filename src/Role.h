#ifndef _ROLE_H_
#define _ROLE_H_
#include "Entity.h"
#include "Object.h"
#include "Enemy.h"
#include <vector>

// Role class represents a character role in the game
class Role : public Entity, public Object
{
public:
    // Constructor for Role class
    Role() : Entity() {};

    // Move the role to a new position on the game board and trigger any interactions with objects on the new position
    void move(int y, int x);

    void gainHealth(int);
    void gainFocus(int);

    // Object's virtual funtion
    void active(Role* role);
    void chooseActiveUP();
    void chooseActiveDown();
    vector<string> getAllChoose();
    int getChosenIndex();
    vector<string> getDescription();

    virtual void selectAction(std::vector<Entity* > role, std::vector<Entity* > enemy);
    virtual void normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy);
    virtual void skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy);
};

#endif _ROLE_H_