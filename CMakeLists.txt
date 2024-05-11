project(Project2)

set(src_SRC_LIST 
	${PROJECT_SOURCE_DIR}/src/Main.cpp
	${PROJECT_SOURCE_DIR}/src/GameManager.cpp	
	${PROJECT_SOURCE_DIR}/src/Object.cpp
	${PROJECT_SOURCE_DIR}/src/Rect.cpp

	${PROJECT_SOURCE_DIR}/src/GameManager.h
	${PROJECT_SOURCE_DIR}/src/Object.h
	${PROJECT_SOURCE_DIR}/src/Point.h
	${PROJECT_SOURCE_DIR}/src/Rect.h
)

add_executable(src ${src_SRC_LIST})