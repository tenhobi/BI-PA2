### Variables

CXX=g++
CXXFLAGS=-std=c++11 -W -Wall -Wextra -pedantic
EXECUTABLE=program.out
SOURCEDIR=src/
SOURCES=$(shell find $(SOURCEDIR) -name "*.cpp")

## Colors

COLOR_DEFAULT=\033[0m
COLOR_STATUS=\033[1;33m
COLOR_INFO=\033[1;36m
COLOR_GOOD=\033[1;32m

### Tasks

.PHONY: all build rebuild clean run runclean rundirect doc

all: run

%.o: %.cpp
	@echo "$(COLOR_STATUS)$^ -> $@$(COLOR_DEFAULT)"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

build: $(SOURCES:.cpp=.o)
	@echo "$(COLOR_INFO)compiling with flags $(COLOR_DEFAULT)$(CXXFLAGS)"
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE)
	@echo "$(COLOR_GOOD)BUILD OK$(COLOR_DEFAULT)"

rebuild: clean build

clean:
	@echo "$(COLOR_INFO)removing object files$(COLOR_DEFAULT)"
	$(shell find $(SOURCEDIR) -type f -name "*.o" -exec rm {} \;)
	@echo "$(COLOR_INFO)removing executable files$(COLOR_DEFAULT)"
	@rm -f $(EXECUTABLE)
	@echo "$(COLOR_GOOD)CLEAN OK$(COLOR_DEFAULT)"

run: build
	@echo "$(COLOR_INFO)starting executable$(COLOR_DEFAULT)"
	@./$(EXECUTABLE)
	@echo "$(COLOR_GOOD)EXECUTABLE OK$(COLOR_DEFAULT)"

runclean: rebuild run

rundirect: 
	@./$(EXECUTABLE)

doc:
	@echo "$(COLOR_INFO)generating documentation$(COLOR_DEFAULT)"
	@echo "$(COLOR_GOOD)DOC OK$(COLOR_DEFAULT)"
