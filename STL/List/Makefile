CXX = c++
CXXFLAGS = -std=c++20 -Wall -Wextra

TARGET = list

SRC = main.cpp

LIBS = -lgtest -lgtest_main -pthread

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
