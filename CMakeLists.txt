project(Project2_Framework)

set(Project2_SRC_LIST 
	${PROJECT_SOURCE_DIR}/Project2/Main.cpp
	${PROJECT_SOURCE_DIR}/Project2/Main.h
	${PROJECT_SOURCE_DIR}/Project2/GameManager.h
	${PROJECT_SOURCE_DIR}/Project2/Object.h
	${PROJECT_SOURCE_DIR}/Project2/Point.h
	${PROJECT_SOURCE_DIR}/Project2/Rect.h
)

add_executable(Project2 ${Project2_SRC_LIST})