CXX = c++
CXXFLAGS = -std=c++20 -Wall -Wextra -pthread

NAME = priority_queue

all: $(NAME)

$(NAME): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -lgtest -lgtest_main -o $(NAME)

run:
	./$(NAME)

clean:
	rm -f $(NAME)
