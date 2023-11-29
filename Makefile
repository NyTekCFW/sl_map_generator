NAME = sl_map_generator
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I. -Iincludes

OBJ_DIR = obj
SRC_DIR = src

INCLUDE_DIR = includes/

# Styles de texte
COLOR_RESET = \033[0m
COLOR_BOLD = \033[1m
COLOR_DIM = \033[2m
COLOR_UNDERLINE = \033[4m
COLOR_BLINK = \033[5m
COLOR_REVERSE = \033[7m
COLOR_HIDDEN = \033[8m

# Couleurs du texte (texte / fond)
COLOR_BLACK = \033[30m
COLOR_RED = \033[31m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m
COLOR_BLUE = \033[34m
COLOR_MAGENTA = \033[35m
COLOR_CYAN = \033[36m
COLOR_WHITE = \033[37m

# Couleurs de fond
COLOR_BG_BLACK = \033[40m
COLOR_BG_RED = \033[41m
COLOR_BG_GREEN = \033[42m
COLOR_BG_YELLOW = \033[43m
COLOR_BG_BLUE = \033[44m
COLOR_BG_MAGENTA = \033[45m
COLOR_BG_CYAN = \033[46m
COLOR_BG_WHITE = \033[47m

# Styles de texte supplémentaires
COLOR_BOLD_BRIGHT = \033[1;1m
COLOR_DIM_BRIGHT = \033[2;2m
COLOR_UNDERLINE_BRIGHT = \033[4;4m
COLOR_BLINK_BRIGHT = \033[5;5m
COLOR_REVERSE_BRIGHT = \033[7;7m
COLOR_HIDDEN_BRIGHT = \033[8;8m

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

# Couleurs du texte supplémentaires (texte / fond)
COLOR_BLACK_BRIGHT = \033[30;30m
COLOR_RED_BRIGHT = \033[31;31m
COLOR_GREEN_BRIGHT = \033[32;32m
COLOR_YELLOW_BRIGHT = \033[33;33m
COLOR_BLUE_BRIGHT = \033[34;34m
COLOR_MAGENTA_BRIGHT = \033[35;35m
COLOR_CYAN_BRIGHT = \033[36;36m
COLOR_WHITE_BRIGHT = \033[37;37m

# Couleurs de fond supplémentaires
COLOR_BG_BLACK_BRIGHT = \033[40;40m
COLOR_BG_RED_BRIGHT = \033[41;41m
COLOR_BG_GREEN_BRIGHT = \033[42;42m
COLOR_BG_YELLOW_BRIGHT = \033[43;43m
COLOR_BG_BLUE_BRIGHT = \033[44;44m
COLOR_BG_MAGENTA_BRIGHT = \033[45;45m
COLOR_BG_CYAN_BRIGHT = \033[46;46m
COLOR_BG_WHITE_BRIGHT = \033[47;47m

SRCS_ALL = sl_atoi.c sl_check.c sl_final_check.c sl_func.c sl_map_gen.c sl_map_init.c sl_utils.c sl_file_exporter.c

TOTAL_FILES := $(words $(SRCS_ALL))

COMPILED_FILES = 0

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS_ALL)))

all: init_header $(OBJ_DIR) $(NAME)

WIDTH = $(shell echo $$(($(TOTAL_FILES)/100 + 1)))
STATUS_OK = $(OK_COLOR)[✓]$(NO_COLOR)
STATUS_ERROR = $(ERROR_COLOR)[✖]$(NO_COLOR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ || (rm -f $@; exit 1)
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	@printf "$(COLOR_BOLD)$(COLOR_CYAN)Compile %-30s ➜$(COLOR_RESET) $(COLOR_BOLD)$(COLOR_GREEN) %-30s$(COLOR_RESET) [%-$(WIDTH)d/%-$(WIDTH)d] $(OK_COLOR)[✓]$(NO_COLOR)\n" $(notdir $<) $(notdir $@) $(COMPILED_FILES) $(TOTAL_FILES)

$(OBJ_DIR):
	@echo "$(COLOR_CYAN)Creating directory $(OBJ_DIR)$(COLOR_RESET)"
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@chmod +x $(NAME)
	@echo "$(COLOR_BOLD)$(COLOR_MAGENTA)Compilation done.$(COLOR_RESET)"

clean:
	@$(RM) $(OBJS)
	@echo "$(COLOR_BOLD)$(COLOR_YELLOW)All files are now removed.$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(COLOR_BOLD)$(COLOR_YELLOW)$(NAME) removed.$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re

init_header: 
	@clear
	@echo ".-----------------."
	@echo "| .--------------. |"
	@echo "| | ____  _____  | |"
	@echo "| ||_   \|_   _| | |"
	@echo "| |  |   \ | |   | |"
	@echo "| |  | |\ \| |   | |"
	@echo "| | _| |_\   |_  | |"
	@echo "| ||_____|\____| | |"
	@echo "| |              | |"
	@echo "| '--------------' |"
	@echo " '----------------' "
	@echo ""

