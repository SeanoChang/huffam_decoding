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

	./pa2 pa2_examples/encoded/gophers_huff.hbt outputs/gophers1.tree outputs/gophers1.ori outputs/gophers1.count outputs/gophers1.htree outputs/gophers1.eval
	diff outputs/gophers1.tree pa2_examples/tree/gophers_huff.tree
	diff outputs/gophers1.ori pa2_examples/decoded/gophers
	diff outputs/gophers1.count pa2_examples/count/gophers.count
	diff outputs/gophers1.htree pa2_examples/tree/gophers_huff.tree
	diff outputs/gophers1.eval pa2_examples/eval/gophers_huff.eval

	./pa2 pa2_examples/encoded/lorum_nonhuff.hbt outputs/lorum.tree outputs/lorum.ori outputs/lorum.count outputs/lorum.htree outputs/lorum.eval
	diff outputs/lorum.tree pa2_examples/tree/lorum_nonhuff.tree
	diff outputs/lorum.ori pa2_examples/decoded/lorum
	diff outputs/lorum.count pa2_examples/count/lorum.count
	diff outputs/lorum.htree pa2_examples/tree/lorum_huff.tree
	diff outputs/lorum.eval pa2_examples/eval/lorum_nonhuff.eval

	./pa2 pa2_examples/encoded/stone_nonhuff.hbt outputs/stone.tree outputs/stone.ori outputs/stone.count outputs/stone.htree outputs/stone.eval
	diff outputs/stone.tree pa2_examples/tree/stone_nonhuff.tree
	diff outputs/stone.ori pa2_examples/decoded/stone
	diff outputs/stone.count pa2_examples/count/stone.count
	diff outputs/stone.htree pa2_examples/tree/stone_huff.tree
	diff outputs/stone.eval pa2_examples/eval/stone_nonhuff.eval

	./pa2 pa2_examples/encoded/woods_nonhuff.hbt outputs/woods.tree outputs/woods.ori outputs/woods.count outputs/woods.htree outputs/woods.eval
	diff outputs/woods.tree pa2_examples/tree/woods_nonhuff.tree
	diff outputs/woods.ori pa2_examples/decoded/woods
	diff outputs/woods.count pa2_examples/count/woods.count
	diff outputs/woods.htree pa2_examples/tree/woods_huff.tree
	diff outputs/woods.eval pa2_examples/eval/woods_nonhuff.eval

	./pa2 pa2_examples/encoded/binary1_nonhuff.hbt outputs/binary1.tree outputs/binary1.ori outputs/binary1.count outputs/binary1.htree outputs/binary1.eval
	diff outputs/binary1.tree pa2_examples/tree/binary1_nonhuff.tree
	diff outputs/binary1.ori pa2_examples/decoded/binary1
	diff outputs/binary1.count pa2_examples/count/binary1.count
	diff outputs/binary1.htree pa2_examples/tree/binary1_huff.tree
	diff outputs/binary1.eval pa2_examples/eval/binary1_nonhuff.eval
	
memory: $(EXEC)
	mkdir moutputs
	$(VALGRIND) ./$(EXEC) pa2_examples/encoded/binary1_nonhuff.hbt outputs/binary1.tree outputs/binary1.ori outputs/binary1.count outputs/binary1.htree outputs/binary1.eval
	
%.o : %.c
	$(GCC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f *.bin *.b *.ori *.tree *.count *.eval *.htree
	/bin/rm -rf outputs
	/bin/rm -rf moutputs
	/bin/rm -f id? first? last? log?
