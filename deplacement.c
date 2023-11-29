#include "deplacement.h"


int deplacerPion(Damier *damier, Deplacement deplacement, Rafle *rafle, int couleurPion) {
    /*
    -1: Le poin n'appartient pas au joeur
    -2: Case vide
    -3: Case occupee
    -4: Mauvaise Ligne
    -5: Mauvaise Colonne
    -6: Prise impossible car le pion appartient au joeur
    +1: deplacement possible
    */ 

    if(rafle == NULL) { // C'est un simple deplacement
        if(damier[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] != couleurPion) { // Le poin n'appartient pas au joeur
        return -1;
        } if(damier[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] == CASE_VIDE){ // La case vide
            return -2;
        } else if(damier[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] != CASE_VIDE) { // La case occupee
            return -3;
        } else if(deplacement.caseInitiale.ligne - deplacement.caseFinale.ligne != 1) { // La ligne est mauvaise
            return -4;
        } else if(deplacement.caseInitiale.colonne - deplacement.caseFinale.colonne != 1) { // La colonne est mauvaise
            return -5;
        } else { // On peut effectuer un deplacement d'une case
            damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
            damier->plateau[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] = couleurPion;
        }
    } else {
        Rafle *prises = rafle;

        while(prises != NULL) {
            if(damier[prises->cases.ligne][prises->cases.colonne] != couleurPion) { // Le poin n'appartient pas au joeur : Prise possible
                
                if(verifierPrise(deplacement.caseInitiale, prises->cases) == 1) { // Prise avant
                    damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
                    damier->plateau[deplacement.caseFinale.ligne - 2][deplacement.caseFinale.colonne + 2] = couleurPion;
                } else if(verifierPrise(deplacement.caseInitiale, prises->cases) == 2) { // Prise Arriere
                    damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
                    damier->plateau[deplacement.caseInitiale.ligne + 2][deplacement.caseInitiale.colonne - 2] = couleurPion;
                }
            } else { // Le poin appartient au joeur : Prise impossible
                return -6;
            }
            deplacerPion();
            prises = prises->suivante;
        }
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
