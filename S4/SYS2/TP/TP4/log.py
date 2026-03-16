import os

cmd = input('commande? ')
fd = os.open('log.txt', os.O_WRONLY | os.O_CREAT | os.O_APPEND)
os.dup2(fd, 1)
os.close(fd)
args = cmd.split(" ")
os.execvp(args[0], args)