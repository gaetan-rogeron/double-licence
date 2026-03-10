import time
import signal
import os

def capter_INT(sig_num, frame):
    print("\nSignal SIGINT recu")

if __name__ == '__main__':
    signal.signal(signal.SIGINT, capter_INT)
    
    print(f"Mon PID est : {os.getpid()}")

    print("Test avec time.sleep(30)")
    time.sleep(30)
    print("Sortie de sleep()")
    
    print("Test avec signal.pause()")
    signal.pause()
    print("Sortie de pause()")