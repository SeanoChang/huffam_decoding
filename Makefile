CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -pedantic -Werror
GCCALL = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc $(CFLAGS)
EXEC = pa2
OBJS =  pa2.o decode_tree.o huffman_tree.o char_list.o
HOBJS = decode_tree.h huffman_tree.h char_list.h
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose


$(EXEC): $(OBJS) $(HOBJS)
	$(GCC) $(OBJS) -o $(EXEC)

test: $(EXEC)
	mkdir outputs
	./pa2 pa2_examples/encoded/gophers_huff.hbt outputs/gophers_huff.tree outputs/gophers.ori outputs/gophers.count outputs/gophers.htree outputs/gophers.eval

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
