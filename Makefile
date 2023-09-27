CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
INCLUDES := -Icommon -Icli -Istorage -Ivar -I buffer

SRCDIR := common cli storage var buffer
SOURCES := $(wildcard $(addsuffix /*.cpp, $(SRCDIR)))
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

EXECUTABLE := unloadkv

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)