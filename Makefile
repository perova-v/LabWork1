PROJECT = labwork1
TESTPROJECT = runTests

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -fsanitize=address
LDGTESTFLAGS = $(LDFLAGS) -lgtest -lgtest_main -lpthread

SRC_COMMON = BmpImage.cpp
SRC_MAIN = Main.cpp
SRC_TEST = tests.cpp

OBJ_COMMON = $(SRC_COMMON:.cpp=.o)
OBJ_MAIN = $(SRC_MAIN:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)

.PHONY: all clean test format

all: $(PROJECT)

$(PROJECT): $(OBJ_COMMON) $(OBJ_MAIN)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(TESTPROJECT): $(OBJ_COMMON) $(OBJ_TEST)
	$(CXX) -o $@ $^ $(LDGTESTFLAGS)

test: $(TESTPROJECT)
	./$(TESTPROJECT)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

format:
	astyle -A1 -s4 *.cpp *.h

clean:
	rm -f *.o $(PROJECT) $(TESTPROJECT) *.orig
