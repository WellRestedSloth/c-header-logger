## Variables
NAME	= testlog
SRC		= \
	test.c

OBJ		= $(SRC:.c=.o)
CFLAGS	= -g -Wall -Wextra
LDLIBS	=
CC		= gcc

## Rules
$(NAME)	: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDLIBS)

default	: $(NAME)

## Disable logger for the "nolog" target
nolog	: CFLAGS += -D__WRSLOG_DISABLE
nolog	: $(NAME)

clean	:
	rm -f $(OBJ) $(NAME)
