test_sem:./test_sem.c ./common.c
	gcc -o $@ -g $^
.PHONY:clean
clean:
	rm -rf test_sem
