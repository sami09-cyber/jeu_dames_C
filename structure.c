#include "structure.h"

Damier * creerDamier() {
    Damier *damier = NULL;

    damier = (Damier *) malloc(sizeof(Damier));

    damier->nombrePionVert = NOMBRE_PION_VERT;
    damier->nombrePionRouge = NOMBRE_PION_ROUGE;

    for(int i = 0; i < DIMENSION_PLATEAU; i++) {
        for(int j = 0; j < DIMENSION_PLATEAU; j++) {
            damier->plateau[i][j] = CASE_VIDE;
        }
    }

    return damier;
}

Rafle * creerRafle(int ligne, int colonne) {
    Rafle *rafle = NULL;

    rafle = (Rafle *) malloc(sizeof(Rafle));

    rafle->cases.ligne = ligne;
    rafle->cases.colonne = colonne;
    rafle->suivante = NULL;

    return rafle;
}

Rafle * insererRafle(Rafle *rafle, Rafle *valeur) {
    
    if(rafle == NULL) {
        return valeur;
    } else {
        valeur->suivante = rafle;
        
        return valeur;
    }
}

Rafle * supprimerRafle(Rafle *rafle, int position) {
    int pos = 1;
    Rafle *last = NULL, *p = NULL;

    if(rafle == NULL) {
        printf("La rafle est vide");
    } else if(position == pos) {
        p = rafle;
        rafle = rafle->suivante;
        free(p);
    } else {
        p = rafle;
        while(p != NULL && pos < position) {
            last = p;
            p = p->suivante;
            pos += 1;
        }

        if(p != NULL) {
            last->suivante = p->suivante;
            free(p);
        }
    }

    return rafle;
}