all: server client

server : server_thread.c
	gcc -o $@ $^ -pthread

client : client_thread.c
	gcc -o $@ $^ -pthread

clean:
	rm server_thread client_thread
