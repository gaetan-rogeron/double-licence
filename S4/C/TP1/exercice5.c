#include <stdio.h>

int lire_entier(void) {
    char c;
    int resultat = 0;
    int valide = 1;
    int chiffre = 0;

    printf("ENTIER> "); 
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c >= '0' && c <= '9') {
            resultat = resultat * 10 + (c - '0');
            chiffre = 1;
        } else {
            valide = 0;
        }
    }

    if (valide == 1 && chiffre == 1) {
        return resultat;
    } else {
        return -1;
    }
}

void pyramide(int n) {
    int i, j;
        for (i = 1; i <= n; i++) {
        for (j = 0; j < n - i; j++) {
            printf(" ");
        }

        for (j = 0; j < (2 * i - 1); j++) {
            printf("*");
        }
        printf("\n");
    }
}

int main(void) {
    int n;

    while (1) {
        n = lire_entier();
        if (n == -1) {
            break; 
        }

        pyramide(n);
    }

    return 0;
}