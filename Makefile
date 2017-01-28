CFLAGS     := -Wall -pedantic -ggdb -O0 -std=c++11 -W
CXXFLAGS	 := -c -FPIC -shared
# CFLAGS     := -Wall -Werror -pedantic -ggdb -O0 -std=c++98 -W
LIBS       := -lrt -lpthread
TEST_LIBS  := $(LIBS) -lgtest
GCC        := g++
TARGET     := Framework
CPP_FILES  := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp) $(wildcard src/*/*/*/*.cpp) $(wildcard src/*/*/*/*/*.cpp)
TEST_FILES := $(CPP_FILES:src/%.cpp=test/%.test.cpp)
EXECUTABLE := bin/lib$(TARGET).so

shared_lib:
	$(CXX) $(CXXLAGS) $(CPP_FILES) $(LIBS) -o $(EXECUTABLE)

vardump:
	@clear
	@echo "TARGET\n$(TARGET)\n"
	@echo "EXECUTABLE\n$(EXECUTABLE)\n"
	@echo "CPP_FILES\n\t $(addsuffix \n\t, $(CPP_FILES))\n"
	@echo "OBJ_FILES\n\t $(addsuffix \n\t, $(OBJ_FILES))\n"
	@echo "TEST_FILE\n\t $(addsuffix \n\t, $(TEST_FILES))\n"

help:
	@clear
	@echo "The targets provided by this Makefile:"
	@echo "... all\t\tBuilds all the projects in this folder"
	@echo "... clean\tRemoves all executables and object files"
	@echo "... vardump\tShows a list of variables collected by this makefile"
	@echo "... run\t\tBuilds and executes the current project"
	@echo "... test\tBuilds all the test files for the current project"
	@echo "... valgrind\tBuilds the current project and runs it with valgrind"
	@echo "... valgrind_v\tBuilds the current project and runs it with valgrind in verbose mode"
	@echo ""
