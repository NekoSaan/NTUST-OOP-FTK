#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Weapon;
class Armor;
class Accessory;

// Entity class represents a character or entity in the game
class Entity
{
private:
    int vitality;       // Health points
    int maxFocus;       // Maximum focus points
    int speed;          // Speed
    int hitRate;        // Hit rate
    int pAttack;        // Physical attack
    int mAttack;        // Magical attack
    int pDefense;       // Physical defense
    int mDefense;       // Magical defense
    int focus;          // Current focus points
    int Hp;             // Health

public:
    Weapon* weapon;                     // Weapon
    int actions;                        // Number of actions
    std::vector<std::string> buff;      // Status effects
    std::vector<int> buffTime;          // Status effects duration

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
    std::string getWeaponName();

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

    // Other methods
    int useFocus(int MaxFocus);
    bool searchBuff(std::string);
    void giveBuff(std::string, int);
    void minusBuff();
    void removeBuff(std::string Buff);
    void selectAction(std::vector<Entity* > role, std::vector<Entity* > enemy);
    void normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy);
    void skillAttack(std::vector<Entity*> role, std::vector<Entity* > enemy);
    void Flee(std::vector<Entity* > role, std::vector<Entity* > enemy);
};

#endif _ENTITY_H_