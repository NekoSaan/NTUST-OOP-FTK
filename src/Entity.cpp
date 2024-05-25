#include "Entity.h"
#include "Dice.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include <conio.h>
#include <algorithm>

// Intent: Construct an Entity object
// Pre: None
// Post: Constructs an Entity object with random attribute values within
//		 specified ranges, initializes focus, and creates a default weapon
Entity::Entity(void)
{
	setVitality(rand() % 15 + 30);  // random value between [30, 45)
	setMaxFocus(3);					// initialize to 3, fixed
	setFocus(3);					// initialize to 3, fixed
	setSpeed(rand() % 25 + 30);		// random value between [30, 55)
	setHitRate(rand() % 20 + 40);	// random value between [40, 60)
	setPAttack(rand() % 11 + 5);	// random value between [5, 15]
	setMAttack(rand() % 11 + 5);	// random value between [5, 15]
	setPDefense(rand() % 21);		// random value between [0, 20]
	setMDefense(rand() % 21);		// random value between [0, 20]
	setHp(getVitality());
	actions = 0;
	this->weapon = new Weapon("Empty", ITEMID::Invalid);
	this->armor = new Armor("Empty", ITEMID::Invalid);
	this->acc = new Accessory("Empty", ITEMID::Invalid);
}

// Intent: Set the vitality of the entity
// Pre: newVitality must be a non-negative integer
// Post: Sets the vitality of the entity to the specified value
void Entity::setVitality(int newVitality) 
{
	vitality = newVitality; 
}

// Intent: Set the maximum focus of the entity
// Pre: newFocus must be a non-negative integer
// Post: Sets the maximum focus of the entity to the specified value
void Entity::setMaxFocus(int newFocus) 
{
	maxFocus = newFocus;
}

// Intent: Set the speed of the entity
// Pre: newSpeed must be a non-negative integer
// Post: Sets the speed of the entity to the specified value
void Entity::setSpeed(int newSpeed) 
{
	speed = newSpeed; 
}

// Intent: Set the hit rate of the entity
// Pre: newHitRate must be a non-negative integer
// Post: Sets the hit rate of the entity to the specified value
void Entity::setHitRate(int newHitRate)
{
	hitRate = newHitRate; 
}

// Intent: Set the physical attack of the entity
// Pre: newPAttack must be a non-negative integer
// Post: Sets the physical attack of the entity to the specified value
void Entity::setPAttack(int newPAttack) 
{
	pAttack = newPAttack; 
}

// Intent: Set the magical attack of the entity
// Pre: newMAttack must be a non-negative integer
// Post: Sets the magical attack of the entity to the specified value
void Entity::setMAttack(int newMAttack)
{
	mAttack = newMAttack; 
}

// Intent: Set the physical defense of the entity
// Pre: newPDefense must be a non-negative integer
// Post: Sets the physical defense of the entity to the specified value
void Entity::setPDefense(int newPDefense) 
{
	pDefense = newPDefense; 
}

// Intent: Set the magical defense of the entity
// Pre: newMDefense must be a non-negative integer
// Post: Sets the magical defense of the entity to the specified value
void Entity::setMDefense(int newMDefense) 
{
	mDefense = newMDefense; 
}

// Intent: Set the current focus of the entity
// Pre: newFocus must be a non-negative integer
// Post: Sets the current focus of the entity to the specified value
void Entity::setFocus(int newFocus) 
{
	focus = newFocus; 
}

// Intent: Set the current hit points of the entity
// Pre: newHp must be a non-negative integer
// Post: Sets the current hit points of the entity to the specified value
void Entity::setHp(int newHp) 
{ 
	hp = newHp; 
}

// Intent: Search for a specific buff in the entity's buffs
// Pre: None
// Post: Returns true if the entity has the specified buff; otherwise, returns false
bool Entity::searchBuff(std::string Buff)
{
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);

	return it != buff.end();
}

// Intent: Give a buff to the entity
// Pre: None
// Post: Adds the specified buff to the entity's buffs with the specified duration
void Entity::giveBuff(std::string Buff, int BuffTime)
{
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);

	if (it != buff.end()) 
	{
		buff.push_back(Buff);
		buffTime.push_back(BuffTime);
	}
	else 
	{
		buffTime[it - buff.begin()] = BuffTime;
	}
}

// Intent: Decrease the duration of active buffs and remove expired buffs
// Pre: None
// Post: Decreases the duration of active buffs and removes buffs with expired durations
void  Entity::minusBuff()
{
	for (int i = 0; i < buffTime.size(); i++) 
	{
		buffTime[i]--;

		if (buffTime[i] < 0) 
		{
			removeBuff(buff[i]);
		}
	}
}

