NAME = philo
CFILES = philosophers.c philosophers_init.c philosophers_utils.c simulation.c simulation_routine.c simulation_utils.c simulation_time_utils.c simulation_supervisor.c
OBJ_DIR = obj
OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))
CC = cc
CFLAGS = -Wall -Werror -Wextra

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
RESET = \033[0m

TOTAL_FILES = $(words $(CFILES))
COMPILED_FILES = 0

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	@echo "${YELLOW}[$$(($(COMPILED_FILES)*100/$(TOTAL_FILES)))%]${RESET}		${GREEN}Compiled${RESET} $< ${GREEN}with flags${RESET} $(CFLAGS)"

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $(CFILES) -o $(NAME)
	@echo "${YELLOW}[COMPLETED]${RESET}	${GREEN}Created executable${RESET} $(NAME)"

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${RED}Deleted directory${RESET} $(OBJ_DIR) ${RED}containing${RESET} $(CFILES:.c=.o)"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}Deleted executable${RESET} $(NAME)"

re: fclean $(NAME)

.PHONY: all clean fclean re
