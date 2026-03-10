#!/usr/bin/env python3
import os
import sys

if len(sys.argv) < 2 :
    print("Usage: ./execcmd.py <commande> [args...]")
    sys.exit(1)


fils = os.fork()

if fils == 0:
    try:
        os.execvp(sys.argv[1], sys.argv[1:])
    except FileNotFoundError:
        print(f"Erreur lors du chargement de {sys.argv[1]}", file=sys.stderr)
        sys.exit(13)

pid, status = os.wait()

if status == 0:
    print("success")
else: 
    print("Error")
sys.exit(1)

