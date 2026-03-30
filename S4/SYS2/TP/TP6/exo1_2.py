import os, select, socket, sys

HOST = "127.0.0.1" # or 'localhost' or '' - Standard loopback interface address
PORT = 2005 # Port to listen on (non-privileged ports are > 1023)

MAXBYTES = 4096

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # IPv4, TCP
serversocket.bind((HOST, PORT))
serversocket.listen()
print("server listening on port:", PORT)
nb_open = 0
# Create list of potential active sockets and place server socket in
# first position
socketlist = [serversocket]
first = True
while first or nb_open > 0:
    first = False
    (activesockets, _, _) = select.select(socketlist, [], [])
    for s in activesockets:
        if s == serversocket:
            (clientsocket, (addr, port)) = serversocket.accept()
            socketlist.append(clientsocket)
            print(f"Incoming connection from {addr} on port {port}...")
            nb_open += 1
        else:
            msg = s.recv(MAXBYTES)
            if len(msg) == 0:
                print("NULL message. Closing connection...")
                s.close()
                # Remove the closed connection from potential active sockets
                socketlist.remove(s)
                nb_open -= 1
            else:
                os.write(1, msg)
serversocket.close()
print("Last connection closed. Bye!")
sys.exit(0)