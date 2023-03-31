SRC_DIR := src
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
HPP_FILES := $(wildcard $(SRC_DIR)/*.hpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=
CC_FLAGS := -Wall -Wextra -pedantic -std=c++17
UT_FLAGS := -I googletest/googletest/include 
GTEST_LIB := googletest/build/lib/libgtest.a -lpthread

EXECUTABLE := my_program

all: $(EXECUTABLE) ut

$(EXECUTABLE): $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: $(SRC_DIR)/%.cpp $(HPP_FILES)
	g++ $(CC_FLAGS) -c -o $@ $<

ut: uts/ut.cpp $(CPP_FILES) $(HPP_FILES)
	g++ $(CC_FLAGS) $(UT_FLAGS) -o $@ $< $(GTEST_LIB)

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) $(OBJ_FILES) ut
