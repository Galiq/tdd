# This are internal config for Make
#VER=$(shell hg head | head -n 1 | awk -F'[: \t]+' '{print $$2}')
VER_MAJOR=0
VER_MINOR=0
CPPFLAGS= -fPIC -pthread -std=c++11 -ggdb -fopenmp -I./include -I./thirdparty/json -I./thirdparty/catch -I./thirdparty/fakeit
CLIBS= -std=c++11 -fopenmp -ldl -rdynamic


##################  CONFIG #################
#

BASESOURCES = $(wildcard src/*.cpp)
BASEOBJS := $(BASESOURCES:src%.cpp=build%.o)

TESTSOURCES = $(wildcard test/*.cpp)
TESTOBJS := $(TESTSOURCES:test%.cpp=build/test%.o)

#
################## ENDCONDIF ###############


all: $(BASEOBJS)
	
unittests: $(BASEOBJS) $(TESTOBJS)
	g++ -O2 $^ -o $@ $(CLIBS)

test: unittests
	./unittests
#	./unittests -r junit

build/%.o : src/%.cpp
	@echo $<
	gcc -c $(CPPFLAGS) $< -o $@

build/test/%.o : test/%.cpp
	@echo $<
	gcc -c $(CPPFLAGS) $< -o $@

clean:
	rm -f $(APPNAME) $(OBJS) build/*.o build/test/*.o unittests