// Intent: Remove a specific buff from the entity
// Pre: None
// Post: Removes the specified buff from the entity's buffs
void Entity::removeBuff(std::string Buff)
{
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);
	int index = std::distance(buff.begin(), it);
	buff.erase(it);
	buffTime.erase(buffTime.begin() + index);
}

// Intent: Get the current vitality of the entity
// Pre: None
// Post: Returns the current vitality of the entity
int Entity::getVitality()
{
	return vitality;
}

// Intent: Get the maximum focus of the entity
// Pre: None
// Post: Returns the maximum focus of the entity
int Entity::getMaxFocus()
{
	return maxFocus + acc->getMaxFocus();
}


// Intent: Get the effective speed of the entity, considering buffs and equipped weapon
// Pre: None
// Post: Returns the effective speed of the entity
int Entity::getSpeed() 
{
	int Speed = speed + armor->getSpeed() + acc->getSpeed();

	if (searchBuff("SpeedUp")) 
	{
		Speed *= 1.5;
	}

	return std::min(100, Speed);
}

// Intent: Get the effective hit rate of the entity, considering buffs
// Pre: None
// Post: Returns the effective hit rate of the entity
int Entity::getHitRate() 
{ 
	int HitRate = hitRate + weapon->getHitRate() - (searchBuff("Angle") ? 30 : 0);

	return std::min(100, HitRate);
}

// Intent: Get the effective physical attack of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective physical attack of the entity
int Entity::getPAttack() 
{
	return std::min(100, pAttack + weapon->getPAttack());
}

// Intent: Get the effective magical attack of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective magical attack of the entity
int Entity::getMAttack() 
{
	return std::min(100, mAttack + weapon->getMAttack());
}

// Intent: Get the effective physical defense of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective physical defense of the entity
int Entity::getPDefense() 
{
	return std::min(100, pDefense + armor->getPDefense());
}

// Intent: Get the effective magical defense of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective magical defense of the entity
int Entity::getMDefense() 
{
	int MDefense = mDefense + armor->getMDefense() + acc->getMDefense();

	return std::min(100, mDefense);
}

// Intent: Get the current focus of the entity
// Pre: None
// Post: Returns the current focus of the entity
int Entity::getFocus() 
{
	return focus; // current focus
}

// Intent: Get the current hit points of the entity
// Pre: None
// Post: Returns the current hit points of the entity
int Entity::getHp() 
{
	return hp; // current health
}

// Intent: Select an action for the entity based on user input
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Selects an action for the entity based on user input
void Entity::selectAction(std::vector<Entity*> role, std::vector<Entity*> enemy) 
{
	char c = _getch();

	if (c == '0') 
	{
		normalAttack(role, enemy);
	}
	else if (c == '1') 
	{
		skillAttack(role, enemy);
	}
	else if (c == '3') 
	{
		Flee(role, enemy);
	}
}

// Intent: Perform a normal attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a normal attack against an enemy entity
void Entity::normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) 
{
	if (weapon->getType() == 'p') 
	{
		char c = _getch();
		int n = useFocus(1);
		int absorption = enemy[(int)c]->getPDefense() / (getPDefense() + 50);
		int Attack = getPAttack() * dice(n, 1, getHitRate());
		enemy[0]->setHp(enemy[(int)c]->getHp() - Attack * (1 - absorption));
	}
}

// Intent: Perform a skill attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a skill attack against an enemy entity
void Entity::skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) 
{
	if (weapon->getActiveSkill() == "Provoke") 
	{
		int HitRate = getHp() / (getVitality() + getPDefense() + getMDefense()) * getSpeed();
		char c = _getch();
		int n = useFocus(1);

		if (dice(n, 1, HitRate) == 1) 
		{
			enemy[(int)c]->giveBuff("Angry", 3);
		}
	}
}

// Intent: Use focus points for an action
// Pre: MaxFocus must be a non-negative integer
// Post: Uses focus points for an action
int Entity::useFocus(int MaxFocus) {
	while (true) {
		char c = getch();

		// 检查输入是否为有效数字字符
		if (!isdigit(c)) {
			std::cout << "Invalid input. Please enter a digit." << std::endl;
			continue;
		}

		int n = c - '0';  // 将字符转换为数字

		// 检查使用的注意力值是否超过限制
		if (n > getFocus() || n > MaxFocus) {
			std::cout << "Fail: Amount exceeds available or maximum focus." << std::endl;
			continue;
		}
		else {
			setFocus(getFocus() - n);
			return n;
		}
	}
}

// Intent: Attempt to flee from a battle
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Attempts to flee from a battle
void Entity::Flee(std::vector<Entity* > role, std::vector<Entity* > enemy) 
{
}