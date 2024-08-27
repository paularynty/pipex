# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 12:05:04 by prynty            #+#    #+#              #
#    Updated: 2024/08/27 14:25:31 by prynty           ###   ########.fr        #
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
GREEN			= \033[1;92m
BLUE 			= \033[0;94m
BLUE_BOLD 		= \033[1;94m
CYAN 			= \033[0;96m
CYAN_BOLD 		= \033[1;96m
MAGENTA 		= \033[1;95m
PINK			= \e[1m\e[38;5;212m
WHITE 			= \033[1;97m

OBJ_READY		= echo "📥 $(ORANGE)Compiled pipex files!$(RESET)"
COMP_LIBFT		= echo "\n📝 $(YELLOW)Compiling Libft...$(RESET)$(DARK_GRAY)"
PIP_READY		= echo "\n🧮 $(GREEN)pipex ready!$(RESET)"
CLEANING		= echo "\n💧 $(CYAN)Cleaning...$(RESET)$(DARK_GRAY)"
CLEANED			= echo "💧$(CYAN_BOLD)Successfully cleaned all object files!$(RESET)"
FCLEANING		= echo "\n🧼 $(BLUE)Deep cleaning...$(RESET)$(DARK_GRAY)"
FCLEANED		= echo "🧼 $(BLUE_BOLD)Successfully cleaned all executable files!$(RESET)"
REMAKE			= echo "✅ $(GREEN)Successfully cleaned and rebuilt everything!$(RESET)"

NAME			= pipex
CFLAGS			= -Wall -Wextra -Werror
LIBFT			= ./libft/libft.a

FILES 			= pipex.c \

SRCS			= $(addprefix srcs/, $(FILES))
OBJS			= $(addprefix objs/, $(FILES:.c=.o))

all: $(NAME)

objs:
	@mkdir -p objs/
	@mkdir -p libft/objs/

objs/%.o: srcs/%.c | objs
	@cc $(FLAGS) -c $< -o $@ && echo "$(DARK_GRAY)Compiled: $@ $(RESET)"

$(NAME): $(OBJS)
	@$(OBJ_READY)
	@$(COMP_LIBFT)
	@make -C ./libft
	@cp $(LIBFT) .
	@cc -g $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	@chmod 777 $(NAME)
	@$(SL_READY)

comp_libft:
	$(COMP_LIBFT)
	@make -C ./libft

clean:
	@$(CLEANING)
	@rm -rf $(OBJS)
	@rm -rf objs/
	@cd libft && make clean
	@$(CLEANED)

fclean: clean
	@$(FCLEANING)
	@rm -rf $(NAME)
	@cd libft && make fclean
	@rm -rf libft.a
	@$(FCLEANED)

re:	fclean all
	@$(REMAKE)

.PHONY: all clean fclean re libft
