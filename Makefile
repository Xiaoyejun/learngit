maze:maze.c
maze.c:
	gcc -g $@ -o $^
.PHONY:clean
clean:
	rm -rf maze
