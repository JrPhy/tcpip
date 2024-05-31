CXX = gcc
all: server client

server : server_thread.c
	$(CXX) -o server_thread server_thread.c -pthread

client : client_thread.c
	$(CXX) -o client_thread client_thread.c -pthread

clean:
	rm server_thread client_thread
