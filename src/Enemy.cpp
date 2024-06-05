#include "Enemy.h"
#include "Dice.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "GameManager.h"
#include "Backpack.h"
#include "Rect.h"
#include "Combat.h"
#include <conio.h>
#include <cmath>

// Intent: Constructor for the Enemy class initializing member variables and equipping a random weapon
// Pre: None
// Post: Initializes an Enemy instance with default values and a random weapon
Enemy::Enemy() : Entity() {
    this->tag = TAG_ENEMY;
    this->icon = 'E';
    this->chosenIndex = 0;

    // Enemy will randomly get a weapon
    int randWeapon = rand() % 200 + 1;

    if (randWeapon < 50) {
        randWeapon = rand() % 5 + (int)ITEMID::WoodenSword;
        weapon = new Weapon("Weapon", ITEMID(randWeapon));
    }
    else {
        weapon = new Weapon("Empty", ITEMID::Invalid);
    }

    armor = new Armor("Empty", ITEMID::Invalid);
    acc = new Accessory("Empty", ITEMID::Invalid);
}

// Intent: Support combat by gathering allies and enemies within range and starting the combat
// Pre: role must be a valid pointer to a Role object
// Post: Initiates combat with nearby allies and enemies
void Enemy::combatSupport(Role* role) {
    GameManager* gameManager = GameManager::getInstance();
    vector<Entity*> enemies;
    vector<Rect*> enemyRect;
    vector<Entity*> roles;

    enemies.push_back(this);
    roles.push_back(role);
    enemyRect.push_back(&GameManager::gameBoard[role->getPos().first][role->getPos().second]);

    // Find nearby roles
    for (int i = 0; i < 3; i++) {
        Role* r = gameManager->getRole(i);

        if (r == role) {
            continue;
        }

        if (abs(r->getPos().first - role->getPos().first) + abs(r->getPos().second - role->getPos().second) <= 3) {
            roles.push_back(r);
        }
    }

    // Find nearby enemies
    int relativePos[24][2] = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {2, 0}, {1, 1}, {0, 2}, {-1, 1}, {-2, 0}, {-1, -1}, {0, -2}, {1, -1},
        {3, 0}, {2, 1}, {1, 2}, {0, 3}, {-1, 2}, {-2, 1}, {-3, 0}, {-2, -1}, {-1, -2}, {0, -3}, {1, -2}, {2, -1}
    };

    for (int i = 0; i < 24; i++) {
        if (!GameManager::isPositionValid(role->getPos().first + relativePos[i][0], role->getPos().second + relativePos[i][1])) {
            continue;
        }

        Object* obj = GameManager::gameBoard[role->getPos().first + relativePos[i][0]][role->getPos().second + relativePos[i][1]].getObject();

        if (obj == NULL) {
            continue;
        }

        if (obj->getTag() == Object::TAG_ENEMY) {
            enemyRect.push_back(&GameManager::gameBoard[role->getPos().first + relativePos[i][0]][role->getPos().second + relativePos[i][1]]);
            enemies.push_back((Enemy*)obj);

            if (enemies.size() >= 3) {
                break;
            }
        }
    }

    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->setName("Enemy " + to_string(i + 1));
    }

    // Start combat
    combat(roles, enemies);

    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getHp() <= 0) {
            enemyRect[i]->die = 1;
        }
    }
}

// Intent: Use a specified amount of focus during combat
// Pre: n must be a non-negative integer, role and enemy must be valid vectors of Entity pointers
// Post: Returns the amount of focus used (currently a placeholder returning 0)
int useFocus(int n, std::vector<Entity*> role, std::vector<Entity*> enemy) {
    return 0;
}

// Intent: Select an action for the enemy entity
// Pre: role and enemy must be valid vectors of Entity pointers
// Post: Performs the selected action
int Enemy::selectAction(std::vector<Entity*> role, std::vector<Entity*> enemy) {
    int index = rand() % 2;

    if (index == 0) {
        normalAttack(role, enemy);
    }
    else if (index == 1) {
        skillAttack(role, enemy);
    }

    return 0;
}

