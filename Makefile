server:server.c
#client:client.c
	gcc -o $@ -g $^
.PHONY:clean
clean:
#	rm -f client
	rm -f server
