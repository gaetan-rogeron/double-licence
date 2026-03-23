import os

server_fifo = f"/tmp/server_{os.getpid()}.fifo"
os.mkfifo(server_fifo)
print(f"Serveur multi-clients démarré sur : {server_fifo}")

# O_RDWR empêche os.read de renvoyer une chaîne vide en boucle quand il y a aucun client
fd_server = os.open(server_fifo, os.O_RDWR)

# Dictionnaire : pid client  -> fd 
clients = {} 

try:
    while True:
        # Lecture bloquante
        data = os.read(fd_server, 1024).decode()
        if not data:
            continue
            
        # ligne par ligne au cas ou il y en a plusieurs en meme temps
        for line in data.strip().split('\n'):
            if not line:
                continue
                
            # prefixe client avec identifiant
            parts = line.split(':', 2)
            if len(parts) < 2:
                continue
                
            client_pid = parts[0]
            msg_type = parts[1]
            
            # Demande de connexion
            if msg_type == 'CONNECT' and len(parts) == 3:
                client_fifo = parts[2]
                #ouvre la FIFO du client pour pouvoir lui écrire plus tard
                clients[client_pid] = os.open(client_fifo, os.O_WRONLY)
                # Ajout client au dictionnaire
                print(f"Nouveau client : PID {client_pid}")
                
            # Message à renvoyer 
            elif msg_type == 'MSG' and len(parts) == 3:
                msg = parts[2]
                if client_pid in clients:
                    # serveur communique vers ce client 
                    echo_msg = f"Echo serveur : {msg}\n"
                    os.write(clients[client_pid], echo_msg.encode())
                    
            # déconnexion volontaire
            elif msg_type == 'DISCONNECT':
                if client_pid in clients:
                    os.close(clients[client_pid])
                    del clients[client_pid] # Suppression client du dictionnaire
                    print(f"Client {client_pid} déconnecté et retiré du dictionnaire.")

except KeyboardInterrupt:
    print("\nArrêt du serveur.")
finally:
    # Nettoyage des descripteurs restants
    for fd in clients.values():
        os.close(fd)
    os.close(fd_server)
    os.unlink(server_fifo)