// Intent: Perform a normal attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a normal attack against an enemy entity
void Enemy::normalAttack(std::vector<Entity*> role, std::vector<Entity*> enemy) {
    int targetIndex = selectTarget(role, enemy);
    GameManager* gameManager = GameManager::getInstance();
    gameManager->battleScreen(role, enemy, { "" }, { "" });

    if (weapon->getType() == 'p') {
        int n = useFocus(1, role, enemy);
        int absorption = role[targetIndex]->getPDefense() / (getPDefense() + 50);
        int attack = getPAttack() * dice(n, 1, getHitRate());
        role[targetIndex]->setHp(role[targetIndex]->getHp() - attack * (1 - absorption) * ((role[targetIndex]->getPassiveSkill("Fortify") == 1) ? 0.9 : 1));

        if (getPassiveSkill("Hammer-Splash") == 1 && attack == getPAttack()) {
            role[targetIndex]->giveBuff("Dizziness", 3);

            for (int i = 0; i < role.size(); i++) {
                if (i != targetIndex) {
                    role[i]->setHp(role[i]->getHp() - attack * (1 - (role[i]->getPDefense() / (role[i]->getPDefense() + 50))));
                }
            }
        }
    }
    else {
        int n = useFocus(1, role, enemy);
        int absorption = role[targetIndex]->getMDefense() / (getMDefense() + 50);
        int attack = getMAttack() * dice(n, 1, getHitRate());
        role[targetIndex]->setHp(role[targetIndex]->getHp() - attack * (1 - absorption) * ((role[targetIndex]->getPassiveSkill("Fortify") == 1) ? 0.9 : 1));

        if (getPassiveSkill("Hammer-Splash") == 1 && attack == getMAttack()) {
            role[targetIndex]->giveBuff("Dizziness", 3);

            for (int i = 0; i < role.size(); i++) {
                if (i != targetIndex) {
                    role[i]->setHp(role[i]->getHp() - attack * (1 - (role[i]->getMDefense() / (role[i]->getMDefense() + 50))));
                }
            }
        }
    }

    if (getPassiveSkill("Destroy") == 1) {
        while (!(role[targetIndex]->weapon->getId() == 17 && role[targetIndex]->armor->getId() == 17 && role[targetIndex]->acc->getId() == 17)) {
            int index = rand() % 3;

            if (index == 0) {
                if (role[targetIndex]->weapon->getId() == 17) {
                    continue;
                }
                else {
                    bag.deleteItemById(role[targetIndex]->weapon->getId());
                    role[targetIndex]->weapon = new Weapon("Empty", ITEMID::Invalid);
                    break;
                }
            }
            else if (index == 1) {
                if (role[targetIndex]->armor->getId() == 17) {
                    continue;
                }
                else {
                    bag.deleteItemById(role[targetIndex]->armor->getId());
                    role[targetIndex]->armor = new Armor("Empty", ITEMID::Invalid);
                    break;
                }
            }
            else if (index == 2) {
                if (role[targetIndex]->acc->getId() == 17) {
                    continue;
                }
                else {
                    bag.deleteItemById(role[targetIndex]->acc->getId());
                    role[targetIndex]->acc = new Accessory("Empty", ITEMID::Invalid);
                    break;
                }
            }
        }
    }
}

