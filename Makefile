# makefile for BOHM

CFLAGS = -Iinclude
#CFLAGS = -g
LDLIBS = -ll -ly
YFLAGS = -d

# No user serviceable parts below this line

# each time one of the following is modified, everything is recompiled
SUPPORT = include/crashhandler.i include/dynallhandler.i include/save.i include/copy.i\
          include/errorhandler.i include/filehandler.i include/garbage.i include/graphgenerator.i \
          include/inspect.i include/lambda_lexan.i include/lambda_parser.i include/listinghandler.i \
          include/loader.i include/m_stack.i include/menu.i include/numberhandler.i src/destroyer.c \
          include/readback.i include/reducer.i include/scope_analysis.i include/sthandler.i \
          include/stringhandler.i include/const.h include/crashmsgs.h include/errormsgs.h \
          include/iolibrary.h include/keywords.h include/types.h Makefile

# the C files -- not the sources (lex and yacc object too)

CSRC = src/main.c src/y.tab.c src/lex.yy.c src/copy.c\
       src/sthandler.c src/scope_analysis.c src/inspect.c src/graphgenerator.c src/destroyer.c \
       src/loader.c src/reducer.c src/m_stack.c src/readback.c src/garbage.c src/menu.c src/save.c \
       src/util/crashhandler.c src/util/errorhandler.c \
       src/util/numberhandler.c src/util/dynallhandler.c \
       src/util/filehandler.c src/util/stringhandler.c

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
	-rm -f $(OBJ) include/y.tab.h src/y.tab.c src/lex.yy.c $(BIN)
