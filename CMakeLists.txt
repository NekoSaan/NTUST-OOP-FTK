project(Project2_Framework)

set(Project2_SRC_LIST 
	${PROJECT_SOURCE_DIR}/src/Source.cpp
	${PROJECT_SOURCE_DIR}/src/Point.h
	${PROJECT_SOURCE_DIR}/src/Character.h
)

add_executable(Project2 ${Project2_SRC_LIST})