// Intent: Perform a skill attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a skill attack against an enemy entity
void Enemy::skillAttack(std::vector<Entity*> role, std::vector<Entity*> enemy) {
    GameManager* gameManager = GameManager::getInstance();
    gameManager->battleScreen(role, enemy, { "" }, { "select target (input number)" });

    if (weapon->getCD() > 0) {
        selectAction(role, enemy);
        return;
    }

    if (weapon->getActiveSkill() == "Provoke") {
        int HitRate = getHp() / (getVitality() + getPDefense() + getMDefense()) * getSpeed();
        int targetIndex = selectTarget(role, enemy);
        int n = useFocus(1, role, enemy);

        if (dice(n, 1, HitRate) == 1) {
            role[targetIndex]->giveBuff("Angry", 3);
        }

        weapon->setCD(3);

    }
    else if (weapon->getActiveSkill() == "Shock - Blast") {
        int n = useFocus(3, role, enemy);

        for (int i = 0; i < role.size(); i++) {
            int absorption = role[i]->getMDefense() / (getMDefense() + 50);
            int attack = getMAttack() * dice(n, 3, getHitRate() - 5);
            role[i]->setHp(role[i]->getHp() - attack / 2 * (1 - absorption));
        }

        weapon->setCD(2);

    }
    else if (weapon->getActiveSkill() == "Heal") {
        int targetIndex = selectTarget(role, role);
        int n = useFocus(2, role, enemy);

        if (dice(n, 2, getHitRate()) == 2) {
            enemy[targetIndex]->setHp(enemy[targetIndex]->getHp() + getMAttack() * 3 / 2);
        }

        weapon->setCD(2);

    }
    else if (weapon->getActiveSkill() == "SpeedUp") {
        int targetIndex = selectTarget(enemy, role);
        int n = useFocus(2, role, enemy);

        if (dice(n, 2, getHitRate()) == 2) {
            enemy[targetIndex]->giveBuff("SpeedUp", 3);
        }

        weapon->setCD(4);

    }
    else {
        selectAction(role, enemy);
    }
}

// Intent: Execute the active event based on the chosen index
// Pre: role must be a valid pointer to a Role object
// Post: Executes the appropriate event action
void Enemy::active(Role* role) {
    switch (chosenIndex) {
    case 0:
        combatSupport(role);
        break;
    case 1:
        exitActive(role);
        break;
    }
}

// Intent: Move the selection index up
// Pre: None
// Post: Decreases the chosenIndex value, wrapping around if necessary
void Enemy::chooseActiveUP() {
    chosenIndex--;

    if (chosenIndex < 0) {
        chosenIndex = 1;
    }
}

// Intent: Move the selection index down
// Pre: None
// Post: Increases the chosenIndex value, wrapping around if necessary
void Enemy::chooseActiveDown() {
    chosenIndex++;

    if (chosenIndex > 1) {
        chosenIndex = 0;
    }
}

// Intent: Get all available choices for the enemy's active events
// Pre: None
// Post: Returns a vector of strings containing all choices
vector<string> Enemy::getAllChoose() {
    vector<string> choose;
    choose.push_back("Fight!");
    choose.push_back("Retreat");
    return choose;
}

// Intent: Get the current chosen index
// Pre: None
// Post: Returns the chosenIndex value
int Enemy::getChosenIndex() {
    return chosenIndex;
}

// Intent: Get the description of the enemy
// Pre: None
// Post: Returns a vector of strings containing the enemy's description
vector<string> Enemy::getDescription() {
    vector<string> description;
    description.push_back("This is an enemy, maybe a goblin");
    description.push_back("HP: " + to_string(hp));
    description.push_back("Physical attack: " + to_string(pAttack));
    description.push_back("Magical attack: " + to_string(mAttack));
    return description;
}

// Intent: Select a target from the role entities
// Pre: role must be a non-empty vector of Entity pointers
// Post: Returns the index of the selected target
int Enemy::selectTarget(std::vector<Entity*> role, std::vector<Entity*> enemy) {
    return rand() % role.size();
}

// Intent: Exit the active event and return the role to its last position
// Pre: role must be a valid pointer to a Role object
// Post: Moves the role to its last position
void Enemy::exitActiveEvent(Role* role) {
    role->moveTolastPos();
}
