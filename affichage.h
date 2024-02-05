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

void cadre(char *nom1, char *nom2, int temps1, int temps2);

void initialiserDamier(Damier *damier);

void afficherDamier(Damier *damier, Rafle *rafle, char *nom1, char *nom2, int temps1, int temps2);

void nouvellePartie(Damier *damier, int option, int *quitter);

void partieExistante(Damier *damier, int *quitter);

void revisualiserPartie(Damier *damier, int *quitter);

void choisirOptions(int *option);

Deplacement afficherTourJoueur(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *raflePossible, Rafle *pionDeplacement, Rafle *pionRafle, Rafle *deplacementRafle, int option, int *quitter);

Deplacement afficherTourJoueurDame(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *raflePossible, Rafle *dameDeplacement, Rafle *dameRafle, Rafle *deplacementRafle, int option, int *quitter);

Deplacement jouerCPU(Damier *damier, Joueur *joueur, Rafle *pionDeplacement, Rafle *raflePossible, Rafle *pionRafle, Rafle *deplacementRafle, int option);

Deplacement jouerCPUDame(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *raflePossible, Rafle *dameDeplacement, Rafle *deplacementRafle, int option);

Deplacement jouerHumain(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *pionDeplacement, Rafle *raflePossible, Rafle *pionRafle, Rafle *deplacementRafle, int *quitter);

Deplacement jouerHumainDame(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *dameDeplacement, Rafle *raflePossible, Rafle *dameRafle, Rafle *deplacementRafle, int *quitter);

void jouerPartie(Damier *damier, Joueur joueur1, Joueur joueur2,  int option, int initialiser, int *quitter);

void revisualiserPartie(Damier *damier, int *quitter);

void sauvegarderPartie(Damier *damier, Joueur joueur1, Joueur joueur2, int option);

void sauvegarderRevisualisation(Damier *damier, Joueur joueur1, Joueur joueur2, int option);

int chargerPartie(Damier *damier, Joueur *joueur1, Joueur *joueur2, int *option, char *nomFichier);

int chargerRevisualisation(Damier *damier, Joueur *joueur1, Joueur *joueur2, int *option, char *nomFichier, long *positionCourante);

int VerifierRepertoire(char *chemin);

char * verifierFichier(char *nomFichier);

void confirmerFichier();

void afficherRevisualisation(Damier *damier, Joueur joueur1, Joueur joueur2, int option, int *quitter);

void afficherGagnant(Joueur joueur1, Joueur joueur2, int couleurPion);

void quitterJeu(Damier *damier);
