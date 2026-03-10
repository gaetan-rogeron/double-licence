#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct cellule {
    int contenu;
    struct cellule *suivant;
} cellule;

typedef struct {
    cellule *premier;
} liste;

liste nouvelle_liste() {
    liste L;
    L.premier = NULL;
    return L;
}

void liberer_liste(liste L) {
    cellule *courant = L.premier;
    cellule *suivant;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

int est_vide(liste L) {
    return L.premier == NULL;
}

void ajout_debut(liste *L, int x) {
    cellule *nouvelle = malloc(sizeof(cellule));
    if (nouvelle == NULL) {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(1);
    }
    nouvelle->contenu = x;
    nouvelle->suivant = L->premier;
    L->premier = nouvelle; 
}


void afficher_liste(liste L) {
    cellule *courant = L.premier;
    while (courant != NULL) {
        printf("[%d] -> ", courant->contenu);
        courant = courant->suivant;
    }
    printf("NULL\n");
}






void ajout_fin(liste *L, int x) {
    cellule *nouvelle = malloc(sizeof(cellule));
    if (nouvelle == NULL) exit(1);
    nouvelle->contenu = x;
    nouvelle->suivant = NULL;

    if (est_vide(*L)) {
        L->premier = nouvelle;
    } else {
        cellule *courant = L->premier;
        while (courant->suivant != NULL) { 
            courant = courant->suivant;
        }
        courant->suivant = nouvelle;
    }
}

int longueur(liste L) {
    int taille = 0;
    cellule *courant = L.premier;
    while (courant != NULL) {
        taille++;
        courant = courant->suivant;
    }
    return taille;
}


int pop_liste(liste *L, int *x) {
    cellule *a_supprimer; 
    
    if (est_vide(*L)) {
        return -1; 
    }
    
    a_supprimer = L->premier; 
    *x = a_supprimer->contenu;
    L->premier = a_supprimer->suivant;
    free(a_supprimer);
    return 0;
}






liste tableau_vers_liste(int tableau[], int taille) {
    liste L;
    int i; 
    
    L = nouvelle_liste();
    for (i = taille - 1; i >= 0; i--) {
        ajout_debut(&L, tableau[i]);
    }
    return L;
}

int lire_valeur(liste L, int i, int *x) {
    cellule *courant = L.premier;
    int index = 0;
    while (courant != NULL && index < i) {
        courant = courant->suivant;
        index++;
    }
    if (courant == NULL) return -1;
    *x = courant->contenu;
    return 0;
}

int inserer(liste *L, int x, int i) {
    cellule *courant;
    int index;
    cellule *nouvelle; 

    if (i == 0) {
        ajout_debut(L, x);
        return 0;
    }
    
    courant = L->premier;
    index = 0;
    
    while (courant != NULL && index < i - 1) {
        courant = courant->suivant;
        index++;
    }
    
    if (courant == NULL) return -1;
    
    nouvelle = malloc(sizeof(cellule));
    if (nouvelle == NULL) exit(1);
    
    nouvelle->contenu = x;
    nouvelle->suivant = courant->suivant;
    courant->suivant = nouvelle;
    return 0;
}

int max(liste L, int *x) {
    int index_max;
    int index_courant;
    cellule *courant; 

    if (est_vide(L)) return -1;
    
    index_max = 0;
    index_courant = 0;
    *x = L.premier->contenu; 
    courant = L.premier;
    
    while (courant != NULL) {
        if (courant->contenu > *x) {
            *x = courant->contenu;
            index_max = index_courant;
        }
        courant = courant->suivant;
        index_courant++;
    }
    return index_max;
}

void map(liste L, int (*f)(int)) {
    cellule *courant = L.premier;
    while (courant != NULL) {
        courant->contenu = f(courant->contenu);
        courant = courant->suivant;
    }
}

void supprimer(liste *L, int (*f)(int)) {
    cellule *a_supprimer;
    cellule *precedent;
    cellule *courant;

    if (L == NULL || est_vide(*L)) {
        return;
    }

    while (!est_vide(*L) && f(L->premier->contenu)) {
        a_supprimer = L->premier;
        L->premier = L->premier->suivant; 
        free(a_supprimer);                
    }

    if (est_vide(*L)) {
        return;
    }

    precedent = L->premier;
    courant = L->premier->suivant;

    while (courant != NULL) {
        if (f(courant->contenu)) {
            precedent->suivant = courant->suivant;
            free(courant);
            courant = precedent->suivant;
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}

int main(void){
    return 0;
}