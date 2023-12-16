#include "affichage.h"
#include "deplacement.h"


int main(int argc, char* argv[]) {
    int choix, option;

    Damier *damier = NULL;
    // Rafle *rafle = NULL, *t = NULL, *r = NULL, *deplacementsPossiblesPions = NULL, *initiale = NULL;

    damier = creerDamier();

    // t = insererRafle(t, creerRafle(2, 2));
    // t = insererRafle(t, creerRafle(3, 3));
    // t = insererRafle(t, creerRafle(2, 4));
    // t = insererRafle(t, creerRafle(7, 1));
    // r = insererRafle(r, creerRafle(6, 0));
    // r = insererRafle(r, creerRafle(6, 2));
    // r = insererRafle(r, creerRafle(5, 3));



    // initiale = rechercherRafleParIndice(t, genererNombre(1, longueurRafle(t)));
    // initiale = rechercherRafleParIndice(t, 3);
    // deplacementsPossiblesPions = deplacementEtRaflePossiblesPion(damier, initiale->cases.ligne, initiale->cases.colonne, PION_VERT, 1);
    // deplacementsPossiblesPions = deplacementEtRaflePossiblesPion(damier, 3, 3, PION_VERT, 1);
    // Rafle *finale = rechercherRafleParIndice(deplacementsPossiblesPions, genererNombre(1, longueurRafle(deplacementsPossiblesPions)));

    // rafle = initiale;
    // rafle = deplacementsPossiblesPions;
    // rafle = finale;

    // printf("\nL:%d\t", genererNombre(1, 3));

    // initialiserDamier(damier);
    // rafle = trouverDeplacementsEtRaflesPossiblesPions(damier, PION_ROUGE, 1);
    // // rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, 3, 1, PION_VERT, 1));
    // // rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, 3, 3, PION_VERT, 1));
    // // rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, 3, 5, PION_VERT, 1));
    // rafle = deplacementEtRaflePossiblesPion(damier, 3, 3, PION_VERT, 1);
    // afficherDamier(damier, rafle);

    // while(rafle != NULL) {
    //     printf("(%d, %d)\n", rafle->cases.ligne, rafle->cases.colonne);
    //     rafle = rafle->suivante;
    // }

    // for(int i = 0; i < 10; i++) {
    //     for(int j = 0; j < 10; j++) {
    //         printf("%d\t", damier->plateau[i][j]);
    //     }
    //     printf("\n");
    // }

    do {
        afficherMenu();
        printf("Entrez votre choix (1-4): \t");
        scanf("%d", &choix);

        switch (choix) {
            case 1: // Nouvelle partie
                nouvellePartie(damier, option);
            break;
            case 2: // Partie existante
                system("clear");
                printf("\nCharger une partie existante...\n");
                // Appel à la fonction pour charger une partie
            break;
            case 3: // Les options
                choisirOptions(&option);
            break;
            case 4: // L'aide
                afficherAide();
            break;
            case 0: // Arreter le jeu
                system("clear");
                printf("\nQuitter le jeu de dames. Au revoir!\n");
            break;
            default:
                printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
            break;
        }

    } while (choix != 0);

    // return 0;
}


// monther carlo tree search