import os, select, socket, sys

HOST = "127.0.0.1" 
PORT = 2029

MAXBYTES = 4096


serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # IPv4, TCP
serversocket.bind((HOST, PORT))
serversocket.listen()
print("server listening on port:", PORT)

def print_client():
    res = "Clients connectés : \n"
    for socket in client_pseudo:
        res += client_pseudo[socket] + '\n'
    return res


def print_commande():
    return "les commandes supportées sont : \n @pseudo msg \n @tous msg \n CTRL-D pour se déconnecter proprement\n ..."

nb_open = 0

socketlist = [serversocket]
client_pseudo = {}
client_socket = {}

first = True
while first or nb_open > 0:
    first = False
    (activesockets, _, _) = select.select(socketlist, [], [])
    for s in activesockets:
        if s == serversocket:
            (clientsocket, (addr, port)) = serversocket.accept()
            socketlist.append(clientsocket)

            client_pseudo[clientsocket.fileno()] = clientsocket.recv(MAXBYTES).decode() 
            client_socket[clientsocket.fileno()] = clientsocket
            
            print(f"Incoming connection from {addr} on port {port}...")
            liste_client = print_client()
            clientsocket.send(liste_client.encode())

            nb_open += 1
        else:
            msg = s.recv(MAXBYTES).decode()
            commande = msg.split(' ')[0]
            
            if len(msg) == 0:
                print("NULL message. Closing connection...")
                s.close()
                # Remove the closed connection from potential active sockets
                socketlist.remove(s)
                nb_open -= 1
            elif commande == '@tous':
                print("@tous reçu")
            else:
                os.write(1, msg)
serversocket.close()
print("Last connection closed. Bye!")
sys.exit(0)