CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -g3 \
	-I/opt/homebrew/include -I./include
LDFLAGS := -L/opt/homebrew/lib \
	-lglew -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp, src/%.o, $(SRC))
EXEC := hw7

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
