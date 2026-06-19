CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = lru
SRC = main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
