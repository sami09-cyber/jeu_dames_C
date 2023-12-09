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


int verifierDeplacementJoueur(Damier *damier, Joueur joueur) {
    Rafle *deplacementPion = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur.couleur, 1);
    Rafle *raflePion = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur.couleur, 2);
    Rafle *deplacementDame = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur.couleur, 1);
    Rafle *rafleDame= trouverDeplacementsEtRaflesPossiblesDames(damier, joueur.couleur, 2);

    if(deplacementPion == NULL && raflePion == NULL && deplacementDame == NULL && rafleDame == NULL) {
        return 0;
    }

    return 1;
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
    damier->plateau[cases.ligne][cases.colonne] = 2*couleurPion;
}

int verifierPromotionPion(Damier *damier, Case cases, int couleurPion) {
    if(couleurPion == PION_VERT) {
        for(int j = 0; j < DIMENSION_PLATEAU; j++) {
            if((9 + j) % 2 == 0) { // Selection des cases blanches
                if(damier->plateau[9][j] == couleurPion) {
                    return 1;
                }
            }
        }

        return 0;
    } else { // Pion Rouge
        for(int j = 0; j < DIMENSION_PLATEAU; j++) {
            if((0 + j) % 2 == 0) { // Selection des cases blanches
                if(damier->plateau[0][j] == couleurPion) {
                    return 1;
                }
            }
        }

        return 0;
    }
}

void deplacerDame(Damier *damier, Deplacement deplacement, int couleurDame) {
    damier->plateau[deplacement.caseInitiale.ligne][deplacement.caseInitiale.colonne] = CASE_VIDE;
    damier->plateau[deplacement.caseFinale.ligne][deplacement.caseFinale.colonne] = couleurDame;
}

/*
    -1 : On ne pas enjambe son propre pion
*/ 
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

