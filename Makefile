# Define the compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/include/SDL2 -D_REENTRANT

# Define the source files and executable
SRCS = main.cpp Sprite.cpp Utils.cpp SDLManager.cpp Constants.cpp
OBJS = $(SRCS:.cpp=.o)
EXE = game

# Build the executable
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) -lSDL2 -lSDL2_image

# Build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(EXE)
