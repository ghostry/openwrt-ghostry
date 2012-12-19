CFLAGS = -O2
OBJ = md5c.o getPIN.o c21.o
LIB = 

TLSLIB =
LUALIB =


world: compile

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

compile: $(OBJ) $(TLSLIB) $(LUALIB)
	$(CC) -o ghca $(LDFLAGS) $(LIB) $(OBJ)

clean:
	rm -f *.o *.so ghca

