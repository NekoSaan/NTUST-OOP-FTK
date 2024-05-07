project(Project2_Framework)

set(Project2_SRC_LIST 
	${PROJECT_SOURCE_DIR}/Project2/Source.cpp
	${PROJECT_SOURCE_DIR}/Project2/Point.h
	${PROJECT_SOURCE_DIR}/Project2/Character.h
)

add_executable(Project2 ${Project2_SRC_LIST})