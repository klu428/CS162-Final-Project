CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CSSFLAGS += -pendantic-errors
CXXFLAGS += -g

OBJS = Objects.o Map.o Validation.o Spaces.o Game.o

SRCS = Objects.cpp Map.cpp Validation.cpp Spaces.cpp Game.cpp

HEADERS = Objects.hpp Map.hpp Validation.hpp Spaces.hpp Game.hpp

rpg: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o rpg

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm Objects.o
	rm Map.o
	rm Validation.o
	rm Spaces.o
	rm Game.o
	rm rpg
