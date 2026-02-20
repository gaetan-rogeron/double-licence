#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *notes;
    int taille;
    int n;
} bulletin;

bulletin nouveau(int taille){
    bulletin res;
    int *tab = malloc(taille * sizeof(int));
    res.taille = taille;
    res.notes = tab;
    res.n = 0;
    return res;
}

void liberer_memoire(bulletin b){
    free(b.notes);
}

int ajout_simple(bulletin *b, int note){
    if (note < 0 || note > 20 ){
        return -1;
    }
    if (b->n>= b->taille){
        return -2;
    }
    b->notes[b->n] = note;
    b->n ++;
    return 0;
}

void afficher_bulletin(bulletin b){
    int i;
    i=0;
    printf("%d/%d ",b.n, b.taille);
    printf("[");
    while(i < b.n-1){
        printf("%d, ", b.notes[i]);
        i++;
    }
    printf("%d]\n", b.notes[b.n -1]);
}

int min_bulletin(bulletin b){
    int i;
    int index;
    i = 0;
    index = 0;
    while(i < b.n){
        if(b.notes[i]< b.notes[index]){
            index = i;
        }
        i++;
    }

    return index;

}


void ajout(bulletin b, int note){
    int index_min;
    if (b.n == b.taille){
        index_min = min_bulletin(b);
        if (note > b.notes[index_min]){
            b.notes[index_min] = note;
        } 
    }
    ajout_simple(&b,note);
}

void test(){
    bulletin bul;
    bul = nouveau(3);
    
    ajout_simple(&bul, 3);
    ajout_simple(&bul, 5);
    ajout_simple(&bul, 1);
    ajout(bul, 9);
    
    afficher_bulletin(bul);
    liberer_memoire(bul);
}

int main(){
    test();
    return 0;
}