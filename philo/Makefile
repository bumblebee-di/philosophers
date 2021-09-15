NAME=philo

CC= gcc
FLAGS= -g -Wall -Wextra -Werror

RED= \x1B[31m
GREEN= \033[92m
CYAN= \x1B[36m
ENDCOLOR= \x1B[0m

LIBS = -pthread

SRCS = main.c init.c routine.c utils.c libft_utils.c

OBJS = $(SRCS:.c=.o)

INCLUDES = philo.h
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LIBS) $^ -o $@
	$(RM) $(OBJS:.o=.d)
	echo "philo ${CYAN}is compiled${ENDCOLOR}"

%.o: %.c $(INCLUDES)
	$(CC) -g $(FLAGS) -MMD -c $< -o $@
-include $(OBJS:.o=.d)

bonus: ;

clean:
	$(RM) $(OBJS)
	echo "object files ${RED}are deleted${ENDCOLOR}"

fclean: clean
	$(RM) $(NAME)
	echo "philo_bonus ${RED}is deleted${ENDCOLOR}"

re: fclean
	$(MAKE) all

norm:
	-norminette ${SRCS} ${INCLUDES}

.SILENT:

.PHONY: all clean fclean re norm
