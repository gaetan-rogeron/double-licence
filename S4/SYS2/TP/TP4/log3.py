import os, sys

if len(sys.argv) >= 2 :
    script = os.open(sys.argv[1], os.O_RDONLY)
    
    os.dup2(script, 0)
    os.close(script)
    while True:
        cmd = os.read(0, )
        
        if os.fork() == 0 :
            fd = os.open('log.txt', os.O_WRONLY | os.O_CREAT | os.O_APPEND)
            os.dup2(fd, 1)
            os.close(fd)
            os.execvp(args[0], args)
        os.wait()