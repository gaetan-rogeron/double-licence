#!/usr/bin/env python3
import os, sys

print(f"PERE PID : {os.getpid()}, PPDID : {os.getppid()}")
for i in range(3):
    fils = os.fork()
    if fils == 0:
        print(f"FILS {i} PID : {os.getpid()}, PPDID : {os.getppid()}")
        if i==0:
            for i in range(2):
                petit_fils = os.fork()
                if petit_fils == 0 :
                    print(f"PETIT FILS {i} PID : {os.getpid()}, PPDID : {os.getppid()}")
                    sys.exit(0)
        sys.exit(0)
sys.exit(0)