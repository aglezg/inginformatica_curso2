IDIR =../include
CC = g++
CFLAGS = -I$(IDIR)

ODIR = .
LDIR = ../lib

LIBS = -lm

_DEPS = set_class.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = set_calculator.o set_class.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

set_calculator: $(OBJ)
	$(CC) -std=c++14 -g -Wall -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ o*.txt