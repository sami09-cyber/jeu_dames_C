#include "affichage.h"
#include "deplacement.h"


int main(int argc, char* argv[]) {
    int choix, option;

    Damier *damier = NULL;
    // Rafle *rafle = NULL;

    damier = creerDamier();

    // rafle = insererRafle(rafle, creerRafle(3, 1));
    // rafle = insererRafle(rafle, creerRafle(2, 2));
    // rafle = insererRafle(rafle, creerRafle(1, 3));
    // rafle = insererRafle(rafle, creerRafle(2, 4));
    // rafle = insererRafle(rafle, creerRafle(7, 1));
    // rafle = insererRafle(rafle, creerRafle(6, 0));
    // rafle = insererRafle(rafle, creerRafle(6, 2));
    // rafle = insererRafle(rafle, creerRafle(5, 1));
    // rafle = insererRafle(rafle, creerRafle(5, 3));

    // initialiserDamier(damier);
    // rafle = trouverDeplacementsEtRaflesPossiblesPions(damier, PION_VERT, 1);
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
                nouvellePartie(damier);
            break;
            case 2: // Partie existante
                system("clear");
                printf("\nCharger une partie existante...\n");
                // Appel à la fonction pour charger une partie
            break;
            case 3: // Les options
                system("clear");
                choisirOptions(&option);
            break;
            case 4: // L'aide
                system("clear");
                afficherAide();
            break;
            case 0: // Arreter le jeu
                system("cls");
                printf("\nQuitter le jeu de dames. Au revoir!\n");
            break;
            default:
                printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
            break;
        }

    } while (choix != 0);

    return 0;
}