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
LOGEXE = testlog
NOLOGEXE = testnolog

#
# log build settings
#
LOGDIR = logobj
LOGOBJS = $(addprefix $(LOGDIR)/, $(OBJS))
LOGCPPFLAGS = $(CPPFLAGS)

#
# nolog build settings
#
NOLOGDIR = nologobj
NOLOGOBJS = $(addprefix $(NOLOGDIR)/, $(OBJS))
NOLOGCPPFLAGS = $(CPPFLAGS) -D__WRSLOG_DISABLE

.PHONY: all clean prep test log nolog

# Default build
all: prep log nolog

#
# log rules
#
log: prep
log: $(LOGEXE)
$(LOGEXE): $(LOGOBJS)
	$(CC) $(LOGOBJS) -o $(LOGEXE) $(LDLIBS)

$(LOGDIR)/%.o: prep
$(LOGDIR)/%.o: %.c
	$(CC) -c $(LOGCPPFLAGS) -o $@ $<

$(LOGOBJS): $(HEADERS)

#
# nolog rules
#
nolog: prep
nolog: $(NOLOGEXE)
$(NOLOGEXE): $(NOLOGOBJS)
	$(CC) $(NOLOGOBJS) -o $(NOLOGEXE) $(LDLIBS)

$(NOLOGDIR)/%.o: prep
$(NOLOGDIR)/%.o: %.c
	$(CC) -c $(NOLOGCPPFLAGS) -o $@ $<

$(NOLOGOBJS): $(HEADERS)

#
# Other rules
#
prep:
	@mkdir -p $(LOGDIR) $(NOLOGDIR)

remake: clean all

clean:
	rm -f $(LOGEXE) $(LOGOBJS) $(NOLOGEXE) $(NOLOGOBJS)
