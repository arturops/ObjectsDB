
CC=g++
RM=rm
OBJECT=ObjectDB
DB=ObjectsDB*.db
HELP=readme.txt
SRC=main.cpp Database.cpp BaseObject.cpp Box.cpp Cylinder.cpp BoundingBox.cpp GeometryValidator.cpp DBMediator.cpp Project.cpp Test.cpp
CFLAGS=-std=c++11 -l sqlite3

all : ${SRC}
	${CC} $^ -o ${OBJECT} ${CFLAGS}

clean :
	${RM} ${OBJECT}

cleanDB :
	${RM} ${DB}

help :
	@cat ${HELP}
	@echo "\n"
