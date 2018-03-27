.PHONY: all clean
.SUFFIXES: .l .y .o .c .tab.h .tab.c .yy.c .lea .err .output

PROGRAM = lea

CC = cc
LEX = flex
LFLAGS = 
YACC = bison
YFLAGS = -t -d -v
CFLAGS = -g

OBJECTS = \
$(patsubst %.y,%.tab.o,$(wildcard *.y))\
$(patsubst %.l,%.yy.o,$(wildcard *.l))\
$(patsubst %.c,%.o,$(wildcard *.c)) 

all: Makefile $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) 

%.c: %.y
	@touch $@

%.c: %.l
	@touch $@

%.c: %.h

clean:
	rm $(OBJECTS)

%.o: %.c %.h
	$(CC) -c -o $@ $(CFLAGS) $< 

%.yy.c: %.l
	$(LEX) $(LFLAGS) -o $@ $<

%.tab.c: %.y
	$(YACC) $(YFLAGS) $<

%.err: %.$(PROGRAM) parser
	./parser $< $*.out 2> $@
