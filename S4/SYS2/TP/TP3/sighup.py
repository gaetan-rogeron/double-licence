import time
import signal
import os

if __name__ == '__main__':
    print(f"Mon PID est : {os.getpid()}")
    
    signal.signal(signal.SIGHUP, signal.SIG_IGN)
    
    print("Pas de fermeture du terminal")
    while True:
        time.sleep(2)
        print("Arrière-plan")