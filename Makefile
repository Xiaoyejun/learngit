#bin_tree:./bin_tree.c ./seqqueue.c ./seqstack.c
thread_tree:./thread_tree.c
	gcc -o $@ -g $^
.PHONY:clean
clean:
	rm -f thread_tree
#	rm -f bin_tree
