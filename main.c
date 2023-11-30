#include "affichage.h"
#include "deplacement.h"


int main(int argc, char* argv[]) {
    // int choix, option, typeJoeur;

    Damier *damier = NULL;
    Rafle *rafle = NULL;

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

    initialiserDamier(damier);
    rafle = trouverDeplacementPionPossible(damier, PION_ROUGE);
    afficherDamier(damier, rafle);

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

    // do {
    //     afficherMenu();
    //     printf("Entrez votre choix (1-4): \t");
    //     scanf("%d", &choix);

    //     switch (choix) {
    //         case 1: // Nouvelle partie
    //             printf("\nLancer une nouvelle partie...\n");

    //             do {
    //                 afficherTypeJoeur();
    //                 printf("Entrez le numéro du type de joueur : ");
    //                 scanf("%d", &typeJoeur);

    //                 switch (typeJoeur) {
    //                     case 1: // Humain VS Machine
    //                         Joueur humain, machine;
    //                         enregistrerJoeur(1, humain, machine);
    //                         initialiserDamier(damier);
    //                         afficherDamier(damier);
    //                     break;
    //                     case 2: // Humain VS Humain
    //                         Joueur humain1, humain2;
    //                         enregistrerJoeur(1, humain1, humain2);
    //                         initialiserDamier(damier);
    //                         afficherDamier(damier);
    //                     break;
    //                     case 3:
    //                         printf("Retour au menu principal!\n");
    //                     break;
    //                     case 0:
    //                         choix = 0;
    //                         printf("Quitter le jeu de dames. Au revoir!\n");
    //                     break;
    //                     default:
    //                         printf("Choix invalide. Veuillez entrer un nombre entre 1 et 2.\n");
    //                     break;
    //                 }

    //             } while(typeJoeur != 3 && typeJoeur != 0);
    //         break;
    //         case 2: // Partie existante
    //             printf("\nCharger une partie existante...\n");
    //             // Appel à la fonction pour charger une partie
    //         break;
    //         case 3: // Les options
    //             do {
    //                 afficherOptions();
    //                 printf("Entrez le numéro de l'option : \n");
    //                 scanf("%d", &option);
    //             } while(option != 1 && option != 2 && option != 3);
    //         break;
    //         case 4: // L'aide
    //             afficherAide();
    //         break;
    //         case 0: // Arreter le jeu
    //             printf("\nQuitter le jeu de dames. Au revoir!\n");
    //         break;
    //         default:
    //             printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
    //         break;
    //     }

    // } while (choix != 0);

    return 0;
}