# makefile for BOHM

CFLAGS = -O
#CFLAGS = -g
LDLIBS = -ll -ly
YFLAGS = -d

# No user serviceable parts below this line

# each time one of the following is modified, everything is recompiled
SUPPORT = i/crashhandler.i i/dynallhandler.i i/save.i i/copy.i\
i/errorhandler.i i/filehandler.i i/garbage.i i/graphgenerator.i \
i/inspect.i i/lambda_lexan.i i/lambda_parser.i i/listinghandler.i \
i/loader.i i/m_stack.i i/menu.i i/numberhandler.i destroyer.c\
i/readback.i i/reducer.i i/scope_analysis.i i/sthandler.i \
i/stringhandler.i h/const.h h/crashmsgs.h h/errormsgs.h \
h/iolibrary.h h/keywords.h h/types.h Makefile

# the C files -- not the sources (lex and yacc object too)

CSRC = main.c y.tab.c lex.yy.c copy.c\
sthandler.c scope_analysis.c inspect.c graphgenerator.c destroyer.c \
loader.c reducer.c m_stack.c readback.c garbage.c menu.c save.c \
utility/crashhandler.c utility/errorhandler.c \
utility/numberhandler.c utility/dynallhandler.c \
utility/filehandler.c utility/stringhandler.c

# all the object files
OBJS = main.o y.tab.o lex.yy.o copy.o\
sthandler.o scope_analysis.o inspect.o graphgenerator.o destroyer.o \
loader.o reducer.o m_stack.o readback.o garbage.o menu.o save.o \
utility/crashhandler.o utility/errorhandler.o \
utility/numberhandler.o utility/dynallhandler.o \
utility/filehandler.o utility/stringhandler.o

opt: $(OBJS) $(SUPPORT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) \
	$(OBJS) \
	-o opt $(LDLIBS)

# The two following productions are identical
y.tab.c: lambda_parser.y
	$(YACC) $(YFLAGS) lambda_parser.y
	mv y.tab.h h/y.tab.h

h/y.tab.h: lambda_parser.y
	$(YACC) $(YFLAGS) lambda_parser.y
	mv y.tab.h h/y.tab.h

lex.yy.c: lambda_lexan.l h/y.tab.h
	$(LEX) $(LFLAGS) lambda_lexan.l

# the default .c.o rule puts its object in the wrong directory
.c.o:
	$(COMPILE.c) -o $@ $<

copy.o: copy.c $(SUPPORT)

destroyer.o: destroyer.c $(SUPPORT)

garbage.o: garbage.c $(SUPPORT)

graphgenerator.o: graphgenerator.c $(SUPPORT)

inspect.o: inspect.c $(SUPPORT)

lex.yy.o: lex.yy.c $(SUPPORT) h/y.tab.h

loader.o: loader.c $(SUPPORT)

m_stack.o: m_stack.c $(SUPPORT)

main.o: main.c $(SUPPORT)

menu.o: menu.c $(SUPPORT)

#rback.o: rback.c $(SUPPORT)

readback.o: readback.c $(SUPPORT)

reducer.o: reducer.c $(SUPPORT)

save.o: save.c $(SUPPORT)

scope_analysis.o: scope_analysis.c $(SUPPORT)

sthandler.o: sthandler.c $(SUPPORT) h/y.tab.h

y.tab.o: y.tab.c $(SUPPORT)

utility/crashhandler.o: utility/crashhandler.c $(SUPPORT)

utility/dynallhandler.o: utility/dynallhandler.c $(SUPPORT)

utility/errorhandler.o: utility/errorhandler.c $(SUPPORT)

utility/filehandler.o: utility/filehandler.c $(SUPPORT)

utility/numberhandler.o: utility/numberhandler.c $(SUPPORT)

utility/stringhandler.o: utility/stringhandler.c $(SUPPORT)

# lint the whole code.  Expect a lot of warnings!
lint: $(CSRC)
	$(LINT.c) $(CSRC)

# rebuild the TAGS file for emacs
etags: 
	etags readback.c garbage.c loader.c reducer.c m_stack.c \
	scope_analysis.c graphgenerator.c main.c sthandler.c menu.c inspect.c \
	utility/crashhandler.c utility/errorhandler.c \
	utility/numberhandler.c utility/dynallhandler.c utility/filehandler.c \
	utility/stringhandler.c lambda_parser.y lambda_lexan.l

# rebuild the tags file for vi
ctags: 
	ctags readback.c garbage.c loader.c reducer.c m_stack.c \
	scope_analysis.c graphgenerator.c main.c sthandler.c menu.c inspect.c \
	utility/crashhandler.c utility/errorhandler.c \
	utility/numberhandler.c utility/dynallhandler.c utility/filehandler.c \
	utility/stringhandler.c lambda_parser.y lambda_lexan.l

clean:
	-cd utility ; rm -f *.o
	-rm -f *.o 
	-rm -f y.tab.c lex.yy.c y.output
	-rm -f h/y.tab.h opt

distclean: clean
	-rm -f TAGS tags



