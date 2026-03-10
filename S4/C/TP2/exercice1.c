#include <stdio.h>

void affiche_tableau(int tab[], int n){
    int i;
    printf("[ ");
    for(i=0;i<n;i++){
        printf("%i%s ",tab[i], (i<n-1) ? ", " : "");
    }
    printf("] \n");
}

void question1(){
    int tab1[] = {1,2,3,4,5,6};
    printf("tab = [1,2,3,4,5,6], result : \n");
    printf("n = 1 : ");
    affiche_tableau(tab1,1);
    printf("n = 2 : ");
    affiche_tableau(tab1,2);
    printf("n = 3 : ");
    affiche_tableau(tab1,3);
    printf("n = 4 : ");
    affiche_tableau(tab1,4);
}

void vider_buffer() {
    char c;
    while ( (c = getchar()) != '\n' && c != EOF);
}

int lire_entier() {
    int n = 0;
    char c;
    printf("entier> ");
    while ( (c = getchar()) != '\n' && c != EOF) {
        if ('0' <= c && c <= '9') {
        n = n*10 + (c-'0');
        } else {
            vider_buffer();
            return -1;
        }
    }
    return n;
}

int saisie_tab(int tableau[]){
    int nb = 0;
    while (1){
        int val = lire_entier();
        if (val == -1) {
            break;
        }
        else {
            tableau[nb] = val;
            nb++;
        }
    }
    return nb;
}

void question2(){
    int tab[100];
    int n;
    n = saisie_tab(tab);
    affiche_tableau(tab,n);
}

int main(){
    question1();
    question2();
    return 0;
}