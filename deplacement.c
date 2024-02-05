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

void deplacerDame(Damier *damier, Deplacement deplacement, Rafle *rafle, int couleurPion) {
    if(rafle == NULL) { // C'est un simple deplacement
        damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
        damier->plateau[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] = 2 * couleurPion;
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
        damier->plateau[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] = 2 * couleurPion;
    }
}

int verifierDeplacementJoueur(Damier *damier, Joueur joueur) {
    Rafle *deplacementsPions = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur.couleur, 1);
    Rafle *raflesPions = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur.couleur, 2);

    Rafle *deplacementsDames = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur.couleur, 1);
    Rafle *raflesDames = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur.couleur, 2);

    if(deplacementsPions == NULL && raflesPions == NULL && deplacementsDames == NULL && raflesDames == NULL) {
        return 0;
    }

    return 1;
}

void promouvoirPion(Damier *damier, Case cases, int couleurPion) {
    damier->plateau[cases.ligne][cases.colonne] = 2*couleurPion;
}

int verifierPromotionsPions(Damier *damier, int couleurPion) {
    for(int i = 0; i < DIMENSION_PLATEAU; i++) {
        for(int j = 0; j < DIMENSION_PLATEAU; j++) {
            if(verifierPromotionPion(damier, i, j, couleurPion)) {
                return 1;
            }
        }
    }

    return 0;
}

int verifierPromotionPion(Damier *damier, int ligne, int colonne, int couleurPion) {
    if(damier->plateau[ligne][colonne] == 2 * couleurPion) {
        return 1;
    } else {
        return 0;
    }
}

int verifierDeplacementDame(Damier *damier, Deplacement deplacement, int couleurDame) {
    for(int i = deplacement.caseInitiale.ligne; i < deplacement.caseFinale.ligne; i++) {
        for(int j = deplacement.caseInitiale.colonne; j < deplacement.caseFinale.colonne; j++) {
            if((i + j) % 2 == 0) { // Selection des cases blanches
                if(deplacement.caseInitiale.ligne < deplacement.caseFinale.ligne) {
                    if(deplacement.caseInitiale.colonne < deplacement.caseFinale.colonne) {
                        if(damier->plateau[i + 1][j + 1] == couleurDame/2) {
                            return -1;
                        }
                    } else {
                        if(damier->plateau[i + 1][j - 1] == couleurDame/2) {
                            return -1;
                        }
                    }
                } else {
                    if(deplacement.caseInitiale.colonne < deplacement.caseFinale.colonne) {
                        if(damier->plateau[i - 1][j + 1] == couleurDame/2) {
                            return -1;
                        }
                    } else {
                        if(damier->plateau[i - 1][j - 1] == couleurDame/2) {
                            return -1;
                        }
                    }
                }
            }
        }
    }

    return 1;
}

int verifierCaseValide(int ligne, int colonne) { // La case doit etre comprise entre 0 et la dimension du plateau - 1
    return (ligne >= 0 && ligne < DIMENSION_PLATEAU) && (colonne >= 0 && colonne < DIMENSION_PLATEAU);
}

int verifierCaseVide(Damier *damier, int ligne, int colonne) {
    return damier->plateau[ligne][colonne] == CASE_VIDE;
}

Rafle * trouverDeplacementsEtRaflesPossiblesPions(Damier *damier, int couleurPion, int choix) {
    Rafle *deplacements = NULL, *rafles = NULL, *pionDeplacements = NULL, *pionRafles = NULL, *deplacementRafles = NULL;
    
    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if((i + j) % 2 == 0) { // Selection des cases blanches
                deplacements = insererRafle(deplacements, deplacementEtRaflePossiblesPion(damier, i, j, couleurPion, 1));
                rafles = insererRafle(rafles, deplacementEtRaflePossiblesPion(damier, i, j, couleurPion, 4));
                pionDeplacements = insererRafle(pionDeplacements, deplacementEtRaflePossiblesPion(damier, i, j, couleurPion, 9));
                pionRafles = insererRafle(pionRafles, deplacementEtRaflePossiblesPion(damier, i, j, couleurPion, 14));
                deplacementRafles = insererRafle(deplacementRafles, deplacementEtRaflePossiblesPion(damier, i, j, couleurPion, 19));
            }
        }
    }

    switch (choix) {
        case 1: // Deplacement possible
            return deplacements;
        break;
        case 2: // Rafle possible
            return rafles;
        break;
        case 3: // Pions deplacables
            return pionDeplacements;
        break;
        break;
        case 4: // Pion pouvant rafler
            return pionRafles;
        break;
        break;
        case 5: // Deplacement possible des pions pouvant rafler
            return deplacementRafles;
        break;
        default:
            return NULL;
        break;
    }
}

