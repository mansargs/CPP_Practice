NAME = huffman_encoding

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

SRC = main.cpp HuffmanEncoding.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp HuffmanEncoding.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
