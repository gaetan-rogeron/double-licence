#!/usr/bin/env python3
import os
import sys

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
    print(
        "{cmd}: usage: {cmd} com1 ... --then com2 ... [ --else com3 ... ] --fi",
        file=sys.stderr,
    )


if __name__ == "__main__":
    index_then = indice(sys.argv, "--then", 2)
    index_else = indice(sys.argv, "--else", index_then + 2)
    index_fi = indice(sys.argv, "--fi", max(index_then, index_else) + 2)
    if index_then == -1 or index_fi != len(sys.argv) - 1:
        usage(sys.argv[0])
        sys.exit(1)
    # On va exécuter com1
    if os.fork() == 0:  # Fils
        execvp_with_exception_handling(sys.argv[1], sys.argv[1:index_then])
    # Suite père
    pid, status = os.wait()
    if os.WIFEXITED(status):
        if os.WEXITSTATUS(status) == 0:
            a = index_then + 1
            b = index_else
        else:
            if index_else == -1:
                sys.exit(0)
            a = index_else + 1
            b = index_fi
        # on veut récupérer le code de sortie
        if os.fork() == 0:  # Fils
            execvp_with_exception_handling(sys.argv[a], sys.argv[a:b])
        # Suite père
        pid, status = os.wait()
        if os.WIFEXITED(status):
            print("code de sortie :", os.WEXITSTATUS(status))