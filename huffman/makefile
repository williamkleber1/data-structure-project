OBJS = src/main.c src/queue.c src/descompress.c src/compress.c src/huffman_tree.c
DEPS = inc/queue.h inc/descompress.h inc/compress.h inc/huffman_tree.h


compile:
	gcc $(OBJS) $(DEPS) -o main -lm

test:
	gcc src/file.c -o file

clean:
	rm -f main
	rm -f file

