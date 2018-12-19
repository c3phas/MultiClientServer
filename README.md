# MultiClientServer
This is a simple illustration of a server that can be able to handle multiple clients
The server is written in c and should work on any unix based systems that supports gcc compiler
The server uses fork() to handle the many clients at the same time
To run the server just compile the source code using gcc -Wall -o server server.c and run ./server
The code for the client can be gotten from my client-server repository(chat application)

