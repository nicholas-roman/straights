CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g
EXEC = straights
OBJECTS = main.o card.o computer.o game.o human.o player.o deck.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
