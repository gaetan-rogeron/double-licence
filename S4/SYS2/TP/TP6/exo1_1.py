import socket
HOST = "127.0.0.1"
PORT = 2002
MAXBYTES = 4096
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as serversocket:

    serversocket.bind((HOST, PORT)) 
    serversocket.listen() 
    while True:
        (
            clientsocket,
            (
                addr,
                port,
            ),
        ) = serversocket.accept() 
        with clientsocket:
            print(f"connected by application: {port} on machine: {addr}")
            data = clientsocket.recv(MAXBYTES)
            while (
                len(data) > 0
            ):
                clientsocket.sendall(data)
                data = clientsocket.recv(MAXBYTES)