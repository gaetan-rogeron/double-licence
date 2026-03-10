#!/usr/bin/env python3
import os
import sys

commandes = [
    ["who"],
    ["pwd"],
    ["ls","-l"]
    ]

for args in commandes:
    pid = os.fork()
    if pid == 0:
        os.execvp(args[0],args)
        sys.exit(1)
    else:
        os.wait()

print("toutes les commandes ont ete exectute")