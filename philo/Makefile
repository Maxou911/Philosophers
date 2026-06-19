# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 13:53:23 by maalwis           #+#    #+#              #
#    Updated: 2026/06/19 16:02:49 by maalwis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# TSAN_LDFLAGS = -fsanitize=thread
# LDFLAGS = -lpthread
OBJ_DIR = Object_files

GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \033[1;93m
BLUE = \033[1;96m
RESET = \033[0m

SRC = \
	routine/routine.c \
	routine/routine_functions.c \
	routine/routine_utils.c \
	monitoring/time.c \
	monitoring/monitoring.c \
	main/utils.c \
	main/check_errors.c \
	main/init_data.c \
	main/main.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(OBJ_DIR) $(NAME)
	@printf " $(GREEN)✅ Compilation terminée avec succès$(RESET)\n"

$(NAME): $(OBJ)
	@printf " $(BLUE)🔗 Compilation avec ThreadSanitizer$(RESET)\n"
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(TSAN_LDFLAGS) $(LDFLAGS)
	@printf " $(GREEN)🎯 Exécutable $(NAME) créé$(RESET)\n"

normal: $(OBJ)
	@printf " $(BLUE)🔗 Compilation normale$(RESET)\n"
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LDFLAGS)
	@printf " $(GREEN)🎯 Exécutable $(NAME) créé$(RESET)\n"

$(OBJ_DIR):
	@printf " $(YELLOW)📁 Création des dossiers objets$(RESET)\n"
	@mkdir -p $(OBJ_DIR)/main
	@mkdir -p $(OBJ_DIR)/monitoring
	@mkdir -p $(OBJ_DIR)/routine

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf " $(YELLOW)🧹 Nettoyage des fichiers objets$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf " $(GREEN)✨ Nettoyage terminé$(RESET)\n"

fclean: clean
	@printf " $(RED)🗑️ Suppression des exécutables$(RESET)\n"
	@rm -f $(NAME) $(NAME)_tsan $(NAME)_valgrind
	@printf " $(GREEN)🧽 Nettoyage complet terminé$(RESET)\n"

re: fclean all
	@printf " $(BLUE)🔄 Recompilation terminée$(RESET)\n"

.PHONY: all normal tsan valgrind clean fclean re
