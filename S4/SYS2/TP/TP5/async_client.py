import os, sys, select, signal

if len(sys.argv) != 2:
    print("Usage: python echo_client.py <chemin_fifo_serveur>")
    sys.exit(1)

server_fifo = sys.argv[1]
my_pid = str(os.getpid())
client_fifo = f"/tmp/client_{my_pid}.fifo"
os.mkfifo(client_fifo)


def handler_exit(signum, frame):
    try:
        os.write(fd_server, f"{my_pid}:DISCONNECT\n".encode())
        os.close(fd_server)
        os.unlink(client_fifo)
    except FileNotFoundError:
        pass
    print("\nDéconnecté du chat.")
    sys.exit(0)

signal.signal(signal.SIGINT, handler_exit)

fd_server = os.open(server_fifo, os.O_WRONLY)
os.write(fd_server, f"{my_pid}:CONNECT:{client_fifo}\n".encode())
fd_client = os.open(client_fifo, os.O_RDONLY)

print(f"Connecté au chat (PID: {my_pid}). Tapez vos messages :")

while True:
    lecteurs_prets, _, _ = select.select([sys.stdin, fd_client], [], [])
    for fd in lecteurs_prets:
        if fd == sys.stdin:
            msg = sys.stdin.readline()
            if not msg:
                handler_exit(None, None)
            
            msg = msg.strip()
            if msg:
                os.write(fd_server, f"{my_pid}:MSG:{msg}\n".encode())

        elif fd == fd_client:
            data = os.read(fd_client, 1024).decode()
            if not data:
                print("Le serveur a fermé la connexion.")
                handler_exit(None, None)
                    
            sys.stdout.write(data)