Rafle * deplacementEtRaflePossiblesPion(Damier *damier, int ligne, int colonne, int couleurPion, int choix) {
    // Rafle *deplacement = NULL, *rafle = NULL, *pionDeplacement = NULL, *pionRafle = NULL, *deplacementRafle = NULL;
    Rafle *deplacement = NULL, *rafle = NULL, *pionDeplacement = NULL, *pionRafle = NULL, *deplacementRafle = NULL;
    Rafle *deplacementG = NULL, *rafleG = NULL;
    Rafle *deplacementD = NULL, *rafleD = NULL;
    Rafle *rafleAD = NULL;
    Rafle *rafleAG = NULL;
    Rafle *pionDeplacementG = NULL, *pionRafleG = NULL, *deplacementRafleG = NULL;
    Rafle *pionDeplacementD = NULL, *pionRafleD = NULL, *deplacementRafleD = NULL;
    Rafle *pionDeplacementAD = NULL, *pionRafleAD = NULL, *deplacementRafleAD = NULL;
    Rafle *pionDeplacementAG = NULL, *pionRafleAG = NULL, *deplacementRafleAG = NULL;

    if((damier->plateau[ligne][colonne] == PION_VERT) && (couleurPion == PION_VERT)) { // Selection des pions Verts
        if(verifierCaseValide(ligne + 1, colonne - 1)) { // Deplacement a gauche possible
            if(damier->plateau[ligne + 1][colonne - 1] == CASE_VIDE) {
                pionDeplacementG = insererRafle(pionDeplacementG, creerRafle(ligne, colonne));
                deplacementG = insererRafle(deplacementG, creerRafle(ligne + 1, colonne - 1));

                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne - 1));
            } else if((damier->plateau[ligne + 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
                damier->plateau[ligne + 2][colonne - 2] = PION_VERT; // On suppose que la prise est bonne, donc on avance
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 4); // Verification d'une rafle disponible

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE; // Fin du supposition
                }

                pionRafleG = insererRafle(pionRafleG, creerRafle(ligne, colonne));
                rafleG = insererRafle(rafleG, creerRafle(ligne + 1, colonne - 1));
                deplacementRafleG = insererRafle(deplacementRafleG, creerRafle(ligne + 2, colonne - 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne - 2));

                if(recursif != NULL) { // Recherche de toutes les rafles disponibles recursivements
                    pionRafleG = insererRafle(pionRafleG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 14)); // On insere tous les pions rafles possible a la pionRafleG
                    rafleG = insererRafle(rafleG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 4)); // On insere tous les rafles possible a la rafleG
                    deplacementRafleG = insererRafle(deplacementRafleG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 19)); // On insere tous les deplacement rafles possible a la deplacementRafleG

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 14)); 
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 4)); 
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 19)); 
                }

                if(choix < 14 && choix > 18) {
                    damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE; // Fin du supposition
                }
            }
        }

        if(verifierCaseValide(ligne + 1, colonne + 1)) { // Deplacement a droite possible
            if(damier->plateau[ligne + 1][colonne + 1] == CASE_VIDE) {
                pionDeplacementD = insererRafle(pionDeplacementD, creerRafle(ligne, colonne));
                deplacementD = insererRafle(deplacementD, creerRafle(ligne + 1, colonne + 1));

                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne + 1));
            } else if((damier->plateau[ligne + 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
                damier->plateau[ligne + 2][colonne + 2] = PION_VERT;

                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 4);

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE; 
                }

                pionRafleD = insererRafle(pionRafleD, creerRafle(ligne, colonne));
                rafleD = insererRafle(rafleD, creerRafle(ligne + 1, colonne + 1));
                deplacementRafleD = insererRafle(deplacementRafleD, creerRafle(ligne + 2, colonne + 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafleD = insererRafle(pionRafleD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 14));
                    rafleD = insererRafle(rafleD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 4));
                    deplacementRafleD = insererRafle(deplacementRafleD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 19));

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 19));
                }

                if(choix < 14 || choix > 18) {
                    damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE; 
                }
            }
        }


        if(verifierCaseValide(ligne - 1, colonne + 1)) { // Rafle arriere a droite possible
            if((damier->plateau[ligne - 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { 
                damier->plateau[ligne - 2][colonne + 2] = PION_VERT;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 4);

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE; 
                }

                pionRafleAD = insererRafle(pionRafleAD, creerRafle(ligne, colonne));
                rafleAD = insererRafle(rafleAD, creerRafle(ligne - 1, colonne + 1));
                deplacementRafleAD = insererRafle(deplacementRafleAD, creerRafle(ligne - 2, colonne + 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafleAD = insererRafle(pionRafleAD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 14));
                    rafleAD = insererRafle(rafleAD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 4));
                    deplacementRafleAD = insererRafle(deplacementRafleAD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 19));

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 19));
                }

                if(choix < 14 || choix > 18) {
                    damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE; 
                }
            }
        }

        if(verifierCaseValide(ligne - 1, colonne - 1)) { // Rafle arriere a gauche possible
            if((damier->plateau[ligne - 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { 
                damier->plateau[ligne - 2][colonne - 2] = PION_VERT;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 4);

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE; 
                }

                pionRafleAG = insererRafle(pionRafleAG, creerRafle(ligne, colonne));
                rafleAG = insererRafle(rafleAG, creerRafle(ligne - 1, colonne - 1));
                deplacementRafleAG = insererRafle(deplacementRafleAG, creerRafle(ligne - 2, colonne - 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne - 2));

                if(recursif != NULL) {
                    pionRafleAG = insererRafle(pionRafleAG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 14));
                    rafleAG = insererRafle(rafleAG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 4));
                    deplacementRafleAG = insererRafle(deplacementRafleAG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 19));

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 19));
                }

                if(choix < 14 || choix > 18) {
                    damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE; 
                }
            }
        }
    } else if((damier->plateau[ligne][colonne] == PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des pions Rouges
        if(verifierCaseValide(ligne - 1, colonne + 1)) { // Deplacement a droite possible
            if(damier->plateau[ligne - 1][colonne + 1] == CASE_VIDE) { 
                pionDeplacementD = insererRafle(pionDeplacementD, creerRafle(ligne, colonne));
                deplacementD = insererRafle(deplacementD, creerRafle(ligne - 1, colonne + 1));

                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne + 1));
            } else if((damier->plateau[ligne - 1][colonne + 1] == PION_VERT || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions verts a droite
                damier->plateau[ligne - 2][colonne + 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 4);

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE;
                }

                pionRafleD = insererRafle(pionRafleD, creerRafle(ligne, colonne));
                rafleD = insererRafle(rafleD, creerRafle(ligne - 1, colonne + 1));
                deplacementRafleD = insererRafle(deplacementRafleD, creerRafle(ligne - 2, colonne + 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafleD = insererRafle(pionRafleD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 14));
                    rafleD = insererRafle(rafleD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 4));
                    deplacementRafleD = insererRafle(deplacementRafleD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 19));

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 19));
                }

                if(choix < 14 || choix > 18) {
                    damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE;
                }
            }
        }

        if(verifierCaseValide(ligne - 1, colonne - 1)) { // Deplacement a gauche possible
            if(damier->plateau[ligne - 1][colonne - 1] == CASE_VIDE) { 
                pionDeplacementG = insererRafle(pionDeplacementG, creerRafle(ligne, colonne));
                deplacementG = insererRafle(deplacementG, creerRafle(ligne - 1, colonne - 1));
                
                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne - 1));
            } else if((damier->plateau[ligne - 1][colonne - 1] == PION_VERT || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions verts a gauche
                damier->plateau[ligne - 2][colonne - 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 4);

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE;
                }

                pionRafleG = insererRafle(pionRafleG, creerRafle(ligne, colonne));
                rafleG = insererRafle(rafleG, creerRafle(ligne - 1, colonne - 1));
                deplacementRafleG = insererRafle(deplacementRafleG, creerRafle(ligne - 2, colonne - 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne - 2));

                if(recursif != NULL) {
                    pionRafleG = insererRafle(pionRafleG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 14));
                    rafleG = insererRafle(rafleG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 4));
                    deplacementRafleG = insererRafle(deplacementRafleG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 19));

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 19));
                }

                if(choix < 14 || choix > 18) {
                    damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE;
                }
            }
        }


        if(verifierCaseValide(ligne + 1, colonne - 1)) { // Rafle arriere a gauche possible
            if((damier->plateau[ligne + 1][colonne - 1] == PION_VERT || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
                damier->plateau[ligne + 2][colonne - 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 4);

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE;
                }

                pionRafleAG = insererRafle(pionRafleAG, creerRafle(ligne, colonne));
                rafleAG = insererRafle(rafleAG, creerRafle(ligne + 1, colonne - 1));
                deplacementRafleAG = insererRafle(deplacementRafleAG, creerRafle(ligne + 2, colonne - 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne - 2));

                if(recursif != NULL) {
                    pionRafleAG = insererRafle(pionRafleAG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 14));
                    rafleAG = insererRafle(rafleAG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 4));
                    deplacementRafleAG = insererRafle(deplacementRafleAG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 19));

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 19));
                }

                if(choix < 14 || choix > 18) {
                    damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE;
                }
            }
        }

        if(verifierCaseValide(ligne + 1, colonne + 1)) { // Rafle arriere a droite possible
            if((damier->plateau[ligne + 1][colonne + 1] == PION_VERT || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
                damier->plateau[ligne + 2][colonne + 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 4);

                if(choix >= 14 && choix <= 18) {
                    damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE;
                }

                pionRafleAD = insererRafle(pionRafleAD, creerRafle(ligne, colonne));
                rafleAD = insererRafle(rafleAD, creerRafle(ligne + 1, colonne + 1));
                deplacementRafleAD = insererRafle(deplacementRafleAD, creerRafle(ligne + 2, colonne + 2));

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafleAD = insererRafle(pionRafleAD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 14));
                    rafleAD = insererRafle(rafleAD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 4));
                    deplacementRafleAD = insererRafle(deplacementRafleAD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 19));

                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 19));
                }

                if(choix < 14 || choix > 18) {
                    damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE;
                }
            }
        }
    }

    switch (choix) {
        case 1: // Deplacement possible
            return deplacement;
        break;
        case 2: // Deplacement a gauche
            return deplacementG;
        break;
        case 3: // Deplacement a droite
            return deplacementD;
        break;
        case 4: // Rafle possible
            return rafle;
        break;
        case 5: // Rafle a gauche
            return rafleG;
        break;
        case 6: // Rafle arriere a gauche
            return rafleAG;
        break;
        case 7: // Rafle a droite
            return rafleD;
        break;
        case 8: // Rafle arriere a droite
            return rafleAD;
        break;
        case 9: // Pions deplacables possible
            return pionDeplacement;
        break;
        case 10: // Pions deplacables a gauche
            return pionDeplacementG;
        break;
        case 11: // Pions deplacables arriere a gauche
            return pionDeplacementAG;
        break;
        case 12: // Pions deplacables a droite
            return pionDeplacementD;
        break;
        case 13: // Pions deplacables arriere a droite
            return pionDeplacementAD;
        break;
        case 14: // Pion pouvant rafler possible
            return pionRafle;
        break;
        case 15: // Pion pouvant rafler a gauche
            return pionRafleG;
        break;
        case 16: // Pion pouvant rafler arriere a gauche
            return pionRafleAG;
        break;
        case 17: // Pion pouvant rafler a droite
            return pionRafleD;
        break;
        case 18: // Pion pouvant rafler arriere a droite
            return pionRafleAD;
        break;
        case 19: // Deplacement possible des pions pouvant rafler
            return deplacementRafle;
        break;
        case 20: // Deplacement possible des pions pouvant rafler a gauche
            return deplacementRafleG;
        break;
        case 21: // Deplacement possible des pions pouvant rafler arriere a gauche
            return deplacementRafleAG;
        break;
        case 22: // Deplacement possible des pions pouvant rafler a droite
            return deplacementRafleD;
        break;
        case 23: // Deplacement possible des pions pouvant rafler arriere a droite
            return deplacementRafleAD;
        break;
        default:
            return NULL;
        break;
    }
}

