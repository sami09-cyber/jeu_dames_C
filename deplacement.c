#include "deplacement.h"


void deplacerPion(Damier *damier, Deplacement deplacement, Rafle *rafle, int couleurPion) {
    
    if(rafle == NULL) { // C'est un simple deplacement
        damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
        damier->plateau[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] = couleurPion;
    } else {
        Rafle *prises = rafle;

        while(prises != NULL) {
            damier->plateau[prises->cases.ligne][prises->cases.colonne] = CASE_VIDE;
            
            if(couleurPion == PION_VERT) {
                damier->nombrePionVert -= 1; 
            } else {
                damier->nombrePionRouge -= 1; 
            }
            prises = prises->suivante;
        }
        damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
        damier->plateau[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] = couleurPion;
   }    
}

/*
    1 : Prise avant verifiee
    2 : Prise arriere verifiee
*/ 

int verifierPrise(Case caseInitiale, Case casePrise) {
    int ligneAvantVerifie = (caseInitiale.ligne - casePrise.ligne == 1) ? 1 : 0;
    int ligneArriereVerifie = (caseInitiale.ligne - casePrise.ligne == -1) ? 1 : 0;
    int colonneAvantVerifie = (caseInitiale.colonne - casePrise.colonne == -1) ? 1 : 0;
    int colonneArriereVerifie = (caseInitiale.colonne - casePrise.colonne == 1) ? 1 : 0;

    if(ligneAvantVerifie && colonneAvantVerifie) {
        return 1;
    } else if(ligneArriereVerifie && colonneArriereVerifie) {
        return 2;
    } else {
        return 0;
    }
}

void promouvoirPion(Damier *damier, Case cases, int couleurPion) {
    if(couleurPion == PION_VERT) {
        damier->plateau[cases.ligne][cases.colonne] = 2*PION_VERT;
    } else {
        damier->plateau[cases.ligne][cases.colonne] = 2*PION_ROUGE;
    }
}

void deplacerDame(Damier *damier, Deplacement deplacement, int couleurDame) {
    
    damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
    damier->plateau[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] = couleurDame;
}
/*
    -1 : On ne pas enjambe son propre pion
*/ 
// int verifierDeplacementDame(Damier *damier, Deplacement deplacement, int couleurDame) {
//     for(int i = deplacement.caseInitiale.ligne; i < deplacement.caseFinale.ligne; i++) {
//         for(int j = deplacement.caseInitiale.colonne; j < deplacement.caseFinale.colonne; j++) {
//             if((i + j) % 2 == 0) { // Selection des cases blanches
//                 if(deplacement.caseInitiale.ligne < deplacement.caseFinale.ligne) {
//                 if(deplacement.caseInitiale.colonne < deplacement.caseFinale.colonne) {
//                     if(damier->plateau[i + 1][j + 1] == couleurDame/2) {
//                         return -1;
//                     }
//                 } else {
//                     if(damier->plateau[i + 1][j - 1] == couleurDame/2) {
//                         return -1;
//                     }
//                 }
//             } else {
//                 if(deplacement.caseInitiale.colonne < deplacement.caseFinale.colonne) {
//                     if(damier->plateau[i + 1][j + 1] == couleurDame/2) {
//                         return -1;
//                     }
//                 } else {
//                     if(damier->plateau[i + 1][j - 1] == couleurDame/2) {
//                         return -1;
//                     }
//                 }
//             }
//             }

            
//         }
//     }
// }

int verifierCaseValide(int ligne, int colonne) { // La case doit etre comprise entre 0 et la dimension du plateau - 1
    return (ligne >= 0 && ligne < DIMENSION_PLATEAU) && (colonne >= 0 && colonne < DIMENSION_PLATEAU);
}

Rafle * trouverDeplacementPionPossible(Damier *damier, int couleurPion) {
    Rafle *rafle = NULL;

    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if((i + j) % 2 == 0) { // Selection des cases blanches
                if((damier->plateau[i][j] == PION_VERT) && (couleurPion == PION_VERT)) { // Selection des pions Verts
                    if(verifierCaseValide(i + 1, j - 1) && damier->plateau[i + 1][j - 1] == CASE_VIDE) { // Deplacement a gauche possible
                        rafle = insererRafle(rafle, creerRafle(i + 1, j - 1));
                    } else if(verifierCaseValide(i + 1, j + 1) && damier->plateau[i + 1][j + 1] == CASE_VIDE) { // Deplacement a droite possible
                        rafle = insererRafle(rafle, creerRafle(i + 1, j + 1));
                    }
                } else if((damier->plateau[i][j] == PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des pions Rouges
                    if(verifierCaseValide(i - 1, j + 1) && damier->plateau[i - 1][j + 1] == CASE_VIDE) { // Deplacement a gauche possible
                        rafle = insererRafle(rafle, creerRafle(i - 1, j + 1));
                    } else if(verifierCaseValide(i - 1, j - 1) && damier->plateau[i - 1][j - 1] == CASE_VIDE) { // Deplacement a droite possible
                        rafle = insererRafle(rafle, creerRafle(i - 1, j - 1));
                    }
                }
            }
        }
    }

    return rafle;
}

