XX = g++
CXXFLAGS = -std=c++11 -Wall

# Define your source files
SRCS = main.cpp heap.cpp util.cpp

# Define object files based on source files
OBJS = $(SRCS:.cpp=.o)

# Define the executable 
EXECUTABLE = PJ2

# Default target to build the executable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(EXECUTABLE)
