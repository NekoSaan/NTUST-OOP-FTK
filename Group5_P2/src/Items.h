#ifndef _ITEMS_H_
#define _ITEMS_H_

#include <string>
#include <vector>

// Forward declaration of Role class
class Role;

// Declaration of static function to get the list of item names
std::vector<std::string> getItemList(void);

// Enumeration to represent different types of items
enum class ITEMID {
    // Consumables, stackable
    Godsbeard = 0,
    GoldenRoot,
    TeleportScroll,
    Tent,

    // Equipments, non-stackable
    // Weapons
    WoodenSword,
    Hammer,
    GiantHammer,
    MagicWand,
    RitualSword,

    // Armor
    WoodenShield,
    PlateArmor,
    LeatherArmor,
    Robe,
    LaurelWreath,

    // Accessory
    HolyGrail,
    Shoes,
    Bracelet,
    Invalid
};

// Item class represents an item in the game
class Item {
protected:
    std::string tag;        // Tag of the item
    std::string itemName;   // Name of the item
    ITEMID id;              // ID of the item
    int amount;             // Current amount of the item

public:
    // Default constructor
    Item(void);

    // Constructor
    Item(std::string, ITEMID);

    // Destructor
    ~Item(void);

    // Get the ID of the item
    int getId(void);

    // Get the amount of the item
    int getAmount(void);

    // Increase the amount of the item
    void incAmount(void);

    // Decrease the amount of the item
    void decAmount(void);

    // Get the tag of the item
    std::string getTag(void);

    // Get the name of the item
    std::string getName(void);

    // Virtual function to use the item by a role
    virtual void use(Role*);
};

#endif // _ITEMS_H_