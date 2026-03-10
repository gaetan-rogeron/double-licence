#include <stdio.h>

struct horaire_struct {
    short heures, minutes, secondes;
};

typedef struct horaire_struct horaire;

horaire nouvel_horaire(short h, short m, short s){
    horaire a;
    a.heures = h;
    a.minutes = m;
    a.secondes = s;
    return a;
}

void afficher_horaire(horaire h){
    printf("%dh %dm %ds \n", h.heures, h.minutes, h.secondes);
}

horaire ajout(horaire h1, horaire h2){
    horaire h;
    short sh = h1.heures + h2.heures;
    short sm = h1.minutes + h2.minutes;
    short ss = h1.secondes + h2.secondes;

    if ( ss >= 60 ){
        sm += 1;
    }
    h.secondes = ss % 60;
    if ( sm >= 60 ){
        sh += 1;
    }
    h.minutes = sm % 60;
    h.heures = sh % 24;
    return h;
}

horaire secondes_vers_horaire(int s){
    horaire h;
    h.heures = (s / 3600)%24;
    s -= h.heures*3600;
    h.minutes = (s / 60)%60;
    s -= h.minutes*60;
    h.secondes = s;
    return h;
}

int horaire_vers_secondes(horaire h){
    int s;
    s = h.heures*3600 + h.minutes*60 + h.secondes;
    return s;
}



void test(){
    horaire h;
    horaire h1;
    horaire h2;

    horaire res;

    int a;

    h1 = nouvel_horaire(1, 20, 35);
    afficher_horaire(h1);
    printf("+\n");
    h2 = nouvel_horaire(22, 40, 0);
    afficher_horaire(h2);
    printf("= \n");
    h = ajout(h1,h2);
    afficher_horaire(h);
    printf("__________________\n");

    res = secondes_vers_horaire(3650);
    printf("3650 secondes : ");
    afficher_horaire(res);
    printf("__________________\n");

    a = horaire_vers_secondes(h1);
    printf("horaire : ");
    afficher_horaire(h1);
    printf("secondes : %d \n", a);

}

int main(void){
    test();
    return 0;
}