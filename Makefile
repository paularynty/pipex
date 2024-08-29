# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 12:05:04 by prynty            #+#    #+#              #
#    Updated: 2024/08/29 18:42:51 by prynty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET 			= \033[0;39m
BLACK			= \033[1;30m
DARK_RED		= \033[1;31m
DARK_GREEN		= \033[1;32m
DARK_YELLOW		= \033[1;33m
DARK_BLUE		= \033[1;34m
DARK_MAGENTA	= \033[1;35m
DARK_CYAN		= \033[1;36m
DARK_GRAY		= \033[0;90m
LIGHT_GRAY		= \033[1;37m
RED				= \033[1;91m
ORANGE 			= \e[1m\e[38;5;202m
YELLOW 			= \033[0;93m
YELLOW_BOLD		= \033[1;93m
GREEN			= \033[1;92m
BLUE 			= \033[0;94m
BLUE_BOLD 		= \033[1;94m
CYAN 			= \033[0;96m
CYAN_BOLD 		= \033[1;96m
MAGENTA 		= \033[1;95m
PINK			= \e[1m\e[38;5;212m
WHITE 			= \033[1;97m

OBJ_READY		= echo "📥 $(ORANGE)Compiled pipex files!$(RESET)"
COMP_LIBFT		= echo "📝 $(YELLOW)Compiling Libft...$(RESET)"
LIBFT_READY		= echo "📝 $(YELLOW_BOLD)Libft compiled!$(RESET)"
PIP_READY		= echo "🧮 $(GREEN)pipex ready!$(RESET)"
CLEANING		= echo "💧 $(CYAN)Cleaning...$(RESET)"
CLEANED			= echo "💧 $(CYAN_BOLD)Successfully cleaned all object files!$(RESET)"
FCLEANING		= echo "🧼 $(BLUE)Deep cleaning...$(RESET)"
FCLEANED		= echo "🧼 $(BLUE_BOLD)Successfully cleaned all executable files!$(RESET)"
REMAKE			= echo "✅ $(GREEN)Successfully cleaned and rebuilt everything!$(RESET)"

NAME			= pipex
CFLAGS			= -Wall -Wextra -Werror
LIBFT			= ./libft/libft.a

FILES			= 	pipex.c \
					utils.c \

SRCS			= $(addprefix srcs/, $(FILES))
OBJS			= $(addprefix objs/, $(FILES:.c=.o))

all: $(NAME)

objs:
	@mkdir -p objs/
	@mkdir -p libft/objs/

objs/%.o: srcs/%.c | objs
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(COMP_LIBFT)
	@make -s -C ./libft > /dev/null
	@cp $(LIBFT) .
	@$(LIBFT_READY)
	@$(OBJ_READY)
	@cc -g $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	@chmod 777 $(NAME)
	@$(PIP_READY)

clean:
	@$(CLEANING)
	@rm -rf $(OBJS)
	@rm -rf objs/
	@make clean -s -C libft
	@$(CLEANED)

fclean: clean
	@$(FCLEANING)
	@rm -rf $(NAME)
	@make fclean -s -C libft
	@rm -rf libft.a
	@$(FCLEANED)

re:	fclean all
	@$(REMAKE)

.PHONY: all clean fclean re libft
