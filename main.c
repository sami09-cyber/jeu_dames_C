#include "affichage.h"
#include "deplacement.h"


int main(int argc, char* argv[]) {
    int choix, option;

    Damier *damier = NULL;
    

    damier = creerDamier();     


    do {
        afficherMenu();
        printf("Entrez votre choix (1-5): ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: // Nouvelle partie
                nouvellePartie(damier, option, &choix);
            break;
            case 2: // Partie existante
                partieExistante(damier, &choix);
            break;
            case 3: // Revisualiser partie
                revisualiserPartie(damier, &choix);
            break;
            case 4: // Les options
                choisirOptions(&option);
            break;
            case 5: // L'aide
                afficherAide();
            break;
            case 0: // Arreter le jeu
                system("clear");
                quitterJeu(damier);
            break;
            default:
                printf("\nChoix invalide. Veuillez entrer un nombre entre 1 et 5.\n");
            break;
        }

    } while (choix != 0);

    return 0;
}
