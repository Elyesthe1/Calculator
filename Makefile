CC = c++
FLAGS = -Wall -Wextra -g -std=c++17 #-fsanitize=address #-Werror 
RM = rm -f

NAME = Calculator

SRCS = srcs/main.cpp \
	   srcs/Calculator/Calculator.cpp \

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
