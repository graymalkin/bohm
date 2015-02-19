# makefile for BOHM

include config.mk

# each time one of the following is modified, everything is recompiled
SUPPORT = include/crashhandler.h include/dynallhandler.h include/save.h include/copy.h\
          include/errorhandler.h include/garbage.h include/graphgenerator.h \
          include/inspect.h include/lambda_lexan.h include/lambda_parser.h \
          include/loader.h include/m_stack.h include/options.h src/destroyer.c \
          include/readback.h include/reducer.h include/scope_analysis.h include/sthandler.h \
          include/stringhandler.h include/const.h include/crashmsgs.i include/errormsgs.i \
          include/iolibrary.i include/keywords.i include/types.h Makefile

# the C files -- not the sources (lex and yacc object too)

CSRC = src/main.c src/y.tab.c src/lex.yy.c src/copy.c\
       src/sthandler.c src/scope_analysis.c src/inspect.c src/graphgenerator.c src/destroyer.c \
       src/loader.c src/reducer.c src/m_stack.c src/readback.c src/garbage.c src/save.c \
       src/util/crashhandler.c src/util/errorhandler.c \
       src/util/dynallhandler.c \
       src/util/stringhandler.c

# all the object files
OBJS = $(CSRC:.c=.o)

BIN = bin/opt

all: $(BIN)

$(BIN): $(OBJS) $(SUPPORT)
	mkdir -p bin
	$(CC) -o $(BIN) $(OBJS) $(LDFLAGS) $(LDLIBS)

# The two following productions are identical
src/y.tab.c include/y.tab.h: src/lambda_parser.y
	$(YACC) $< $(YFLAGS)
	mv y.tab.c src/
	mv y.tab.h include/

src/lex.yy.c: src/lambda_lexan.l include/y.tab.h
	$(LEX) src/lambda_lexan.l $(LFLAGS)
	mv lex.yy.c src/

# the default .c.o rule puts its object in the wrong directory
.c.o:
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ): $(SUPPORT)

src/lex.yy.o: include/y.tab.h

src/sthandler.o: include/y.tab.h

clean:
	-rm -f $(OBJS) include/y.tab.h src/y.tab.c src/lex.yy.c $(BIN)
