project(project_Framework)

set(project_SRC_LIST 
    ${PROJECT_SOURCE_DIR}/src/Main.cpp

    ${PROJECT_SOURCE_DIR}/src/GameManager.h
    ${PROJECT_SOURCE_DIR}/src/GameManager.cpp

    ${PROJECT_SOURCE_DIR}/src/Dice.h
    ${PROJECT_SOURCE_DIR}/src/Dice.cpp

    ${PROJECT_SOURCE_DIR}/src/Point.h

    ${PROJECT_SOURCE_DIR}/src/Rect.h
    ${PROJECT_SOURCE_DIR}/src/Rect.cpp
    
    ${PROJECT_SOURCE_DIR}/src/Object.h
    ${PROJECT_SOURCE_DIR}/src/Object.cpp

    ${PROJECT_SOURCE_DIR}/src/Backpack.h
    ${PROJECT_SOURCE_DIR}/src/Backpack.cpp

    ${PROJECT_SOURCE_DIR}/src/Items.h
    ${PROJECT_SOURCE_DIR}/src/Shop.h
    
    ${PROJECT_SOURCE_DIR}/src/Entity.h
    ${PROJECT_SOURCE_DIR}/src/Entity.cpp
    
    ${PROJECT_SOURCE_DIR}/src/Role.h
    ${PROJECT_SOURCE_DIR}/src/Role.cpp
)

add_executable(project ${project_SRC_LIST})