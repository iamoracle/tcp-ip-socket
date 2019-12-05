# tcp-ip-socket
Implementaion of TCP/IP socket in a very easy and memorable way.

Extract the server.c and client.c to a folder, launch the terminal from the folder.

You can compile the server and client using

> gcc client.c -o client

> gcc server.c -o server

Then, run the server using

+ > ./server 127.0.0.1 10050

Then, run the client using

- > ./client 127.0.0.1 10050

You can use other IP address and port number e.g.

> ./server <IP> <PORT>

> ./client <IP> <PORT>
