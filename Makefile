#
# Compiler flags
#
CC = gcc
CPPFLAGS = -g -Wall -Wextra
LDLIBS =

#
# Project files
#
SRCS = \
	test.c
OBJS = $(SRCS:.c=.o)
HEADERS = wrslog.h
TESTEXE = testlog
TESTEXE2 = testnolog

#
# log build settings
#
OBJDIR = obj
TESTOBJS = $(addprefix $(OBJDIR)/, $(OBJS))
TESTCPPFLAGS = $(CPPFLAGS)

#
# nolog build settings
#
OBJDIR2 = obj2
TESTOBJS2 = $(addprefix $(OBJDIR2)/, $(OBJS))
TESTCPPFLAGS2 = $(CPPFLAGS) -D__WRSLOG_DISABLE

.PHONY: all prep remake clean test test2

# Default build
all: prep test test2

#
# log rules
#
test: prep
test: $(TESTEXE)
$(TESTEXE): $(TESTOBJS)
	$(CC) $(TESTOBJS) -o $(TESTEXE) $(LDLIBS)

$(OBJDIR)/%.o: prep
$(OBJDIR)/%.o: %.c
	$(CC) -c $(TESTCPPFLAGS) -o $@ $<

$(TESTOBJS): $(HEADERS)

#
# nolog rules
#
test2: prep
test2: $(TESTEXE2)
$(TESTEXE2): $(TESTOBJS2)
	$(CC) $(TESTOBJS2) -o $(TESTEXE2) $(LDLIBS)

$(OBJDIR2)/%.o: prep
$(OBJDIR2)/%.o: %.c
	$(CC) -c $(TESTCPPFLAGS2) -o $@ $<

$(TESTOBJS2): $(HEADERS)

#
# Other rules
#
prep:
	@mkdir -p $(OBJDIR) $(OBJDIR2)

remake: clean all

clean:
	rm -f $(TESTEXE) $(TESTOBJS) $(TESTEXE2) $(TESTOBJS2)
