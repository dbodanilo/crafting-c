CC       = gcc
CFLAGS   = -std=c11 -Wall -fmax-errors=10 -Wextra
LFLAGS   = 
LIBS     = 
OBJFILES = main.o chunk.o debug.o vm.o \
value.o memory.o compiler.o object.o \
scanner.o 

MAIN     = clox

all: $(MAIN)

$(MAIN): $(OBJFILES) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJFILES) $(LFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(MAIN)

