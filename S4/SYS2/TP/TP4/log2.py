import os

while True:
    cmd = input('commande? ')
    if cmd == 'exit' : break
    args = cmd.split(" ")
    
    if os.fork() == 0 :
        fd = os.open('log.txt', os.O_WRONLY | os.O_CREAT | os.O_APPEND)
        os.dup2(fd, 1)
        os.close(fd)
        os.execvp(args[0], args)
    os.wait()