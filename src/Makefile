NAME		=	startScreen
CXX			=	c++
CXXFLAGS	=	-lraylib

INC_DIR		=	./inc/
SRC_DIR		=	./src/
INC			=	-I$(INC_DIR)

SRC			=	$(SRC_DIR)main.cpp \
				$(SRC_DIR)game.cpp \
				$(SRC_DIR)menu.cpp

OBJ			=	$(SRC:.cpp=.o)
RM			=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(INC) -o $(NAME) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(INC) -c $< -o $@ $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
