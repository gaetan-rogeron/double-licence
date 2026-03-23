import os, sys

if len(sys.argv) != 2:
    print("Usage: python echo_client.py <chemin_fifo_serveur>")
    sys.exit(1)

server_fifo = sys.argv[1]
my_pid = str(os.getpid())
client_fifo = f"/tmp/client_{my_pid}.fifo"
os.mkfifo(client_fifo)

# 1 Ouverture vers le serveur 
fd_server = os.open(server_fifo, os.O_WRONLY)

# 2 message de connexion IDENTIFIANT:TYPE:CONTENU
os.write(fd_server, f"{my_pid}:CONNECT:{client_fifo}\n".encode())

# 3 Ouverture FIFO en lecture
fd_client = os.open(client_fifo, os.O_RDONLY)

print(f"Connecté (PID: {my_pid}). Tapez vos messages (Ctrl+D ou Ctrl+C pour quitter) :")

try:
    while True:
        # Lecture bloquante 
        msg = sys.stdin.readline()
        
        # Terminaison par frappe de ^D 
        if not msg:
            os.write(fd_server, f"{my_pid}:DISCONNECT\n".encode())
            break
            
        msg = msg.strip()
        if msg:
            # Envoi message
            os.write(fd_server, f"{my_pid}:MSG:{msg}\n".encode())
            
            # Attente bloquante synchrone de la réponse du serveur
            reply = os.read(fd_client, 1024).decode()
            sys.stdout.write(reply)
            sys.stdout.flush()

except KeyboardInterrupt:
    # Interruption par frappe de ^C 
    os.write(fd_server, f"{my_pid}:DISCONNECT\n".encode())
    print("\nInterruption clavier détectée.")

finally:
    # Nettoyage
    os.close(fd_server)
    os.close(fd_client)
    os.unlink(client_fifo)
    print("Déconnexion réussie.")