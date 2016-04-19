# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdaudre- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/07/15 15:13:38 by fdaudre-          #+#    #+#              #
#    Updated: 2016/01/07 15:33:44 by fdaudre-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

# Sources
SRCDIR		=	src
SRC		=	display_2048.c	\
			error_2048.c	\
			game_2048.c	\
			get_choice.c	\
			grid_init.c	\
			grid_rand.c	\
			grid_status.c	\
			main_2048.c	\
			menu_2048.c	\
			sig_resize.c	\
			swipe.c

# Objects
OBJDIR		=	obj

# Includes
CPPFLAGS	=	-Iinc

# Libraries
LDFLAGS		=	
LDLIBS		=	-lncurses

# Output
NAME		=	2048

# Compiler
CFLAGS		=	-Werror -Wall -Wextra -pedantic


#################
##  AUTO       ##
#################

OBJ		=	$(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
NORME		=	**/*.[ch]
VPATH		+=	$(dir $(addprefix $(SRCDIR)/,$(SRC)))

disp_indent	=	for I in `seq 1 $(MAKELEVEL)`; do \
				test "$(MAKELEVEL)" '!=' '0' && printf "\t"; \
			done
color_exec	=	$(call disp_indent); \
			echo "\033["$(1)"m➤"$(3)"\033["$(2)"m";$(3) && printf "\033[0m"


#################
##  TARGETS    ##
#################

# First target
all: $(NAME)

# Linking
$(NAME): $(OBJ)
	@$(call color_exec,32,31,\
		$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^)

# Objects compilation
$(OBJDIR)/%.o: %.c
	@mkdir $(OBJDIR) 2> /dev/null || true
	@$(call color_exec,36,31,\
		$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<)

# Removing objects
clean:
	@$(call color_exec,33,31,\
		$(RM) $(OBJ))
	@rmdir $(OBJDIR) 2> /dev/null || true

# Removing objects and exe
fclean: clean
	@$(call color_exec,33,31,\
		$(RM) $(NAME))

# All removing then compiling
re: fclean all

.PHONY: all clean fclean re

