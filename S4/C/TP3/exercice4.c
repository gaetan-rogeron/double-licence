#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* memoire;
    int taille;
    int n;
} tableau;

tableau * nouveau_tableau(int taille){
    tableau *t;
    t->taille = taille;
    t->memoire = malloc(taille * sizeof(int));
    t->n = 0;
    return t;
}

void liberer_tableau(tableau *t){
    free(t->memoire);
}

void afficher_tableau(tableau *t){
    int i;
    i=0;
    printf("%d/%d ",t->n, t->taille);
    printf("[");
    while(i < t->n-1){
        printf("%d, ", t->memoire[i]);
        i++;
    }
    printf("%d]\n", t->memoire[t->n -1]);
}

void ajout_simple(){

}

void agrandir(){

}

int inserer(){
    return 0;
}

int supprimer(){
    return 0;
}

void supprimer_doublon(){

}


int main(){
    return 0;
}