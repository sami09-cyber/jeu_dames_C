#ifndef STRUCTURE_H   // Si STRUCTURE_H n'est pas déjà défini
    #define STRUCTURE_H   // On definit STRUCTURE_H pour éviter les inclusions multiples

    #include "structure.h"  // Contenu du fichier d'en-tete

#endif  // Fin du garde d'inclusion

/* Deplacement d'un pion */
void deplacerPion(Damier *damier, Deplacement deplacement, Rafle *rafle, int couleurPion);

int verifierCaseValide(int ligne, int colonne);

int verifierCaseVide(Damier *damier, int ligne, int colonne);

/* Promouvoie un pion en dame */ 
void promouvoirPion(Damier *damier, Case cases, int couleurPion);

int verifierPromotionsPions(Damier *damier, int couleurPion);

int verifierPromotionPion(Damier *damier, int ligne, int colonne, int couleurPion);

/* Deplacement d'un dame */ 
void deplacerDame(Damier *damier, Deplacement deplacement, Rafle *rafle, int couleurPion);

int verifierDeplacementDame(Damier *damier, Deplacement deplacement, int couleurDame);

Rafle * trouverDeplacementsEtRaflesPossiblesPions(Damier *damier, int couleurPion, int choix);

Rafle * deplacementEtRaflePossiblesPion(Damier *damier, int ligne, int colonne, int couleurPion, int choix);

Rafle * trouverPionRafleDeplacementMaximale(Damier *damier, Rafle *pionRafle, int couleurPion, int choix);

Rafle * trouverDernierElement(Rafle *rafle);

Rafle * trouverDeplacementsEtRaflesPossiblesDames(Damier *damier, int couleurPion, int choix);

Rafle * deplacementEtRaflePossiblesDame(Damier *damier, int ligne, int colonne, int couleurPion, int choix);

int verifierFinPartie(Damier *damier, Joueur joueur, int quitter);

int verifierDeplacementJoueur(Damier *damier, Joueur joueur);

int verifierGagnant(Damier *damier, Joueur joueur1, Joueur joueur2, int quitter);