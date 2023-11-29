#ifndef STRUCTURE_H   // Si STRUCTURE_H n'est pas déjà défini
    #define STRUCTURE_H   // On definit STRUCTURE_H pour éviter les inclusions multiples

    #include "structure.h"  // Contenu du fichier d'en-tete

#endif  // Fin du garde d'inclusion

/* Deplacement d'un pion */
int deplacerPion(Damier *damier, Deplacement deplacement, Rafle *rafle, int couleurPion);

int verifierPrise(Case caseInitiale, Case casePrise);

/* Promouvoie un pion en dame */ 
void promouvoirPion(Damier *damier, int couleur);

/* Deplacement d'un dame */ 
void deplacerDame(Damier *damier, Deplacement deplacement, Case prise, int couleur, int pion);
