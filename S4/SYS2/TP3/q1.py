import os
argv = ["ls", "-lt", "/"]
os.execv("/bin/ls", argv)

# Cette commande exectute la commande 'ls -lt /'
