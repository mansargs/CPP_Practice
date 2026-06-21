CXX = c++
CXXFLAGS = -std=c++20 -Wall -Wextra

TARGET = stack

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

GTEST_LIBS = -lgtest -lgtest_main -pthread

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./$(TARGET)
