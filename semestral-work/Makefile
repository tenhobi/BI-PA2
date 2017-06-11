.PHONY: all compile run check doc clean
.DEFAULT_GOAL = all

## Variables

CXX = g++
CXXFLAGS = -std=c++11 -Werror -Wall -pedantic -Wno-long-long -O0 -ggdb
LDFLAGS = -lncurses
EXECUTABLE = bittnja3
SOURCES := $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)
CHECK = valgrind
CHECKFLAGS = --leak-check=full --tool=memcheck

## Colors

COLOR_DEFAULT = \033[0m
COLOR_STATUS = \033[1;33m
COLOR_INFO = \033[1;36m
COLOR_GOOD = \033[1;32m

## Tasks

%.o: %.cpp
	@echo "$(COLOR_STATUS)$^ -> $@$(COLOR_DEFAULT)"
	@$(CXX) $(CXXFLAGS) -c -o $@ -c $< $(LDFLAGS)
	@$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp $(LDFLAGS) > $*.d

all: doc compile

compile: $(SOURCES:.cpp=.o)
	@echo "$(COLOR_INFO)compiling with flags $(COLOR_DEFAULT)$(CXXFLAGS) $(LDFLAGS)"
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) $(LDFLAGS)
	@echo "$(COLOR_GOOD)COMPILE OK$(COLOR_DEFAULT)"

run: compile
	@echo "$(COLOR_INFO)starting executable$(COLOR_DEFAULT)"
	@./$(EXECUTABLE)
	@echo "$(COLOR_GOOD)RUN OK$(COLOR_DEFAULT)"

clean:
	@echo "$(COLOR_INFO)removing object files$(COLOR_DEFAULT)"
	@rm -f -- src/*.o src/*/*.o src/*/*/*.o
	@echo "$(COLOR_INFO)removing link files$(COLOR_DEFAULT)"
	@rm -f -- src/*.d src/*/*.d src/*/*/*.d
	@echo "$(COLOR_INFO)removing executable files$(COLOR_DEFAULT)"
	@rm -f $(EXECUTABLE)
	@echo "$(COLOR_INFO)removing documentation files$(COLOR_DEFAULT)"
	@rm -rf -- doc/
	@echo "$(COLOR_GOOD)CLEAN OK$(COLOR_DEFAULT)"

doc:
	@echo "$(COLOR_INFO)generating documentation$(COLOR_DEFAULT)"
	doxygen Doxyfile
	@echo "$(COLOR_GOOD)DOC OK$(COLOR_DEFAULT)"

check: CXXFLAGS += -g -O2
check: clean compile
	@echo "$(COLOR_INFO)starting check in $(CHECK) with flags $(COLOR_DEFAULT)$(CHECKFLAGS)"
	$(CHECK) ./$(EXECUTABLE) $(CHECKFLAGS)
	@echo "$(COLOR_GOOD)CHECK OK$(COLOR_DEFAULT)"

help:
	@echo "Usage: $(COLOR_INFO)make$(COLOR_DEFAULT) $(COLOR_STATUS)[TARGET]$(COLOR_DEFAULT)"
	@echo
	@echo "TARGETS:"
	@echo "  $(COLOR_STATUS)all$(COLOR_DEFAULT)       create all outputs generated from source code"
	@echo "  $(COLOR_STATUS)compile$(COLOR_DEFAULT)   compiles outdated object files and creates the executable"
	@echo "  $(COLOR_STATUS)run$(COLOR_DEFAULT)       does the 'compile' task and then runs the executable file"
	@echo "  $(COLOR_STATUS)clean$(COLOR_DEFAULT)     removes all of the compiled files and executable"
	@echo "  $(COLOR_STATUS)doc$(COLOR_DEFAULT)       generates the project documentation"
	@echo "  $(COLOR_STATUS)check$(COLOR_DEFAULT)     does a clean compilation and runs check tool"
	@echo "  $(COLOR_STATUS)help$(COLOR_DEFAULT)      print this message"

## Inlude D files

-include $(SOURCES:.cpp=.d)
