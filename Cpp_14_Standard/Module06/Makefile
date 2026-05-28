CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++14

NAME = custom_deleter

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)
FILENAME = test.txt

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(FILENAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
