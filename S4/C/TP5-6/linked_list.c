#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*PART 1*/
struct cellule{
    int contenu;
    struct cellule *suivant;
};

typedef struct cellule* liste_chainee;


/*--------------------------------------------*/
/*PART 2*/

liste_chainee nouvelle_lc(){
    return NULL;
}

int est_vide(liste_chainee L){
    return L==NULL;
}

int head(liste_chainee L){
    if (est_vide(L)){
        printf("La liste est vide.");
        exit(1);
    }
    return L->contenu;
}

liste_chainee tail(liste_chainee L){
    if (est_vide(L)){
        printf("La liste est vide.");
        exit(1);
    }
    return L->suivant;
}

liste_chainee ajout_lc(int x, liste_chainee L){
    liste_chainee L2 = malloc(sizeof(struct cellule));

    if (L2 == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
    }

    L2->contenu= x;
    L2->suivant= L;
    return L2;
}

void liberer_lc(liste_chainee L){
    if (!est_vide(L)){
        liberer_lc(tail(L));
        free(L);
    }
}



/*--------------------------------------------*/
/*PART 3*/


void affiche_lc(liste_chainee L){
    if (est_vide(L)){
        printf("NULL\n");
    }else{
        printf("[%d] -> ",head(L));
        affiche_lc(tail(L));
    }
}

int longueur_lc(liste_chainee L){
    if (est_vide(L)){
        return 0;
    }
    else {
        return 1 + longueur_lc(tail(L));
    }
}

liste_chainee copie_lc(liste_chainee L) {
    if (est_vide(L)) {
        return nouvelle_lc();
    } else {
        return ajout_lc(head(L), copie_lc(tail(L)));
    }
}

liste_chainee ajout_fin_lc(liste_chainee L, int x) {
    if (est_vide(L)) {
        return ajout_lc(x, nouvelle_lc());
    } else {
        return ajout_lc(head(L), ajout_fin_lc(tail(L), x));
    }
}

int max_lc(liste_chainee L) {
    if (est_vide(L)) {
        return -INT_MAX - 1;
    } else {
        int max_reste = max_lc(tail(L));
        int tete = head(L);
        
        if (tete > max_reste) {
            return tete;
        } else {
            return max_reste;
        }
    }
}

liste_chainee map_lc(liste_chainee L, int (*f)(int)) {
    if (est_vide(L)) {
        return nouvelle_lc();
    } else {
        return ajout_lc(f(head(L)), map_lc(tail(L), f));
    }
}



void test(){
    liste_chainee L = nouvelle_lc();
    L = ajout_lc(20,L); 
    L = ajout_lc(1,L);
    L = ajout_lc(17,L); 
    affiche_lc(L);
}

int main(void){
    test();
    return 0;
}