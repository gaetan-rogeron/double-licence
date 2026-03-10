import sys
import time
import subprocess

def main():
    args = sys.argv[1:]
    if not args:
        print("Usage: python mytime.py [-n k] [-s] commande [arg...]")
        sys.exit(1)

    k_times = 1
    show_status = False

    while args and args[0].startswith('-'):
        if args[0] == '-s':
            show_status = True
            args.pop(0)
        elif args[0] == '-n':
            args.pop(0)
            if args:
                k_times = int(args.pop(0))
            else:
                print("Err: l'option -n valeur entière.")
                sys.exit(1)
        else:
            break
            
    commande = args
    if not commande:
        print("Err: aucune commande")
        sys.exit(1)

    if k_times <= 0:
        print("Err: la valeur de k doit être > 0.")
        sys.exit(1)

    total_time = 0.0

    for i in range(k_times):
        start_time = time.time() 
        
        process = subprocess.run(commande)
        
        end_time = time.time() 
        duration = end_time - start_time
        total_time += duration

        print(f"Exécution {i+1} : durée = {duration:.6f} s")
        if show_status:
            print(f"Code sortie : {process.returncode}")

    if k_times > 1:
        print(f"durée moyenne sur {k_times} exécutions : {total_time / k_times:.6f} s")

if __name__ == '__main__':
    main()