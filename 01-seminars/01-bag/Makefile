# In this project, you can use these tasks:
#
# - compile			compiles outdated object files and creates the executable
# - run				does 'compile' and then runs the executable file
# - clean			cleans all the compiled files
# ---
# - recompile		does 'clean' and then 'compile' tasks
# - runclean		does 'recompile' and then 'run' tasks
#
# some of the tasks can be modified by VALGRIND=true

## Variables

CXX := g++
CXXFLAGS := -std=c++11 -Wall -pedantic -Werror -Wextra
EXECUTABLE := program.out
SOURCEDIR := src/
SOURCES := $(shell find $(SOURCEDIR) -name "*.cpp")
VALGRIND ?= false
VALGRINDFLAGS := --leak-check=yes --tool=memcheck

ifeq ($(VALGRIND), true)
CXXFLAGS += -g -O2
endif

## Colors

COLOR_DEFAULT=\033[0m
COLOR_STATUS=\033[1;33m
COLOR_INFO=\033[1;36m
COLOR_GOOD=\033[1;32m

## Tasks

all: compile

%.o: %.cpp
	@echo "$(COLOR_STATUS)$^ -> $@$(COLOR_DEFAULT)"
	@$(CXX) $(CXXFLAGS) -c -o $@ -c $<
	@$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp > $*.d

compile: $(SOURCES:.cpp=.o)
	@echo "$(COLOR_INFO)compiling with flags $(COLOR_DEFAULT)$(CXXFLAGS)"
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE)
	@echo "$(COLOR_GOOD)COMPILE OK$(COLOR_DEFAULT)"

recompile: clean compile

clean:
	@echo "$(COLOR_INFO)removing object files$(COLOR_DEFAULT)"
	$(shell find $(SOURCEDIR) -type f -name "*.o" -exec rm {} \;)
	@echo "$(COLOR_INFO)removing executable files$(COLOR_DEFAULT)"
	@rm -f $(EXECUTABLE)
	@echo "$(COLOR_INFO)removing link files$(COLOR_DEFAULT)"
	$(shell find $(SOURCEDIR) -type f -name "*.d" -exec rm {} \;)
	@echo "$(COLOR_GOOD)CLEAN OK$(COLOR_DEFAULT)"

run: compile
ifeq ($(VALGRIND), true)
	@echo "$(COLOR_INFO)starting executable in valgrind with flags$(COLOR_DEFAULT) $(VALGRINDFLAGS)"
	@valgrind $(VALGRINDFLAGS) ./$(EXECUTABLE)
else
	@echo "$(COLOR_INFO)starting executable$(COLOR_DEFAULT)"
	@./$(EXECUTABLE)
endif
	@echo "$(COLOR_GOOD)RUN OK$(COLOR_DEFAULT)"

runclean: recompile run

doc:
	@echo "$(COLOR_INFO)generating documentation$(COLOR_DEFAULT)"
	@echo "$(COLOR_GOOD)DOC OK$(COLOR_DEFAULT)"

.PHONY: all build rebuild clean run runclean rundirect doc

-include $(SOURCES:.cpp=.d)
