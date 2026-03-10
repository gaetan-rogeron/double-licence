import sys
import signal
import atexit
import time

def nettoyage_final():
    print("\n[atexit] message ")

def forcer_exit(sig_num, frame):
    print(f"\nSignal {sig_num} reçu. Fermeture")
    sys.exit(0)

if __name__ == '__main__':
    atexit.register(nettoyage_final)

    signaux_a_capter = [signal.SIGQUIT, signal.SIGINT, signal.SIGABRT, signal.SIGTERM]
    for sig in signaux_a_capter:
        signal.signal(sig, forcer_exit)

    print("exécution. envoyer signal ou attendez 5s")
    try:
        time.sleep(5)
        print("Fin normale.")
        sys.exit(0)
    except Exception as e:
        print("Une erreur s'est produite.")
        sys.exit(1)