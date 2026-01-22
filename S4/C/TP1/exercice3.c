#include <stdio.h>

int lire_nombre(void){
    char c;
    int resultat = 0;
    int valide = 1;
    int chiffre = 0;

    printf("ENTIER> ");

    while ((c= getchar()) != '\n' && c!= EOF){
        if (c>='0' && c<='9'){
            resultat = resultat * 10 + (c - '0');
            chiffre = 1;
        }
        else {
            valide=0;
        }
     
    }
    if (valide == 1 && chiffre == 1){
        return resultat;
    }
    else {
        return -1;
    }
    return 0;

}

int main(void){
    int valeur;
    for (;;) {
        valeur = lire_nombre();
        if (valeur == -1){
            printf("Ce n'est pas un chiffre.\n");
        }
        else {
            if (valeur %2 == 0){
                printf("L'entier %d est pair \n", valeur);
            }
            else {
                printf("L'entier %d est impair \n", valeur);
            }
        }
    }
    return 0;
}