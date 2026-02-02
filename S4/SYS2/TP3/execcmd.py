#!/usr/bin/env python3
import os
import sys

if len(sys.argv) < 2 :
    print("Usage: ./execcmd.py <commande> [args...]")
    sys.exit(1)

cmd = sys.argv[1] 

args = sys.argv[1:] 

print(f"Exécution de : {cmd}")
print(f"Avec les arguments : {args}")

try:
    os.execvp(cmd, args)
except OSError as e:
    print(f"Erreur de l'execution : {e}")
