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

int moyenne_stdin(void) {
    double notes;
    double somme;
    double acc;
    printf("Entre les notes (lettre pour arreter)");
    while (1){
        notes = lire_nombre();
        if (notes == -1){
            break;
        }
        else if (0<=notes && notes <= 20){
            somme += notes;
            acc += 1;
        }
        else {
            continue;
        }
    }
    return (double) somme / acc;
}

void eucl(int a, int b){
    int reste = a%b;
    int quotient = a/b;
    if (b==0) {
        printf("Pas de division par 0 \n");

    }
    else {
        printf("%i = %i x %i + %i \n",a,b,quotient,reste);

    }
}

void eucl_deci(int a, int b){
    float quotient = (float) a/b;
    if (b==0) {
        printf("Pas de division par 0 \n");

    }
    else {
        printf("%i = %i x %f \n",a,b,quotient);

    }
}

void question7(int a, int b) {
    if (b == 0) {
        printf("division par zéro\n");
        return;
    }

    if (a % b == 0) {
        printf("%d/%d = %d (exacte)\n", a, b, a / b);
    } 
    else {
        printf("%d/%d = %f (approchée)\n", a, b, (float)a / b);
    }
}

int main(void){
    question7(25,10);
    return 0;
}