#ifndef STRUCTURE_H   // Si STRUCTURE_H n'est pas déjà défini
    #define STRUCTURE_H   // On definit STRUCTURE_H pour éviter les inclusions multiples

    #include "structure.h"  // Contenu du fichier d'en-tete
    #include "deplacement.h"

#endif  // Fin du garde d'inclusion


void afficherMenu();

void afficherOptions();

void afficherAide();

void afficherTypeJoeur();

void enregistrerJoeur(int typeJoeur, Joueur *joueur1, Joueur *joueur2);

int genererNombre(int minimum, int maximum);

int lire(char *chaine, int longueur);

void viderBuffer();

void tabuler(int nombre);

void initialiserDamier(Damier *damier);

void afficherDamier(Damier *damier, Rafle *rafle);

void nouvellePartie(Damier *damier, int option);

void choisirOptions(int *option);

Deplacement afficherTourJoueur(Damier *damier, Joueur joueur, Rafle *pions, Rafle *rafle);

void jouerPartie(Damier *damier, Joueur joueur1, Joueur joueur2, int quitter);
// afficherCoup
// chargerPartie
// quitterJeu
// afficherRafle
// sauvegarderPartie