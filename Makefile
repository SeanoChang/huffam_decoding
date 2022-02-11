CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -pedantic -Werror
GCCALL = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc $(CFLAGS)
EXEC = pa2
OBJS =  pa2.o
HOBJS = 
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose


$(EXEC): $(OBJS) $(HOBJS)
	$(GCC) $(OBJS) -o $(EXEC)

test: $(EXEC)
	./pa2 encoded/gophers_huff.hbt gophers_huff.tree gophers.ori gophers.count gophers.htree gophers.eval

memory: $(EXEC)
	mkdir moutputs
	$(VALGRIND) ./$(EXEC) 

%.o : %.c
	$(GCC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f *.bin *.b
	/bin/rm -rf outputs
	/bin/rm -rf moutputs
	/bin/rm -f id? first? last? log?
