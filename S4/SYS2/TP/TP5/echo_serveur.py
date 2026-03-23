import os
import sys
import atexit

# 1 Créer FIFO avec nom unique
server_fifo = f"/tmp/server_{os.getpid()}.fifo"
os.mkfifo(server_fifo)
print(f"Serveur démarré (PID: {os.getpid()}). En attente sur : {server_fifo}")

# 2 Suppression avec atexit
def suppression():
    try:
        os.unlink(server_fifo)
        print("\nFIFO serveur supprimée.")
    except FileNotFoundError:
        pass

atexit.register(suppression)

#3 Ouvrir FIFO en lecture 
fd_server_read = os.open(server_fifo, os.O_RDONLY)
print("Un client s'est connecté FIFO serveur.")

# 4. Lire les données client
client_fifo_path = os.read(fd_server_read, 1024).decode().strip()
print(f"Chemin de la FIFO client reçu : {client_fifo_path}")

# 5. Ouvrir la FIFO client en écriture
fd_client_write = os.open(client_fifo_path, os.O_WRONLY)

# 6
try:
    while True:
        # Lecture du message du client
        data = os.read(fd_server_read, 1024)
        
        if len(data) == 0:
            print("Le client est déconnecté.")
            break
            
        os.write(fd_client_write, data)
        
except KeyboardInterrupt:
    print("\nArrêt du serveur.")
finally:
    os.close(fd_server_read)
    os.close(fd_client_write)