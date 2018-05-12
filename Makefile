heap:heap.c
	gcc -o $@ -g $^
.PHONY:clean
clean:
	rm -f heap
