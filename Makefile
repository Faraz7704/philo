# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 11:40:15 by fkhan             #+#    #+#              #
#    Updated: 2022/09/15 20:21:03 by fkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= philo
BONUS 				= philo_bonus
CC 					= gcc
FLAGS 				= -Wall -Werror -Wextra
INCLUDES 			= -I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY 	= ./includes/
HEADERS_LIST 		= philo.h philo_bonus.h
HEADERS 			= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY 	= ./sources/
SOURCES_LIST 		= philo.c
SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY 	= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

BSOURCES_LIST 		= philo_bonus.c
BSOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(BSOURCES_LIST))

BOBJECTS_LIST 		= $(patsubst %.c, %.o, $(BSOURCES_LIST))
BOBJECTS			= $(addprefix $(OBJECTS_DIRECTORY), $(BOBJECTS_LIST))

# COLORS
GREEN 				= \033[0;32m
RED 				= \033[0;31m
RESET 				= \033[0m

all: $(NAME) $(BONUS)

bonus: $(BONUS)

$(BONUS) : $(OBJECTS_DIRECTORY) $(BOBJECTS)
	@$(CC) $(FLAGS) $(BOBJECTS) $(INCLUDES) -o $(BONUS)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(BONUS) was created$(RESET)"

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(INCLUDES) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo ".\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@rm -f $(BONUS)
	@echo "$(NAME): $(RED)$(BONUS) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all bonus clean fclean re