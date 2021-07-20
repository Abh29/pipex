#first parts 
SRC :=	src/ft_exit.c gnl/get_next_line.c gnl/get_next_line_utils.c

#bonnus 
BSRC := ft_lstnew.c 	ft_lstadd_front.c 	ft_lstsize.c 	\
		ft_lstlast.c 	ft_lstadd_back.c 	ft_lstdelone.c 	\
		ft_lstclear.c	ft_lstiter.c		ft_lstmap.c

OBJ := ${SRC:%.c=%.o}

BOBJ := $(BSRC:%.c=%.o)

CC = gcc

FLGS = -Wall -Werror -Wextra -D BUFFER_SIZE=42

HEADER = pipex.h

NAME = pipex



%.o : %.c
	@echo "compiling ..."
	$(CC) $(FLGS) -c $<

all :$(NAME)
	
$(NAME): $(OBJ)
	@echo "linking ..."
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

bonus: $(BOBJ)
	@echo "linking with bonus ..."
	@ar rc $(NAME) $(BOBJ)
	@ranlib $(NAME)

so:
	@echo "clreating .so file ..."
	@$(CC) -fPIC $(CFLAGS) -c $(SRC)
	@gcc -shared -o $(NAMESO) $(OBJ)


clean:
	@echo "cleaning all objects"
	@rm -f $(OBJ)
	@rm -f $(BOBJ)

fclean: clean
	@echo "cleaning every thing ..."
	@rm -f $(NAME)
	@rm -f $(NAMESO)

re: fclean all

.PHONY: all clean fclean bonus so re

#&.c : &.o libft.a 