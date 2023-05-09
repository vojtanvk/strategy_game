
FINAL = semestral

SOURCES = $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp)
HEADERS = $(wildcard src/*.hpp src/*/*.hpp src/*/*/*.hpp src/*/*/*/*.hpp)

OBJS = ${SOURCES:.cpp=.o}

CPPFLAGS = -Wall -pedantic -Wextra -std=c++17 -Wno-long-long -O2 -g -lstdc++fs
COMPILER = g++

all: ${OBJS}

compile: ${OBJS}
	${COMPILER} $^ -o ${FINAL}


run: compile
	./semestral

conf: compile
	./semestral -c

run_def: compile
	./semestral examples/gui_conf examples/conf examples/saves/map_test

load_def: compile
	./semestral examples/gui_conf

doc:
	doxygen Doxyfile



%.o : %.cpp
	${COMPILER} -c ${CPPFLAGS} $< -o $@

clean:
	rm -f ${OBJS}
	rm -f Makefile.d
	rm -f ${FINAL}
	
Makefile.d: $(SOURCES) $(HEADERS)
	g++ -MM $(SOURCES) > Makefile.d

include Makefile.d