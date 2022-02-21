CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -pedantic -Werror
GCCALL = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc $(CFLAGS)
EXEC = pa2
OBJS =  pa2.o decode_tree.o huffman_tree.o char_list.o write_output.o
HOBJS = decode_tree.h huffman_tree.h char_list.h write_output.h
VALGRIND = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --verbose


$(EXEC): $(OBJS) $(HOBJS)
	$(GCC) $(OBJS) -o $(EXEC)

test: $(EXEC)
	mkdir outputs
	./pa2 pa2_examples/encoded/gophers_nonhuff.hbt outputs/gophers.tree outputs/gophers.ori outputs/gophers.count outputs/gophers.htree outputs/gophers.eval
	diff outputs/gophers.tree pa2_examples/tree/gophers_nonhuff.tree
	diff outputs/gophers.ori pa2_examples/decoded/gophers
	diff outputs/gophers.count pa2_examples/count/gophers.count
	diff outputs/gophers.htree pa2_examples/tree/gophers_huff.tree
	diff outputs/gophers.eval pa2_examples/eval/gophers_nonhuff.eval
	
memory: $(EXEC)
	mkdir moutputs
	$(VALGRIND) ./$(EXEC) pa2_examples/encoded/gophers_nonhuff.hbt moutputs/gohers_huff.tree moutputs/gophers.ori moutputs/gophers.count moutputs/gophers.htree moutputs/gophers.eval

%.o : %.c
	$(GCC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f *.bin *.b
	/bin/rm -rf outputs
	/bin/rm -rf moutputs
	/bin/rm -f id? first? last? log?
