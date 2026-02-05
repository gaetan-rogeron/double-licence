#include <stdio.h>

typedef enum {
    entier,
    decimal
} typage; 

typedef union {
    int ent;
    float dec;
} valeur;

typedef struct {
    typage t;
    valeur v;
} nombre;

nombre nombre_entier(int i){
    nombre a;
    a.t = entier;
    a.v.ent = i;
    return a;
} 

nombre nombre_decimal(float f){
    nombre a;
    a.t = decimal;
    a.v.dec = f;
    return a;
}

int est_entier(nombre n){
    return n.t == entier;
}

int est_decimal(nombre n){
    return n.t == decimal;
}

void afficher_nombre(nombre n){
    switch(n.t){
        case entier:
            printf("%d", n.v.ent);
            break;
        case decimal:
            printf("%.2f",n.v.dec);
            break;
    }
}

nombre somme(nombre a, nombre b){
    nombre x;
    if (est_entier(a) & est_entier(b)){
        return nombre_entier(a.v.ent + b.v.ent);
    }
    else {
        float val_a = (a.t == entier) ? (float)a.v.ent : a.v.dec;
        float val_b = (b.t == entier) ? (float)b.v.ent : b.v.dec;
        return nombre_decimal(val_a + val_b);
    }
}

nombre division(nombre a, nombre b){
if (a.t == entier && b.t == entier && b.v.ent != 0 && (a.v.ent % b.v.ent == 0)) {
        return nombre_entier(a.v.ent / b.v.ent);
    } else {
        float val_a = (a.t == entier) ? (float)a.v.ent : a.v.dec;
        float val_b = (b.t == entier) ? (float)b.v.ent : b.v.dec;
        
        if (val_b == 0.0f) {
            printf("Erreur : Division par zéro.\n");
            return nombre_entier(0); 
        }
        return nombre_decimal(val_a / val_b);
    }
}

nombre moyenne(nombre notes[], int taille){
if (taille <= 0) return nombre_entier(0);

    nombre total = nombre_entier(0);
    for (int i = 0; i < taille; i++) {
        total = somme(total, notes[i]);
    }
    return division(total, nombre_entier(taille));
}

int main(void){
nombre n1 = nombre_entier(10);
    nombre n2 = nombre_entier(5);
    nombre n3 = nombre_decimal(2.5);

    printf("Test Affichage :\n");
    printf("n1 (entier) : "); afficher_nombre(n1); printf("\n");
    printf("n3 (decimal) : "); afficher_nombre(n3); printf("\n\n");

  
    nombre s1 = somme(n1, n2); 
    printf("Somme 10 + 5 : "); afficher_nombre(s1); 
    printf(" (Type: %s)\n", est_entier(s1) ? "entier" : "decimal");

    nombre s2 = somme(n1, n3); 
    printf("Somme 10 + 2.5 : "); afficher_nombre(s2); 
    printf(" (Type: %s)\n\n", est_entier(s2) ? "entier" : "decimal");

    nombre d1 = division(n1, n2); 
    printf("Division 10 / 5 : "); afficher_nombre(d1); 
    printf(" (Type: %s)\n", est_entier(d1) ? "entier" : "decimal");

    nombre d2 = division(nombre_entier(10), nombre_entier(4));
    printf("Division 10 / 4 : "); afficher_nombre(d2); 
    printf(" (Type: %s)\n\n", est_entier(d2) ? "entier" : "decimal");

    nombre notes1[] = {nombre_entier(10), nombre_entier(5), nombre_entier(15)};
    nombre moy1 = moyenne(notes1, 3);
    printf("Moyenne {10, 5, 15} : "); afficher_nombre(moy1);
    printf(" (Type: %s)\n", est_entier(moy1) ? "entier" : "decimal");

    nombre notes2[] = {nombre_entier(10), nombre_entier(5), nombre_entier(15), nombre_entier(12), nombre_entier(9)};
    nombre moy2 = moyenne(notes2, 5); 
    printf("Moyenne {10, 5, 15, 12, 9} : "); afficher_nombre(moy2);
    printf(" (Type: %s)\n", est_entier(moy2) ? "entier" : "decimal");

    return 0;
}