Rafle * trouverPionRafleDeplacementMaximale(Damier *damier, Rafle *pionRafle, int couleurPion, int choix) {
    Rafle *p = pionRafle, *pion = NULL, *rafleMaximale = NULL, *deplacementMaximale = NULL; 
    int longueurMaximale = 0; 

    while (p != NULL) {
        int longueurGauche = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 5));
        int longueurArriereGauche = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 6));
        int longueurDroite = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 7));
        int longueurArriereDroite = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 8));

        if (longueurGauche > longueurMaximale) { // Comparaison des longueurs, mise à jour de la rafle maximale et du pion
            longueurMaximale = longueurGauche;
            pion = p;
            rafleMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 5);
            deplacementMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 20);
        } else if (longueurArriereGauche > longueurMaximale) {
            longueurMaximale = longueurArriereGauche;
            pion = p;
            rafleMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 6);
            deplacementMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 21);
        } else if (longueurDroite > longueurMaximale) {
            longueurMaximale = longueurDroite;
            pion = p;
            rafleMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 7);
            deplacementMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 22);
        } else if (longueurArriereDroite > longueurMaximale) {
            longueurMaximale = longueurArriereDroite;
            pion = p;
            rafleMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 8);
            deplacementMaximale = deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 23);
        }

        p = p->suivante;
    }

    switch (choix) {
        case 1: // Pion pouvant rafler au maximum
            return pion;
        break;
        case 2: // Rafle maximum
            return rafleMaximale;
        break;
        case 3: // Deplacement maximum
            return deplacementMaximale;
        break;
        default:
            return NULL;
        break;
    }
}

