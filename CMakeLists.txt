project(project_Framework)

set(project_SRC_LIST 
    ${PROJECT_SOURCE_DIR}/src/Main.cpp

    ${PROJECT_SOURCE_DIR}/src/GameManager.h
    ${PROJECT_SOURCE_DIR}/src/GameManager.cpp

    ${PROJECT_SOURCE_DIR}/src/Dice.h
    ${PROJECT_SOURCE_DIR}/src/Dice.cpp

    ${PROJECT_SOURCE_DIR}/src/Point.h
    ${PROJECT_SOURCE_DIR}/src/Point.cpp

    ${PROJECT_SOURCE_DIR}/src/Rect.h
    ${PROJECT_SOURCE_DIR}/src/Rect.cpp
    
    ${PROJECT_SOURCE_DIR}/src/Object.h
    ${PROJECT_SOURCE_DIR}/src/Object.cpp

    ${PROJECT_SOURCE_DIR}/src/Event.h
    ${PROJECT_SOURCE_DIR}/src/Event.cpp

    ${PROJECT_SOURCE_DIR}/src/ChestEvent.h
    ${PROJECT_SOURCE_DIR}/src/ChestEvent.cpp

    ${PROJECT_SOURCE_DIR}/src/SpringEvent.h
    ${PROJECT_SOURCE_DIR}/src/SpringEvent.cpp

    ${PROJECT_SOURCE_DIR}/src/Backpack.h
    ${PROJECT_SOURCE_DIR}/src/Backpack.cpp

    ${PROJECT_SOURCE_DIR}/src/Entity.h
    ${PROJECT_SOURCE_DIR}/src/Entity.cpp
    
    ${PROJECT_SOURCE_DIR}/src/Role.h
    ${PROJECT_SOURCE_DIR}/src/Role.cpp

    ${PROJECT_SOURCE_DIR}/src/Items.h
    ${PROJECT_SOURCE_DIR}/src/Items.cpp

    ${PROJECT_SOURCE_DIR}/src/Shop.h
    ${PROJECT_SOURCE_DIR}/src/Shop.cpp
    
    ${PROJECT_SOURCE_DIR}/src/Enemy.h
    ${PROJECT_SOURCE_DIR}/src/Enemy.cpp

    ${PROJECT_SOURCE_DIR}/src/Combat.h
    ${PROJECT_SOURCE_DIR}/src/Combat.cpp

    ${PROJECT_SOURCE_DIR}/src/Weapon.h
    ${PROJECT_SOURCE_DIR}/src/Weapon.cpp

    ${PROJECT_SOURCE_DIR}/src/Armor.h
    ${PROJECT_SOURCE_DIR}/src/Armor.cpp

    ${PROJECT_SOURCE_DIR}/src/Accessory.h
    ${PROJECT_SOURCE_DIR}/src/accessory.cpp

    ${PROJECT_SOURCE_DIR}/src/TeleportScroll.h
    ${PROJECT_SOURCE_DIR}/src/TeleportScroll.cpp

    ${PROJECT_SOURCE_DIR}/src/Tent.h
    ${PROJECT_SOURCE_DIR}/src/Tent.cpp
)

add_executable(project ${project_SRC_LIST})