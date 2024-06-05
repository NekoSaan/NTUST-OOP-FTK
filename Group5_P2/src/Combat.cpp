#include "Entity.h"
#include "GameManager.h"
#include "Weapon.h"
#include <algorithm>

using namespace std;

// Intent: Compare two entities based on various combat priority criteria
// Pre: a and b must be valid pointers to Entity objects
// Post: Returns true if entity a has a lower priority than entity b, false otherwise
bool compareEntities(Entity* a, Entity* b) {
    if (((a->actions + 1) * 100 / a->getSpeed()) != ((b->actions + 1) * 100 / b->getSpeed())) {
        return ((a->actions + 1) * 100 / a->getSpeed()) < ((b->actions + 1) * 100 / b->getSpeed());
    }

    if (a->getSpeed() != b->getSpeed()) {
        return a->getSpeed() > b->getSpeed();
    }

    if ((a->getPAttack() + a->getMAttack()) != (b->getPAttack() + b->getMAttack())) {
        return (a->getPAttack() + a->getMAttack()) > (b->getPAttack() + b->getMAttack());
    }

    if ((a->getPDefense() + a->getMDefense()) != (b->getPDefense() + b->getMDefense())) {
        return (a->getPDefense() + a->getMDefense()) > (b->getPDefense() + b->getMDefense());
    }

    return a->getVitality() > b->getVitality();
}

// Intent: Perform an action by the actor entity and handle its effects
// Pre: actor must be a valid pointer to an Entity object, role and enemy must be valid vectors of Entity pointers
// Post: Updates the actor's state and returns 1 if an action is performed successfully, 0 otherwise
int Action(Entity* actor, vector<Entity*> role, vector<Entity*> enemy) {
    actor->actions++;

    if (actor->searchBuff("Dizziness") == 0) {
        if (actor->selectAction(role, enemy) == 1) {
            return 1;
        }
    }

    if (actor->searchBuff("Poisoned") == 1) {
        actor->setHp(max(actor->getHp() / 10, 1));
    }

    actor->minusBuff();
    actor->weapon->setCD(max(actor->weapon->getCD() - 1, 0));
    return 0;
}

// Intent: Handle the combat between role and enemy entities
// Pre: role and enemy must be valid vectors of Entity pointers
// Post: Simulates the combat, updating the state of each entity and removing defeated ones
void combat(vector<Entity*> role, vector<Entity*> enemy) {
    vector<Entity*> entity;

    // Combine role and enemy entities into a single vector
    for (Entity* x : role) {
        entity.push_back(x);
    }

    for (Entity* x : enemy) {
        entity.push_back(x);
    }

    // Sort entities based on combat priority
    std::sort(entity.begin(), entity.end(), compareEntities);
    string sort;

    for (int i = 0; i < entity.size(); i++) {
        sort += entity[i]->getName();

        if (i != entity.size() - 1) {
            sort += " <- ";
        }
    }

    // First entity in sorted order takes action
    Entity* actor = entity[0];
    actor->sort = sort;

    if (Action(actor, role, enemy) == 1) {
        auto it = std::find(role.begin(), role.end(), actor);

        if (it != role.end()) {
            (*it)->actions = 0;
            (*it)->buff.clear();
            role.erase(it);
        }
    }

    // Remove defeated role entities
    for (auto it = role.begin(); it != role.end();) {
        if ((*it)->getHp() <= 0) {
            (*it)->actions = 0;
            (*it)->weapon->setCD(0);
            (*it)->setHp(0);
            (*it)->buff.clear();
            it = role.erase(it);
        }
        else {
            ++it;
        }
    }

    // Remove defeated enemy entities
    for (auto it = enemy.begin(); it != enemy.end();) {
        if ((*it)->getHp() <= 0) {
            (*it)->actions = 0;
            (*it)->weapon->setCD(0);
            it = enemy.erase(it);
        }
        else {
            ++it;
        }
    }

    // Continue combat if both sides have remaining entities
    if (!role.empty() && !enemy.empty()) {
        combat(role, enemy);
    }
    else {
        // Exit combat and reset entities
        for (Entity* x : entity) {
            x->actions = 0;
            x->weapon->setCD(0);
            x->buff.clear();
        }

        system("CLS");
    }
}