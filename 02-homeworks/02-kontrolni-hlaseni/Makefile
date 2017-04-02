.DEFAULT_GOAL := help
.PHONY: all compile run check doc clean

## Variables

CXX := g++
CXXFLAGS := -std=c++11 -Wall -pedantic -Werror -Wextra
EXECUTABLE := program.out
SOURCEDIR := src/
SOURCES := $(shell find $(SOURCEDIR) -name "*.cpp")
CHECK := valgrind
CHECKFLAGS := --leak-check=yes --tool=memcheck

## Colors

COLOR_DEFAULT=\033[0m
COLOR_STATUS=\033[1;33m
COLOR_INFO=\033[1;36m
COLOR_GOOD=\033[1;32m

## Tasks

%.o: %.cpp
	@echo "$(COLOR_STATUS)$^ -> $@$(COLOR_DEFAULT)"
	@$(CXX) $(CXXFLAGS) -c -o $@ -c $<
	@$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp > $*.d

compile: $(SOURCES:.cpp=.o)
	@echo "$(COLOR_INFO)compiling with flags $(COLOR_DEFAULT)$(CXXFLAGS)"
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE)
	@echo "$(COLOR_GOOD)COMPILE OK$(COLOR_DEFAULT)"

run: compile
	@echo "$(COLOR_INFO)starting executable$(COLOR_DEFAULT)"
	@./$(EXECUTABLE)
	@echo "$(COLOR_GOOD)RUN OK$(COLOR_DEFAULT)"

check: clean compile
	@echo "$(COLOR_INFO)starting check in $(CHECK) with flags$(COLOR_DEFAULT) $(CHECKFLAGS)"
	$(CHECK) ./$(EXECUTABLE) $(CHECKFLAGS)
	@echo "$(COLOR_GOOD)CHECK OK$(COLOR_DEFAULT)"

doc:
	@echo "$(COLOR_INFO)generating documentation$(COLOR_DEFAULT)"
	@echo "$(COLOR_GOOD)DOC OK$(COLOR_DEFAULT)"

clean:
	@echo "$(COLOR_INFO)removing object files$(COLOR_DEFAULT)"
	$(shell find $(SOURCEDIR) -type f -name "*.o" -exec rm {} \;)
	@echo "$(COLOR_INFO)removing executable files$(COLOR_DEFAULT)"
	@rm -f $(EXECUTABLE)
	@echo "$(COLOR_INFO)removing link files$(COLOR_DEFAULT)"
	$(shell find $(SOURCEDIR) -type f -name "*.d" -exec rm {} \;)
	@echo "$(COLOR_GOOD)CLEAN OK$(COLOR_DEFAULT)"

help:
	@echo "Usage: $(COLOR_INFO)make$(COLOR_DEFAULT) $(COLOR_STATUS)[TARGET]$(COLOR_DEFAULT)"
	@echo
	@echo "TARGETS:"
	@echo "  $(COLOR_STATUS)compile$(COLOR_DEFAULT)   compiles outdated object files and creates the executable"
	@echo "  $(COLOR_STATUS)run$(COLOR_DEFAULT)       does the 'compile' task and then runs the executable file"
	@echo "  $(COLOR_STATUS)check$(COLOR_DEFAULT)     does a clean compilation and runs check tool"
	@echo "  $(COLOR_STATUS)doc$(COLOR_DEFAULT)       generates the project documentation"
	@echo "  $(COLOR_STATUS)clean$(COLOR_DEFAULT)     removes all of the compiled files and executable"
	@echo "  $(COLOR_STATUS)help$(COLOR_DEFAULT)      print this message"

-include $(SOURCES:.cpp=.d)
