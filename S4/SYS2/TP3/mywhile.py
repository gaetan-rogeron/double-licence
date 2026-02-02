#!/usr/bin/env python3
import os, sys

def execvp_with_exception_handling(com, argv):
    try:
        os.execvp(com, argv)
    except FileNotFoundError:
        print(f"{argv[0]}: no such command: {argv[0]}", file=sys.stderr)
        sys.exit(2)
    except PermissionError:
        print(f"{argv[0]}: can't execute: {argv[0]}", file=sys.stderr)
        sys.exit(13)


def indice(liste, element, start):
    try:
        return liste.index(element, start)
    except ValueError:
        return -1

def usage(cmd):
    print(f"{cmd}: usage: {cmd} com1 ... --do com2 ... --done", file=sys.stderr)


if __name__ == "__main__":
    ind_do = indice(sys.argv, "--do", 2)
    ind_done = indice(sys.argv, "--done", ind_do + 2)
    if ind_do == -1 or ind_done != len(sys.argv) - 1:
        usage(sys.argv[0])
        sys.exit(1)
    status_com2 = 0
    while True:
        # On va exécuter com1
        if os.fork() == 0:  # Fils 1
            execvp_with_exception_handling(sys.argv[1], sys.argv[1:ind_do])
        # Suite père
        pid, status_com1 = os.wait()  # attente résultat com1
        if os.WIFEXITED(status_com1):
            if os.WEXITSTATUS(status_com1) != 0:
                sys.exit(status_com2)
            # On va exécuter com2
            if os.fork() == 0:  # Fils 2
                os.execvp(sys.argv[ind_do + 1], sys.argv[ind_do + 1 : ind_done])
            # Suite père
            pid, status_com2 = os.wait()