Rafle * trouverDernierElement(Rafle *rafle) {
    Rafle *p = rafle;

    while(p->suivante != NULL) {
        p = p->suivante;
    }

    return p;
}

Rafle * trouverDeplacementsEtRaflesPossiblesDames(Damier *damier, int couleurPion, int choix) {
    Rafle *deplacements = NULL, *rafles = NULL, *dameDeplacements = NULL, *dameRafles = NULL, *deplacementRafles = NULL;


    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if((i + j) % 2 == 0) { // Selection des cases blanches
                deplacements = insererRafle(deplacements, deplacementEtRaflePossiblesDame(damier, i, j, couleurPion, 1));
                rafles = insererRafle(rafles, deplacementEtRaflePossiblesDame(damier, i, j, couleurPion, 6));
                dameDeplacements = insererRafle(dameDeplacements, deplacementEtRaflePossiblesDame(damier, i, j, couleurPion, 11));
                dameRafles = insererRafle(dameRafles, deplacementEtRaflePossiblesDame(damier, i, j, couleurPion, 16));
                deplacementRafles = insererRafle(deplacementRafles, deplacementEtRaflePossiblesDame(damier, i, j, couleurPion, 21));
            }
        }
    }

    switch (choix) {
        case 1: // Deplacement possible
            return deplacements;
        break;
        case 2: // Rafle possible
            return rafles;
        break;
        case 3: // Dames deplacables
            return dameDeplacements;
        break;
        case 4: // Dames pouvant rafler
            return dameRafles;
        break;
        case 5: // Deplacement possible des dames pouvant rafler
            return deplacementRafles;
        break;
        default:
            return NULL;
        break;
    }    
}

