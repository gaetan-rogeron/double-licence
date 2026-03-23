import os, sys, signal

#nom serveur FIFO unique avec PID
server_fifo = f"/tmp/server_{os.getpgid}.fifo"

#dictionnaire client pid -> fd
clients = {}

# handler exit pour ctrl+c
def handler_exit(signum, f):
    for fd in clients.value():
        try:
            os.close(fd)
        except OSError:
            pass
    try: 
        os.unlink(server_fifo)
        print("Serveur FIFO arrêté !")
    except FileNotFoundError:
        pass
        sys.exit(0)   


signal.signal(signal.SIGINT, handler_exit)

os.mkfifo(server_fifo)
print(f"Serveur asyncrone multi-clients démarré sur : {server_fifo}")

fd_server = os.open(server_fifo, os.RDWR)

while True:
    data = os.read(fd_server, 1024).decode()

    if not data:
        continue
    for line in data.split("\n"):
        if not line:
            continue
        part = line.split(':',2)
        if len(part) < 2:
            continue
        client_pid = part[0]
        msg_type = part[1]

        if msg_type == 'CONNECT' and len(part) == 3:
            client_fifo = part[2]
            clients[client_pid] = os.open(client_fifo, os.O_WRONLY)
            print(f"Nouuveau client PID : {client_pid}")
        elif msg_type == 'MSG' and len(part) == 3:
            msg = part[2]
            disconected = []

            for pid, fd_client in clients.items():
                try:
                    formatted_msg = f"[{client_pid}] : {msg}\n"
                    os.write(fd_client, formatted_msg.encode())
                except BrokenPipeError:
                    disconected.append(pid)
            for pid in disconected:
                os.close(clients[pid])
                del clients[pid]

        elif msg_type == 'DISCONNECT':
            if client_pid in clients:
                os.close(clients[client_pid])
                del clients[client_pid]
                print(f"Client {client_pid} déconnecté")