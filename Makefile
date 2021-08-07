#first parts 
SRC :=	main.c src/ft_exit.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		src/pipex_utils.c src/ft_path.c 

#bonnus 
BSRC :=	src/ft_exit.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		src/pipex_utils.c src/ft_path.c src/ft_proc.c main_bonus.c

CC = gcc

FLGS = -Wall -Werror -Wextra
FBSIZE =	-D BUFFER_SIZE=42

HEADER = pipex.h
LIBFT = libft/libft.a

NAME = pipex


all :$(NAME)
	
$(NAME): $(SRC) $(HEADER) $(LIBFT)
	@echo "compiling ..."
	@$(CC) $(FLGS) $(FBSIZE) $(SRC) $(LIBFT) -o $(NAME)

bonus: $(BSRC) $(HEADER) $(LIBFT)
	@echo "compiling bonus ..."
	@rm -f $(NAME)
	@$(CC) $(FLGS) $(FBSIZE) $(BSRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft/
	@make bonus -C libft/

so:
	@echo "clreating .so file ..."
	@$(CC) -fPIC $(CFLAGS) -c $(SRC)
	@gcc -shared -o $(NAMESO) $(OBJ)


clean:
	@echo "cleaning all objects"
	@make clean -C libft/

fclean: clean
	@echo "cleaning every thing ..."
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

test:
	@make -C libft/
	@$(CC) test.c $(FBSIZE) $(BSRC) libft/libft.a  -o tst

.PHONY: all clean fclean bonus so re test

#&.c : &.o libft.a 