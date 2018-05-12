search_tree:search_tree.c
	gcc -o $@ -g $^
.PHONY:
	clean
clean:
	rm -f search_tree

