# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffons-ti <ffons-ti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 19:24:41 by ffons-ti          #+#    #+#              #
#    Updated: 2023/08/27 15:20:28 by ffons-ti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRC_FILES		= time utils routine main data table talk end eat reaper

SRC_DIR			= srcs/
OBJ_DIR			= objs/
INCLUDE			= include/

CC				= gcc
RM				= rm -f
CFLAGS			= -pthread -Wall -Werror -Wextra -I$(INCLUDE) #-fsanitize=address #-fsanitize=thread #-O3 #-Ofast

SRC 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

$(NAME)			:	$(OBJ)
					@$(CC) $(CFLAGS) $^ -o $@
					@echo "Program Created"

all:				$(NAME)


$(OBJ_DIR)%.o	: 	$(SRC_DIR)%.c
					@mkdir -p $(OBJ_DIR)
					@$(CC) $(CFLAGS) -o $@ -c $^

clean:
	@echo "Clean Boys!"
	@$(RM) ${OBJ}
	@${RM} -r ${OBJ_DIR} 

fclean: clean
	@echo "Super Clean Boys!"
	@${RM} ${OBJS} ${NAME}

re: fclean all

norm:          
		@norminette $(INCLUDE) $(LIBFT_DIR) $(SRC_DIR) $(B_DIR)| grep -v Norme -B1 || true

.PHONY: all clean fclean re norm bonus re-all re-bonus