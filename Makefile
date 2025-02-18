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
TESTEXEMT = testlogmt
TESTEXENL = testnolog

#
# log build settings
#
OBJDIR = obj
TESTOBJS = $(addprefix $(OBJDIR)/, $(OBJS))
TESTCPPFLAGS = $(CPPFLAGS)

#
# log multithreaded settings
#
OBJDIRMT = objmt
TESTOBJSMT = $(addprefix $(OBJDIRMT)/, $(OBJS))
TESTCPPFLAGSMT = $(CPPFLAGS) -D__WRSLOG_PTHREAD -pthread

#
# nolog build settings
#
OBJDIRNL = objnl
TESTOBJSNL = $(addprefix $(OBJDIRNL)/, $(OBJS))
TESTCPPFLAGSNL = $(CPPFLAGS) -D__WRSLOG_DISABLE

.PHONY: all prep remake clean test testmt testnl

# Default build
all: prep test testmt testnl

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
# log multithreaded rules
#
testmt: prep
testmt: $(TESTEXEMT)
$(TESTEXEMT): $(TESTOBJSMT)
	$(CC) $(TESTOBJSMT) -o $(TESTEXEMT) $(LDLIBS) -pthread

$(OBJDIRMT)/%.o: prep
$(OBJDIRMT)/%.o: %.c
	$(CC) -c $(TESTCPPFLAGSMT) -o $@ $<

$(TESTOBJSMT): $(HEADERS)

#
# nolog rules
#
testnl: prep
testnl: $(TESTEXENL)
$(TESTEXENL): $(TESTOBJSNL)
	$(CC) $(TESTOBJSNL) -o $(TESTEXENL) $(LDLIBS)

$(OBJDIRNL)/%.o: prep
$(OBJDIRNL)/%.o: %.c
	$(CC) -c $(TESTCPPFLAGSNL) -o $@ $<

$(TESTOBJSNL): $(HEADERS)

#
# Other rules
#
prep:
	@mkdir -p $(OBJDIR) $(OBJDIRMT) $(OBJDIRNL)

remake: clean all

clean:
	rm -f $(TESTEXE) $(TESTOBJS) $(TESTEXEMT) $(TESTOBJSMT) $(TESTEXENL) $(TESTOBJSNL)
