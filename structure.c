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

Rafle * rechercherRafle(Rafle *rafle, int ligne, int colonne) {
    if(rafle == NULL) {
        return NULL;
    } else {
        Rafle *p = rafle;

        while(p != NULL) {
            if(p->cases.ligne == ligne && p->cases.colonne == colonne) {
                return p;
            }
            p = p->suivante;
        }
        return NULL;
    }
}

Rafle * rechercherRafleParIndice(Rafle *rafle, int indice) {
    int position = 1;

    if(rafle == NULL) {
        return NULL;
    } else {
        Rafle *p = rafle;

        while(p != NULL) {
            if(position == indice) {
                p->suivante = NULL;
                return p;
            }
            position += 1;
            p = p->suivante;
        }
        
        return NULL;
    }
}

Rafle * insererRafle(Rafle *rafle, Rafle *valeur) {
    
    if(rafle == NULL) {
        return valeur;
    } else if(valeur == NULL) {
        return rafle;
    } else {  
        Rafle *p = rafle;

        while(p->suivante != NULL) {
            p = p->suivante;
        }
        p->suivante = valeur;

        return supprimerRafleDoublons(rafle);
    }
}

// Rafle *supprimerRafleDoublons(Rafle *rafle) {
//     Rafle *courant = rafle, *precedent = NULL;


//     while(courant != NULL) {
//         Rafle *suivant = courant->suivante;

//         if (rechercherRafle(suivant, courant->cases.ligne, courant->cases.colonne) != NULL) { // Vérifier si l'élément courant est un doublon
//             if (precedent == NULL) { // Si le doublon est en tête de liste
//                 rafle = suivant;
//             } else {
//                 precedent->suivante = suivant;
//             }

//             free(courant);

//         } else {
//             precedent = courant;
//         }

//         courant = suivant;
//     }

//     return rafle;
// }

Rafle *supprimerRafleDoublons(Rafle *rafle) {
    Rafle *courant = rafle;

    while (courant != NULL) {
        Rafle *courantInterne = courant;

        while (courantInterne->suivante != NULL) { // Parcours des éléments après la case courante
            if ((courantInterne->suivante->cases.ligne == courant->cases.ligne) && (courantInterne->suivante->cases.colonne == courant->cases.colonne)) {
                Rafle *temp = courantInterne->suivante; // Suppression des cases dupliqués
                
                courantInterne->suivante = courantInterne->suivante->suivante;
                free(temp);
            } else {
                courantInterne = courantInterne->suivante;
            }
        }

        courant = courant->suivante;
    }

    return rafle;
}


Rafle * supprimerRafle(Rafle *rafle, int position) {
    int pos = 1;
    Rafle *last = NULL, *p = NULL;

    if(rafle == NULL) {
        printf("\nLa rafle est vide\n");
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

int longueurRafle(Rafle *rafle) {
    int longueur = 0;

    if(rafle == NULL) {
        return 0;
    } else {
        Rafle *p = rafle;

        while(p != NULL) {
            longueur += 1;
            p = p->suivante;
        }

        return longueur;
    }
}

void afficherRafle(Rafle *rafle) {
    Rafle *p = rafle;

    if(p == NULL) {
        printf("\n**** Vide ****\n");
    } else {
        while(p != NULL) {
            printf("(%d, %d)\n", p->cases.ligne, p->cases.colonne);
            p = p->suivante;
        }
        printf("\n");
    }
}

void libererMemoire(Damier *damier, Rafle *rafle) {

    if(damier != NULL) {
        free(damier);
    }
   
    while (rafle != NULL) { // Libération de la mémoire des rafles
        Rafle *suivant = rafle->suivante;

        free(rafle);
        rafle = suivant;
    }
}
