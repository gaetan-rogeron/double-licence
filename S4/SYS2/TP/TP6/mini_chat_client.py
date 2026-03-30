import os, socket, sys, select

MAXBYTES = 4096

if len(sys.argv) != 4:
    print('Usage:', sys.argv[0], 'hote port pseudo')
    sys.exit(1)

HOST = sys.argv[1]
PORT = int(sys.argv[2])
PSEUDO = sys.argv[3]

sockaddr = (HOST, PORT)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(sockaddr)
s.send(PSEUDO.encode())
liste_pseudo = s.recv(MAXBYTES).decode()

print('connected to:', sockaddr)
print(liste_pseudo)

while True: # Client synchrone !! On alterne écriture vers serveur
            # et lecture depuis serveur. Le serveur doit donc lui aussi alterner
    line = os.read(0, MAXBYTES)

    if len(line) == 0:
        s.shutdown(socket.SHUT_WR)
        break
    s.send(line)
    data = s.recv(MAXBYTES) # attention, si le serveur n'envoie rien on est bloqué.
    if len(data) == 0:
        break
    os.write(1, data)
s.close()