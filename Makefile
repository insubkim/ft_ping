
# ---------------------------------- NAME ------------------------------------ #

NAME = ft_ping

# ------------------------------- DIRECTORIES -------------------------------- #

HDRS_DIR	= mandatory/headers/
SRCS_DIR	= mandatory/sources/
OBJS_DIR	= objects/
BONUS_HDRS_DIR = bonus/headers/
BONUS_SRCS_DIR	= bonus/sources/
BONUS_OBJS_DIR	= objects/

# ---------------------------------- FILES ----------------------------------- #

INCLUDE = -I $(HDRS_DIR)
SRCS = $(wildcard $(SRCS_DIR)*.c)
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

BONUS_INCLUDE = -I $(BONUS_HDRS_DIR)
BONUS_SRCS = $(wildcard $(BONUS_SRCS_DIR)*.c)
BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR), $(notdir $(BONUS_SRCS:.c=.o)))

# -------------------------------- COMPILATE --------------------------------- #

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g
# -g -fsanitize=address
RM		= rm -rf
MD		= mkdir -p 

# --------------------------------- RULES ------------------------------------ #

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS_DIR)*.h
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BONUS_OBJS_DIR)%.o : $(BONUS_SRCS_DIR)%.c $(BONUS_HDRS_DIR)*.h
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(BONUS_INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): | MAKE_MAN

bonus: | MAKE_BONUS

MAKE_MAN: $(HDRS_DIR)*.h $(OBJS)
		touch MAKE_MAN
		rm -f MAKE_BONUS
		cc $(OBJS) $(CFLAGS) -o $(NAME)
		
MAKE_BONUS: $(BONUS_HDRS_DIR)*.h $(BONUS_OBJS) 
		touch MAKE_BONUS
		rm -f MAKE_MAN
		cc $(BONUS_OBJS) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS_DIR) $(BONUS_OBJS_DIR)
	$(RM) MAKE_MAN MAKE_BONUS

fclean: clean
	$(RM) $(NAME) 

re: 
	make fclean 
	make all

.PHONY:		all clean fclean re bonus