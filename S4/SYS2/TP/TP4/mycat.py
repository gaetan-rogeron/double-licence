import os, sys


if len(sys.argv) == 1 :
        while True:
            octets = os.read(0, 100)
            if not octets: break
            os.write(1, octets)
else :
    cmd = sys.argv[1:]
    for fichier in cmd :
        fd = os.open(fichier, os.O_RDONLY)
        while True :
            octets = os.read(fd,1024)
            if not octets:
                os.close(fd)
                break
            os.write(1,octets)

