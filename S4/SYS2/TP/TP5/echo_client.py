import os
import sys
import atexit

if len(sys.argv) != 2:
    print("Usage: python echo_client.py <chemin_fifo_serveur>")
    sys.exit(1)

# 1. Créer FIFO avec nom unique 
client_fifo = f"/tmp/client_{os.getpid()}.fifo"
os.mkfifo(client_fifo)

# 2.suppression
def suppression():
    try:
        os.unlink(client_fifo)
        print("\nFIFO client supprimée.")
    except FileNotFoundError:
        pass

atexit.register(suppression)

server_fifo = sys.argv[1]


# 3. Récupérer le chemin FIFO serveur et ouvrir en ecriture 
fd_server_write = os.open(server_fifo, os.O_WRONLY)

# 4. Envoyer chemin fifo au server
os.write(fd_server_write, (client_fifo + "\n").encode())

# 5. Ouvrir FIFO client en lecture
fd_client_read = os.open(client_fifo, os.O_RDONLY)

print("Connecté au serveur ! Tapez vos messages (Ctrl+D pour quitter) :")

# 6
try:
    while True:
        # lire sur l'entree standard
        msg = sys.stdin.readline()
        
        if not msg:
            break
            
        # Envoyer au serveur
        os.write(fd_server_write, msg.encode())
        
        # Lire la réponse du serveur et l'écrire sur la sortie standard
        response = os.read(fd_client_read, 1024)
        sys.stdout.write("Écho du serveur : " + response.decode())
        sys.stdout.flush()

except KeyboardInterrupt:
    print("\nArrêt du client.")
finally:
    os.close(fd_server_write)
    os.close(fd_client_read)