Rafle * deplacementEtRaflePossiblesDame(Damier *damier, int ligne, int colonne, int couleurPion, int choix) {
    Rafle *deplacement = NULL, *rafle = NULL, *dameDeplacement = NULL, *dameRafle = NULL, *deplacementRafle = NULL;
    Rafle *deplacementG = NULL, *rafleG = NULL;
    Rafle *deplacementD = NULL, *rafleD = NULL;
    Rafle *deplacementAD = NULL, *rafleAD = NULL;
    Rafle *deplacementAG = NULL, *rafleAG = NULL;
    Rafle *dameDeplacementG = NULL, *dameRafleG = NULL, *deplacementRafleG = NULL;
    Rafle *dameDeplacementD = NULL, *dameRafleD = NULL, *deplacementRafleD = NULL;
    Rafle *dameDeplacementAD = NULL, *dameRafleAD = NULL, *deplacementRafleAD = NULL;
    Rafle *dameDeplacementAG = NULL, *dameRafleAG = NULL, *deplacementRafleAG = NULL;

    if(damier->plateau[ligne][colonne] == 2 * couleurPion) { // Selection des pions Verts
        for(int x = 1; x < DIMENSION_PLATEAU; x++) { // Parcours diagonale
            if(verifierCaseValide(ligne + x, colonne - x)) { // Deplacement en haut a gauche possible
                if(damier->plateau[ligne + x][colonne - x] == CASE_VIDE) {
                    dameDeplacementG = insererRafle(dameDeplacementG, creerRafle(ligne, colonne));
                    deplacementG = insererRafle(deplacementG, creerRafle(ligne + x, colonne - x));

                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne + x, colonne - x));
                } else if((damier->plateau[ligne + x][colonne - x] != couleurPion && damier->plateau[ligne + x][colonne - x] != CASE_VIDE) && verifierCaseValide(ligne + x + 1, colonne - x - 1) && damier->plateau[ligne + x + 1][colonne - x - 1] == CASE_VIDE) {
                    damier->plateau[ligne + x + 1][colonne - x - 1] = 2 * couleurPion; // On suppose que la prise est bonne, donc on avance
                
                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 6); // Verification d'une rafle disponible

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne + x + 1][colonne - x - 1] = CASE_VIDE; // Fin du supposition
                    }

                    dameRafleG = insererRafle(dameRafleG, creerRafle(ligne, colonne));
                    rafleG = insererRafle(rafleG, creerRafle(ligne + x, colonne - x));
                    deplacementRafleG = insererRafle(deplacementRafleG, creerRafle(ligne + x + 1, colonne - x - 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne + x, colonne - x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + x + 1, colonne - x - 1));

                    if(recursif != NULL) { // Recherche de toutes les rafles disponibles recursivements
                        dameRafleG = insererRafle(dameRafleG, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 16)); // On insere tous les pions rafles possible a la pionRafleG
                        rafleG = insererRafle(rafleG, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 6)); // On insere tous les rafles possible a la rafleG
                        deplacementRafleG = insererRafle(deplacementRafleG, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 21)); // On insere tous les deplacement rafles possible a la deplacementRafleG

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 16)); 
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 6)); 
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 21)); 
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne + x + 1][colonne - x - 1] = CASE_VIDE; // Fin du supposition
                    }
                } else {
                    break;
                }
            }
        }

        for(int x = 1; x < DIMENSION_PLATEAU; x++) { 
            if(verifierCaseValide(ligne + x, colonne + x)) { // Deplacement en haut a droite possible
                if(damier->plateau[ligne + x][colonne + x] == CASE_VIDE) {
                    dameDeplacementD = insererRafle(dameDeplacementD, creerRafle(ligne, colonne));
                    deplacementD = insererRafle(deplacementD, creerRafle(ligne + x, colonne + x));

                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne + x, colonne + x));
                } else if((damier->plateau[ligne + x][colonne + x] != couleurPion && damier->plateau[ligne + x][colonne + x] != CASE_VIDE) && verifierCaseValide(ligne + x + 1, colonne + x + 1) && damier->plateau[ligne + x + 1][colonne + x + 1] == CASE_VIDE) {
                    damier->plateau[ligne + x + 1][colonne + x + 1] = 2 * couleurPion;

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne + x + 1][colonne + x + 1] = CASE_VIDE; 
                    }

                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 6);

                    dameRafleD = insererRafle(dameRafleD, creerRafle(ligne, colonne));
                    rafleD = insererRafle(rafleD, creerRafle(ligne + x, colonne + x));
                    deplacementRafleD = insererRafle(deplacementRafleD, creerRafle(ligne + x + 1, colonne + x + 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne + x, colonne + x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + x + 1, colonne + x + 1));

                    if(recursif != NULL) {
                        dameRafleD = insererRafle(dameRafleD, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 16));
                        rafleD = insererRafle(rafleD, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafleD = insererRafle(deplacementRafleD, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 21));

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 16));
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 21));
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne + x + 1][colonne + x + 1] = CASE_VIDE; 
                    }
                } else {
                    break;
                }
            }
        }

        
        for(int x = 1; x < DIMENSION_PLATEAU; x++) {
            if(verifierCaseValide(ligne - x, colonne + x)) { // Deplacement en bas a droite possible
                if(damier->plateau[ligne - x][colonne + x] == CASE_VIDE) {
                    dameDeplacementAD = insererRafle(dameDeplacementAD, creerRafle(ligne, colonne));
                    deplacementAD = insererRafle(deplacementAD, creerRafle(ligne - x, colonne + x));

                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne - x, colonne + x));
                } else if((damier->plateau[ligne - x][colonne + x] != couleurPion && damier->plateau[ligne - x][colonne + x] != CASE_VIDE) && verifierCaseValide(ligne - x - 1, colonne + x + 1) && damier->plateau[ligne - x - 1][colonne + x + 1] == CASE_VIDE) {
                    damier->plateau[ligne - x - 1][colonne + x + 1] = 2 * couleurPion;
                
                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 6);

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne - x - 1][colonne + x + 1] = CASE_VIDE; 
                    }

                    dameRafleAD = insererRafle(dameRafleAD, creerRafle(ligne, colonne));
                    rafleAD = insererRafle(rafleAD, creerRafle(ligne - x, colonne + x));
                    deplacementRafleAD = insererRafle(deplacementRafleAD, creerRafle(ligne - x - 1, colonne + x + 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne - x, colonne + x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - x - 1, colonne + x + 1));

                    if(recursif != NULL) {
                        dameRafleAD = insererRafle(dameRafleAD, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 16));
                        rafleAD = insererRafle(rafleAD, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafleAD = insererRafle(deplacementRafleAD, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 21));

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 16));
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 21));
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne - x - 1][colonne + x + 1] = CASE_VIDE; 
                    }
                } else {
                    break;
                } 
            }
        }

        for(int x = 1; x < DIMENSION_PLATEAU; x++) {
            if(verifierCaseValide(ligne - x, colonne - x)) { // Deplacement en bas a gauche possible
                if(damier->plateau[ligne - x][colonne - x] == CASE_VIDE) {
                    dameDeplacementAG = insererRafle(dameDeplacementAG, creerRafle(ligne, colonne));
                    deplacementAG = insererRafle(deplacementAG, creerRafle(ligne - x, colonne - x));

                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne - x, colonne - x));
                } else if((damier->plateau[ligne - x][colonne - x] != couleurPion && damier->plateau[ligne - x][colonne - x] != CASE_VIDE) && verifierCaseValide(ligne - x - 1, colonne - x - 1) && damier->plateau[ligne - x - 1][colonne - x - 1] == CASE_VIDE) {
                    damier->plateau[ligne - x - 1][colonne - x - 1] = 2 * couleurPion;
                
                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 6);

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne - x - 1][colonne - x - 1] = CASE_VIDE; 
                    }

                    dameRafleAG = insererRafle(dameRafleAG, creerRafle(ligne, colonne));
                    rafleAG = insererRafle(rafleAG, creerRafle(ligne - x, colonne - x));
                    deplacementRafleAG = insererRafle(deplacementRafleAG, creerRafle(ligne - x - 1, colonne - x - 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne - x, colonne - x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - x - 1, colonne - x - 1));

                    if(recursif != NULL) {
                        dameRafleAG = insererRafle(dameRafleAG, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 16));
                        rafleAG = insererRafle(rafleAG, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 6));
                        deplacementRafleAG = insererRafle(deplacementRafleAG, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 21));

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 16));
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 6));
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 21));
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne - x - 1][colonne - x - 1] = CASE_VIDE; 
                    }
                } else {
                    break;
                }
            }
        }

    }

    switch (choix) {
        case 1: // Deplacement possible
            return deplacement;
        break;
        case 2: // Deplacement a gauche
            return deplacementG;
        break;
        case 3: // Deplacement arriere a gauche
            return deplacementAG;
        break;
        case 4: // Deplacement a droite
            return deplacementD;
        break;
        case 5: // Deplacement arriere a droite
            return deplacementAD;
        break;
        case 6: // Rafle possible
            return rafle;
        break;
        case 7: // Rafle a gauche
            return rafleG;
        break;
        case 8: // Rafle arriere a gauche
            return rafleAG;
        break;
        case 9: // Rafle a droite
            return rafleD;
        break;
        case 10: // Rafle arriere a droite
            return rafleAD;
        break;
        case 11: // Pions deplacables possible
            return dameDeplacement;
        break;
        case 12: // Pions deplacables a gauche
            return dameDeplacementG;
        break;
        case 13: // Pions deplacables arriere a gauche
            return dameDeplacementAG;
        break;
        case 14: // Pions deplacables a droite
            return dameDeplacementD;
        break;
        case 15: // Pions deplacables arriere a droite
            return dameDeplacementAD;
        break;
        case 16: // Pion pouvant rafler possible
            return dameRafle;
        break;
        case 17: // Pion pouvant rafler a gauche
            return dameRafleG;
        break;
        case 18: // Pion pouvant rafler arriere a gauche
            return dameRafleAG;
        break;
        case 19: // Pion pouvant rafler a droite
            return dameRafleD;
        break;
        case 20: // Pion pouvant rafler arriere a droite
            return dameRafleAD;
        break;
        case 21: // Deplacement possible des pions pouvant rafler
            return deplacementRafle;
        break;
        case 22: // Deplacement possible des pions pouvant rafler a gauche
            return deplacementRafleG;
        break;
        case 23: // Deplacement possible des pions pouvant rafler arriere a gauche
            return deplacementRafleAG;
        break;
        case 24: // Deplacement possible des pions pouvant rafler a droite
            return deplacementRafleD;
        break;
        case 25: // Deplacement possible des pions pouvant rafler arriere a droite
            return deplacementRafleAD;
        break;
        default:
            return NULL;
        break;
    }
}

