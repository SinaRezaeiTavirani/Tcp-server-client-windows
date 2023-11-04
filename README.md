# Tcp-server-client-windows
This project is for making a connection between server and client in cmd env and by using windows socket library.
IMPORTANT:  for building the code make sure to add -lwsock32 at the end of g++ command.
complete command for building client code : g++ -std=c++17 Logger.cpp Client.cpp main.cpp -lws2_32 -lwsock32 -o client.exe 
complete command for building server code : g++ Logger.cpp Server.cpp main.cpp -lwsock32 -lws2_32 -o server.exe
run server code first : server.exe <IP><PORT> example : server.exe 127.0.0.1 5555
run client code second : client.exe <IP><PORT> example : client.exe 127.0.0.1 5555  