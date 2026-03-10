import time
import signal
import sys

def capter_INT(sig_num, frame):
    print("\nOuch!")
    
    signal.alarm(5)
    
    signal.signal(signal.SIGINT, traitant)
    

def capter_ALRM(sig_num, frame):
    print("\nTemps écoulé (Alarme reçue) ! Fin du programme.")
    sys.exit(0)

if __name__ == '__main__':
    traitant = signal.getsignal(signal.SIGINT)


    signal.signal(signal.SIGINT, capter_INT)
    signal.signal(signal.SIGALRM, capter_ALRM)


    signal.alarm(10)

    while True:
        time.sleep(1)
        print("Alive!")