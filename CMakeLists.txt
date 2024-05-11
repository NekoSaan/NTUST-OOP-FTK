project(project_Framework)

set(project_SRC_LIST 
	${PROJECT_SOURCE_DIR}/src/Main.cpp
	${PROJECT_SOURCE_DIR}/src/Main.h
	${PROJECT_SOURCE_DIR}/src/GameManager.h
	
	${PROJECT_SOURCE_DIR}/src/Point.h
	${PROJECT_SOURCE_DIR}/src/Rect.h
	${PROJECT_SOURCE_DIR}/src/Object.h

	${PROJECT_SOURCE_DIR}/src/Backpack.h
	${PROJECT_SOURCE_DIR}/src/Items.h
    ${PROJECT_SOURCE_DIR}/src/Shop.h
)

add_executable(project ${project_SRC_LIST})