## Variables
TESTEXE = testlog
SRCS = \
	test.c

OBJS = $(SRCS:.c=.o)
CPPFLAGS = -g -Wall -Wextra
LDLIBS =
CC = gcc

.PHONY:	test $(TESTEXE) nolog clean

## Rules section

## Link executable (default)
$(TESTEXE)	: $(OBJS)
	$(CC) $(OBJS) -o $(TESTEXE) $(LDLIBS)

## Disable logger for the "nolog" target
nolog	: CPPFLAGS += -D__WRSLOG_DISABLE
nolog	: $(TESTEXE)

clean	:
	rm -f $(OBJS) $(TESTEXE)
