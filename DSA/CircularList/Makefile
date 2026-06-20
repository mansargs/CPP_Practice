CXX = c++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror
LGTEST = -lgtest

TARGET = circular_list
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LGTEST)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
