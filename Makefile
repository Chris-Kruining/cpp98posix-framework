CFLAGS     := -Wall -pedantic -ggdb -O0 -std=c++11 -W
# CFLAGS     := -Wall -Werror -pedantic -ggdb -O0 -std=c++98 -W
LIBS       := -lrt -lpthread
TEST_LIBS  := $(LIBS) -lgtest
GCC        := g++
TARGET     := Scanner
CPP_FILES  := $(wildcard $(TARGET)/src/*.cpp) $(wildcard  $(TARGET)/src/*/*.cpp) $(wildcard  $(TARGET)/src/*/*/*.cpp) $(wildcard  $(TARGET)/src/*/*/*/*.cpp) $(wildcard  $(TARGET)/src/*/*/*/*/*.cpp)
OBJ_FILES  := $(CPP_FILES:$(TARGET)/src/%.cpp=$(TARGET)/obj/%.o)
TEST_FILES := $(CPP_FILES:$(TARGET)/src/%.cpp=$(TARGET)/test/%.test.cpp)
EXECUTABLE := $(TARGET)/bin/program

$(TARGET): clean $(OBJ_FILES)
	@echo "creating the executable"
	@$(GCC) $(CFLAGS) $(OBJ_FILES) $(LIBS) -o $(EXECUTABLE)

run: $(TARGET)
	@echo "running the executable\n\n"
	@$(EXECUTABLE)

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

all:
	$(MAKE) TARGET=Scanner
	$(MAKE) TARGET=Server
	$(MAKE) TARGET=Plotter

test: clean $(TEST_FILES)
	@mkdir -p $(TARGET)/bin
	@$(GCC) $(CFLAGS) $(TEST_FILES) $(TEST_LIBS) -o $(EXECUTABLE)

install: $(TARGET)
	@scp $(EXECUTABLE) root@${VICTIM}:~

.PHONY: clean

clean:
	@clear
	@echo "clearing previous object files and executable"
	@rm -f $(EXECUTABLE)
	@rm -f $(OBJ_FILES)
	@echo "create bin folder if needed"
	@mkdir -p $(TARGET)/bin -m 775

valgrind: $(TARGET)
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(EXECUTABLE)

valgrind_v: $(TARGET)
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -v $(EXECUTABLE)

$(TARGET)/obj/%.o: $(TARGET)/src/%.cpp
	@mkdir -p $(dir $@) -m 775
	@$(GCC) -c $(CFLAGS) $< -o $@