/* 
    1: choix de deplacements
    2: choix de rafles
*/ 
Rafle * trouverDeplacementsEtRaflesPossiblesPions(Damier *damier, int couleurPion, int choix) {
    Rafle *deplacement = NULL;
    Rafle *rafle = NULL;

    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if((i + j) % 2 == 0) { // Selection des cases blanches
                if((damier->plateau[i][j] == PION_VERT) && (couleurPion == PION_VERT)) { // Selection des pions Verts
                    if(verifierCaseValide(i + 1, j - 1)) { // Deplacement a gauche possible
                        if(damier->plateau[i + 1][j - 1] == CASE_VIDE) {
                            deplacement = insererRafle(deplacement, creerRafle(i + 1, j - 1));
                        } else if((damier->plateau[i + 1][j - 1] == PION_ROUGE) && verifierCaseValide(i + 2, j - 2) && damier->plateau[i + 2][j - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
                            rafle = insererRafle(rafle, creerRafle(i + 1, j - 1));
                        }
                    } else if(verifierCaseValide(i + 1, j + 1)) { // Deplacement a droite possible
                        if(damier->plateau[i + 1][j + 1] == CASE_VIDE) {
                            deplacement = insererRafle(deplacement, creerRafle(i + 1, j + 1));
                        } else if((damier->plateau[i + 1][j + 1] == PION_ROUGE) && verifierCaseValide(i + 2, j + 2) && damier->plateau[i + 2][j + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
                            rafle = insererRafle(rafle, creerRafle(i + 1, j + 1));
                        }
                    }
                } else if((damier->plateau[i][j] == PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des pions Rouges
                    if(verifierCaseValide(i - 1, j + 1)) { // Deplacement a droite possible
                        if(damier->plateau[i - 1][j + 1] == CASE_VIDE) {
                            deplacement = insererRafle(deplacement, creerRafle(i - 1, j + 1));
                        } else if((damier->plateau[i - 1][j + 1] == PION_VERT) && verifierCaseValide(i - 2, j + 2) && damier->plateau[i - 2][j + 2] == CASE_VIDE) { // Selection des rafles des Pions verts a droite
                            rafle = insererRafle(rafle, creerRafle(i - 1, j + 1));
                        }
                    } else if(verifierCaseValide(i - 1, j - 1)) { // Deplacement a gauche possible
                        if(damier->plateau[i - 1][j - 1] == CASE_VIDE) {
                            deplacement = insererRafle(deplacement, creerRafle(i - 1, j - 1));
                        } else if((damier->plateau[i - 1][j - 1] == PION_VERT) && verifierCaseValide(i - 2, j - 2) && damier->plateau[i - 2][j - 2] == CASE_VIDE) { // Selection des rafles des Pions verts a gauche
                            rafle = insererRafle(rafle, creerRafle(i - 1, j - 1));
                        }
                    }
                }
            }
        }
    }

    return choix == 1 ? deplacement : rafle;
}


Rafle * trouverDeplacementsEtRaflesPossiblesDames(Damier *damier, int couleurPion, int choix) {
    Rafle *deplacement = NULL;
    Rafle *rafle = NULL;

    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if((i + j) % 2 == 0) { // Selection des cases blanches
                if((damier->plateau[i][j] == 2 * PION_VERT) && (couleurPion == PION_VERT)) { // Selection des dames Verts
                    for(int x = 1; x < DIMENSION_PLATEAU - 1; x++) { // Parcours diagonale
                        if(verifierCaseValide(i + x, j - x)) { // Deplacement en haut a gauche possible
                            if(damier->plateau[i + x][j - x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i + x, j - x));
                            } else if(damier->plateau[i + x][j - x] == PION_ROUGE || damier->plateau[i + x][j - x] == 2 * PION_ROUGE) {
                                rafle = insererRafle(rafle, creerRafle(i + x, j - x));
                            } else {
                                break;
                            }
                        } else if(verifierCaseValide(i + x, j + x)) { // Deplacement en haut a droite possible
                            if(damier->plateau[i + x][j + x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i + x, j + x));
                            } else if(damier->plateau[i + x][j + x] == PION_ROUGE || damier->plateau[i + x][j + x] == 2 * PION_ROUGE) {
                                rafle = insererRafle(rafle, creerRafle(i + x, j + x));
                            } else {
                                break;
                            }
                        } else if(verifierCaseValide(i - x, j + x)) { // Deplacement en bas a droite possible
                            if(damier->plateau[i - x][j + x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i - x, j + x));
                            } else if(damier->plateau[i - x][j + x] == PION_VERT || damier->plateau[i - x][j + x] == 2 * PION_VERT) {
                                rafle = insererRafle(rafle, creerRafle(i - x, j + x));
                            } else {
                                break;
                            }
                        } else if(verifierCaseValide(i - x, j - x)) { // Deplacement en bas a gauche possible
                            if(damier->plateau[i - x][j - x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i - x, j - x));
                            } else if(damier->plateau[i - x][j - x] == PION_ROUGE || damier->plateau[i - x][j - x] == 2 * PION_ROUGE) {
                                rafle = insererRafle(rafle, creerRafle(i - x, j - x));
                            } else {
                                break;
                            }
                        }
                    }
                } else if((damier->plateau[i][j] == 2 * PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des dames Rouges
                    for(int x = 1; x < DIMENSION_PLATEAU - 1; x++) { // Parcours diagonale
                        if(verifierCaseValide(i - x, j + x)) { // Deplacement en haut a droite possible
                            if(damier->plateau[i - x][j + x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i - x, j + x));
                            } else if(damier->plateau[i - x][j + x] == PION_VERT || damier->plateau[i - x][j + x] == 2 * PION_VERT) {
                                rafle = insererRafle(rafle, creerRafle(i - x, j + x));
                            } else {
                                break;
                            }
                        } else if(verifierCaseValide(i - x, j - x)) { // Deplacement en haut a gauche possible
                            if(damier->plateau[i - x][j - x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i - x, j - x));
                            } else if(damier->plateau[i - x][j - x] == PION_ROUGE || damier->plateau[i - x][j - x] == 2 * PION_ROUGE) {
                                rafle = insererRafle(rafle, creerRafle(i - x, j - x));
                            } else {
                                break;
                            }
                        } else if(verifierCaseValide(i + x, j - x)) { // Deplacement en bas a gauche possible
                            if(damier->plateau[i + x][j - x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i + x, j - x));
                            } else if(damier->plateau[i + x][j - x] == PION_ROUGE || damier->plateau[i + x][j - x] == 2 * PION_ROUGE) {
                                rafle = insererRafle(rafle, creerRafle(i + x, j - x));
                            } else {
                                break;
                            }
                        } else if(verifierCaseValide(i + x, j + x)) { // Deplacement en bas a droite possible
                            if(damier->plateau[i + x][j + x] == CASE_VIDE) {
                                deplacement = insererRafle(deplacement, creerRafle(i + x, j + x));
                            } else if(damier->plateau[i + x][j + x] == PION_ROUGE || damier->plateau[i + x][j + x] == 2 * PION_ROUGE) {
                                rafle = insererRafle(rafle, creerRafle(i + x, j + x));
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return choix == 1 ? deplacement : rafle;
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