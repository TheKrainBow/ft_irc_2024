SRCS			=	main.cpp				\
					channel.cpp				\
					server.cpp				\
					server_test.cpp			\
					user.cpp				\

INCLUDES		=	-Iincludes				\

OBJ_DIR			=	objs

OBJS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

LD_FLAGS		=	-O2

NAME			=	ircserv

NB_OF_FILES	=	0
FIRST_CALL	=	0
I			=	0
TMP			=	0
TMP2		=	20

CC				=	c++
RM				=	@rm -f

FLAGS			=	-Wall -Werror -Wextra $(INCLUDES) -std=c++98 -g -fsanitize=address

$(OBJ_DIR)/%.o: srcs/%.cpp
				@mkdir -p $(@D)
				@$(CC) $(FLAGS) -c $< -o $@
				@$(eval I=$(shell echo $$(($(I)+1))))
				@if [ "$(FIRST_CALL)" -eq "1" ]; then\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
				fi
				@$(eval FIRST_CALL=1)
				@if [ "$(I)" -eq "$(NB_OF_FILES)" ]; then\
					printf "╭─ ft_irc ───────────╮\n";\
					printf "│\033[0;32m████████████████████\033[0m│ %2d/%d compiled!\n" $(I) $(NB_OF_FILES);\
					printf "╰────────────────────╯\n";\
				else\
					printf "╭─ ft_irc ───────────╮\n";\
					printf "│\033[0;32m%.*s%*c\033[0m│ %2d/%d %s\n" $(TMP) "████████████████████" $(TMP2) ' ' $(I) $(NB_OF_FILES) $<;\
					printf "╰────────────────────╯\n";\
				fi
				$(eval TMP=$(shell echo $$(($(I) * 20 / $(NB_OF_FILES) * 3))))
				$(eval TMP2=$(shell echo $$((20 - $(TMP) / 3))))

$(NAME):			init $(OBJS)
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

debug:				add_debug_flag fclean init $(OBJS)
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

add_debug_flag:
					$(eval FLAGS := $(FLAGS) -D DEBUG=1)

init:
				$(eval I=$(shell echo $$(find -name "*.o" | grep srcs | wc -l)))
				$(eval NB_OF_FILES=$(shell echo $$(find -name "*.cpp" | grep srcs | wc -l)))

all:				$(NAME)

clean:
					$(RM) $(OBJS) $(OBJS_bonus)
					$(RM) -r $(OBJ_DIR)

fclean:				clean
					$(RM) $(NAME) $(Name_B)
					$(RM) -r $(OBJ_DIR)

re:					fclean all
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

bonus:			all

.PHONY:				all clean fclean re