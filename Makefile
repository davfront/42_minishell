# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 07:13:52 by dapereir          #+#    #+#              #
#    Updated: 2023/03/21 07:13:52 by dapereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# COLORS

RED					=	\033[0;31m
RED_BOLD			=	\033[1;31m
GREEN				=	\033[0;32m
GREEN_BOLD			=	\033[1;32m
YELLOW				=	\033[0;33m
YELLOW_BOLD			=	\033[1;33m
CYAN				=	\033[0;36m
CYAN_BOLD			=	\033[1;36m
BOLD				=	\033[1m
FAINT				=	\033[2m
EOC					=	\033[0m


# COMMANDS

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf

SILENTFLAG			= 	$(if $(filter s, $(MAKEFLAGS)),1,0)
ifeq ($(SILENTFLAG),1)
ECHO				=	\#
else
ECHO				=	echo
endif


# PROJECT

NAME				=	minishell

SRCS_DIR			=	./src
OBJS_DIR			=	./obj

SRCS_FILES			=	\
						utils/ms_print_quoted.c\
						utils/ms_strs_len.c\
						utils/ms_str_is_llong.c\
						utils/ms_str_to_llong.c\
						utils/ms_error.c\
						utils/ms_exit.c\
						utils/ms_init.c\
						utils/ms_reset.c\
						\
						env/ms_env_new.c\
						env/ms_env_from_char.c\
						env/ms_env_delete.c\
						env/ms_env_list_add.c\
						env/ms_env_list_init.c\
						env/ms_env_list_clear.c\
						env/ms_env_list_find.c\
						env/ms_env_list_delete.c\
						env/ms_env_is_valid_identifier.c\
						env/ms_env_list_update.c\
						env/ms_env_list_get.c\
						env/ms_env_list_set.c\
						env/ms_env_list_unset.c\
						\
						builtin/ms_builtin_pwd.c\
						builtin/ms_builtin_echo.c\
						builtin/ms_builtin_env.c\
						builtin/ms_builtin_unset.c\
						builtin/ms_builtin_export.c\
						builtin/ms_builtin_cd.c\
						builtin/ms_builtin_exit.c\
						builtin/ms_is_builtin_cmd.c\
						builtin/ms_builtin_cmd.c\
						\
						parsing/ms_parser.c\
						parsing/ms_parser_utils.c\
						parsing/ms_cmdsplit.c\
						parsing/ms_expand_var.c\
						parsing/ms_expand_var_utils.c\
						parsing/ms_var_array.c\
						\
						main.c\

SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

HEADER_DIR			=	./include
HEADER				=	$(HEADER_DIR)/minishell.h
HEADER_INC			=	-I $(HEADER_DIR)

FT_DIR				=	./libft
FT					=	$(FT_DIR)/libft.a
FT_INC				=	-I $(FT_DIR)/include
FT_FLAGS			=	-L $(FT_DIR) -l ft

.PHONY: all
all:				$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c Makefile $(FT) $(HEADER)
					@mkdir -p $(@D)
					@$(ECHO) "$(GREEN)[create]$(EOC) $@"
					@$(CC) $(CFLAGS) $(HEADER_INC) $(FT_INC) -c $< -o $@

$(NAME):			$(OBJS) $(FT)
					@$(ECHO) "$(GREEN)[create]$(EOC) $@"
					@$(CC) $(CFLAGS) $(OBJS) $(FT_FLAGS) -lreadline -o $(NAME)
					@$(ECHO) "$(GREEN_BOLD)✓ $(NAME) is ready!$(EOC)"

.PHONY: libft
libft:
					@$(ECHO) "$(CYAN)[libft]$(EOC) Enter directory"
					@$(MAKE) --no-print-directory -C $(FT_DIR) | sed "s/^make\[[0-9]\]: //;s/^/\x1b[36m[libft]\x1b[0m /"
					@$(ECHO) "$(CYAN)[libft]$(EOC) Leave directory"

$(FT):				libft

.PHONY: clean
clean:
					@$(ECHO) "$(RED)[delete]$(EOC) $(OBJS_DIR)"
					@$(RM) $(OBJS_DIR)
					@$(ECHO) "$(RED)[delete]$(EOC) $(FT_DIR)"
					@$(MAKE) --no-print-directory -s -C $(FT_DIR) clean

.PHONY: fclean
fclean:				clean
					@$(ECHO) "$(RED)[delete]$(EOC) $(FT)"
					@$(MAKE) --no-print-directory -s -C $(FT_DIR) fclean
					@$(ECHO) "$(RED)[delete]$(EOC) $(NAME)"
					@$(RM) $(NAME)
					@$(ECHO) "$(RED_BOLD)✓ $(NAME) is fully cleaned!$(EOC)"

.PHONY: re
re:					fclean
					@$(MAKE) --no-print-directory all
