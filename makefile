all:	server client

server:
	gcc server.c transfile.c conn.c -lpthread -o server
  
client:
	gcc client.c transfile.c conn.c -lpthread -o client

clean:  
	rm -rf server client hehe.file
