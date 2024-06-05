#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

// Declare Classes to let this file know they are exists
class Weapon;
class Armor;
class Accessory;

// Entity class represents a character or entity in the game
class Entity
{
protected:
    int vitality;       // Health points
    int maxFocus;       // Maximum focus points
    int speed;          // Speed
    int hitRate;        // Hit rate
    int pAttack;        // Physical attack
    int mAttack;        // Magical attack
    int pDefense;       // Physical defense
    int mDefense;       // Magical defense
    int focus;          // Current focus points
    int hp;             // Health
    std::string name;

public:
    Weapon* weapon;                     // Weapon
    Armor* armor;                       // Armor
    Accessory* acc;                     // Accessory
    int actions;                        // Number of actions
    std::vector<std::string> buff;      // Status effects
    std::vector<int> buffTime;          // Status effects duration
    std::string sort;
    // Constructor
    Entity(void);

    // Getter methods
    int getVitality();
    int getMaxFocus();
    int getSpeed();
    int getHitRate();
    int getPAttack();
    int getMAttack();
    int getPDefense();
    int getMDefense();
    int getFocus();
    int getHp();
    std::string getName();

    // Setter methods
    void setVitality(int newVitality);
    void setMaxFocus(int newFocus);
    void setSpeed(int newSpeed);
    void setHitRate(int newHitRate);
    void setPAttack(int newPAttack);
    void setMAttack(int newMAttack);
    void setPDefense(int newPDefense);
    void setMDefense(int newMDefense);
    void setHp(int);
    void setFocus(int);
    void setName(std::string Name);

    // Other methods
    bool searchBuff(std::string);
    void giveBuff(std::string, int);
    bool getPassiveSkill(std::string);
    void minusBuff();
    void removeBuff(std::string Buff);
    virtual int selectAction(std::vector<Entity*> role, std::vector<Entity*> enemy)=0;
    virtual void normalAttack(std::vector<Entity*> role, std::vector<Entity*> enemy)=0;
    virtual void skillAttack(std::vector<Entity*> role, std::vector<Entity*> enemy)=0;
   
};

#endif // _ENTITY_H_
