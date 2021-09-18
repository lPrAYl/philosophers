NAME					=	philo
NAME_BONUS				=	philo_bonus

GCC						=	gcc -Wall -Wextra -Werror
INCLUDES				=	-I$(HEADERS_DIRECTORY)
INCLUDES_BONUS			=	-I$(HEADERS_DIRECTORY)

HEADERS_LIST			=	philo.h
HEADERS_BONUS_LIST		=	philo_bonus.h
HEADERS_DIRECTORY		= 	./includes/
HEADERS_DIRECTORY_BONUS	=	./includes/
HEADERS					=	$(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))
HEADERS_BONUS			=	$(addprefix $(HEADERS_DIRECTORY_BONUS), $(HEADERS_BONUS_LIST))

SOURCES_LIST			=	philo.c		basis.c		actions.c	utils.c		time.c
SOURCES_DIRECTORY		=	./sources/
SOURCES_LIST_BONUS		=	philo.c		basis.c		actions.c	utils.c		time.c
SOURCES_DIRECTORY_BONUS	=	./bonus/
SOURCES					=	$(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
SOURCES_BONUS			=	$(addprefix $(SOURCES_DIRECTORY_BONUS), $(SOURCES_LIST_BONUS))

OBJECTS_LIST			=	$(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS_DIRECTORY		=	./sources/objects/
OBJECTS					=	$(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))
OBJECTS_LIST_BONUS		=	$(patsubst %.c, %.o, $(SOURCES_LIST_BONUS))
OBJECTS_DIRECTORY_BONUS	=	./bonus/objects/
OBJECTS_BONUS			=	$(addprefix $(OBJECTS_DIRECTORY_BONUS), $(OBJECTS_LIST_BONUS))

#COLORS
GREEN					=	\033[0;32m
RED						=	\033[0;31m
RESET					=	\033[0m

all						:	$(NAME)

$(NAME)					:	$(OBJECTS_DIRECTORY) $(OBJECTS) $(HEADER)
							@$(GCC) $(INCLUDES) $(OBJECTS) -pthread -o $(NAME)
							@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
							@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY)	:
							@mkdir -p $(OBJECTS_DIRECTORY)
							@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o	:	$(SOURCES_DIRECTORY)%.c $(HEADERS)
							@$(GCC) -c $(INCLUDES) $< -o $@
							@echo "$(GREEN).$(RESET)\c"

bonus					:	$(NAME_BONUS)

$(NAME_BONUS)			:	$(OBJECTS_DIRECTORY_BONUS) $(OBJECTS_BONUS) $(HEADERS_BONUS)
							@$(GCC) $(INCLUDES_BONUS) $(OBJECTS_BONUS) -pthread -o $(NAME_BONUS)
							@echo "\n$(NAME_BONUS): $(GREEN)object files were created$(RESET)"
							@echo "$(NAME_BONUS): $(GREEN)$(NAME_BONUS) was created$(RESET)"

$(OBJECTS_DIRECTORY_BONUS)		:
							@mkdir -p $(OBJECTS_DIRECTORY_BONUS)
							@echo "$(NAME_BONUS): $(GREEN)$(OBJECTS_DIRECTORY_BONUS) was created$(RESET)"

$(OBJECTS_DIRECTORY_BONUS)%.o	:	$(SOURCES_DIRECTORY_BONUS)%.c $(HEADERS_BONUS)
							@$(CC) $(FLAGS) -c $(INCLUDES_BONUS) $< -o $@
							@echo "$(GREEN).$(RESET)\c"

clean					:
							@rm -rf $(OBJECTS_DIRECTORY)
							@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
							@echo "$(NAME): $(RED)object files were deleted$(RESET)"
							@rm -rf $(OBJECTS_DIRECTORY_BONUS)
							@echo "$(NAME_BONUS): $(RED)$(OBJECTS_DIRECTORY_BONUS) was deleted$(RESET)"
							@echo "$(NAME_BONUS): $(RED)object files were deleted$(RESET)"

fclean					:	clean
							@rm -f $(NAME)
							@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
							@rm -f $(NAME_BONUS)
							@echo "$(NAME_BONUS): $(RED)$(NAME_BONUS) was deleted$(RESET)"
	
re						:	fclean all

norm					:
							@echo "\033[46m\033[30mNORMINETTE$(RESET)";
							norminette *.h *.c;

.PHONY					:	all clean fclean re	bonus	norm