int verifierFinPartie(Damier *damier, Joueur joueur, int quitter) {
    if(quitter == 0) {
        return 0;
    } else if(joueur.couleur == PION_VERT) {
        if(damier->nombrePionVert == 0) {
            return 0;
        } else if(!verifierDeplacementJoueur(damier, joueur)) {
            return 0;
        }
    } else if(joueur.couleur == PION_ROUGE) {
        if(damier->nombrePionRouge == 0) {
            return 0;
        } else if(!verifierDeplacementJoueur(damier, joueur)) {
            return 0;
        }
    }

    return 1;
}

int verifierGagnant(Damier *damier, Joueur joueur1, Joueur joueur2, int quitter) {
    if(quitter == 0) {
        if(damier->nombrePionVert > damier->nombrePionRouge) {
            return PION_VERT;
        } else {
            return PION_ROUGE;
        }
    } else if(damier->nombrePionVert == 0 && damier->nombrePionRouge != 0) {
        return PION_ROUGE;
    } else if(damier->nombrePionVert != 0 && damier->nombrePionRouge == 0) {
        return PION_VERT;
    } else if(verifierDeplacementJoueur(damier, joueur1) && !verifierDeplacementJoueur(damier, joueur2)) {
        return joueur1.couleur;
    } else if(!verifierDeplacementJoueur(damier, joueur1) && verifierDeplacementJoueur(damier, joueur2)) {
        return joueur2.couleur;
    } else {
        return 0;
    }
}
