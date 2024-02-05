#include "affichage.h"

void afficherMenu() {
    printf("====== Menu du Jeu de Dames ======\n");
    printf("1. Nouvelle partie\n");
    printf("2. Charger partie\n");
    printf("3. Revisualiser une partie\n");
    printf("3. Options\n");
    printf("4. Aide\n");
    printf("0. Quitter\n");
    printf("===================================\n");
}

void afficherOptions() {
    printf("\n====== Options du Jeu de Dames ======\n");
    printf("1. Niveau facile\n");
    printf("2. Niveau Moyen\n");
    printf("3. Niveau difficile\n");
}

void confirmerFichier() {
    printf("====== Chargement de la partie ======\n");
    printf("1. Confirmer\n");
    printf("2. Retour au menu principal\n");
    printf("0. Quitter\n");
}

void afficherTypeJoeur() {
    printf("====== Type de joeurs du Jeu de Dames ======\n");
    printf("1. Humain VS Machine\n");
    printf("2. Humain VS Humain\n");
    printf("3. Retour au menu principal\n");
    printf("0. Quitter\n");
}

Deplacement afficherTourJoueur(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *raflePossible, Rafle *pionDeplacement, Rafle *pionRafle, Rafle *deplacementRafle, int option, int *quitter) { 
    if(joueur->type == CPU) {
        return jouerCPU(damier, joueur, pionDeplacement, raflePossible, pionRafle, deplacementRafle, option); 
    } else {
        return jouerHumain(damier, joueur, deplacementPossible, pionDeplacement, raflePossible, pionRafle, deplacementRafle, quitter);
    }
}

Deplacement afficherTourJoueurDame(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *raflePossible, Rafle *dameDeplacement, Rafle *dameRafle, Rafle *deplacementRafle, int option, int *quitter) { 
    if(joueur->type == CPU) {
        return jouerCPUDame(damier, joueur, dameDeplacement, raflePossible, dameRafle, deplacementRafle, option); 
    } else {
        return jouerHumainDame(damier, joueur, deplacementPossible, dameDeplacement, raflePossible, dameRafle, deplacementRafle, quitter);
    }
}


Deplacement jouerCPU(Damier *damier, Joueur *joueur, Rafle *pionDeplacement, Rafle *raflePossible, Rafle *pionRafle, Rafle *deplacementRafle, int option) {
    Deplacement deplacement;
    Rafle *initiale, *finale, *deplacementPossiblePion;
    time_t start = time(NULL);

    printf("====== Tour de %s ======\n", joueur->surnom);

    if(raflePossible == NULL) {
        // On choisit une case initiale dans les pion deplacable
        initiale = rechercherRafleParIndice(pionDeplacement, genererNombre(1, longueurRafle(pionDeplacement)));

        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start); // Mise a jour du temps de jeu

        deplacementPossiblePion = deplacementEtRaflePossiblesPion(damier, initiale->cases.ligne, initiale->cases.colonne, joueur->couleur, 1);
        
        // On choisit une case finale dans les deplacements possibles de la case initiale
        finale = rechercherRafleParIndice(deplacementPossiblePion, genererNombre(1, longueurRafle(deplacementPossiblePion)));
        
        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start);
    } else {
        // On selection le pion raflant au maximum dans les pions pouvant rafler
        Rafle *pionMax = trouverPionRafleDeplacementMaximale(damier, pionRafle, joueur->couleur, 1);
        
        // On choisit une case initiale dans les pion raflant au maximum
        initiale = rechercherRafleParIndice(pionMax, genererNombre(1, longueurRafle(pionMax)));

        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start);

        // La case finale est le dernier element des deplacements possibles de la case initiale
        finale = trouverDernierElement(trouverPionRafleDeplacementMaximale(damier, pionRafle, joueur->couleur, 3));

        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start);
    }

    // Affectation des valeurs au deplacement
    
    deplacement.caseInitiale.ligne = initiale->cases.ligne;
    deplacement.caseInitiale.colonne = initiale->cases.colonne;
    deplacement.caseFinale.ligne = finale->cases.ligne;
    deplacement.caseFinale.colonne = finale->cases.colonne;


    return deplacement;
}

Deplacement jouerCPUDame(Damier *damier, Joueur *joueur, Rafle *dameDeplacement, Rafle *raflePossible, Rafle *dameRafle, Rafle *deplacementRafle, int option) {
    Deplacement deplacement;
    Rafle *initiale, *finale, *deplacementPossibleDame;
    time_t start = time(NULL);

    printf("====== Tour de %s ======\n", joueur->surnom);

    if(raflePossible == NULL) {
        // On choisit une case initiale dans les dames deplacables
        initiale = rechercherRafleParIndice(dameDeplacement, genererNombre(1, longueurRafle(dameDeplacement)));

        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start);

        deplacementPossibleDame = deplacementEtRaflePossiblesDame(damier, initiale->cases.ligne, initiale->cases.colonne, joueur->couleur, 1);

        // On choisit une case finale dans les deplacements possibles de la case initiale
        finale = rechercherRafleParIndice(deplacementPossibleDame, genererNombre(1, longueurRafle(deplacementPossibleDame)));

        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start);
    } else {
        // On selection le dame raflant au maximum dans les dames pouvant rafler
        Rafle *dameMax = trouverPionRafleDeplacementMaximale(damier, dameRafle, joueur->couleur, 1);

        initiale = rechercherRafleParIndice(dameMax, genererNombre(1, longueurRafle(dameMax)));

        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start);

        // La case finale est le dernier element des deplacements possibles de la case initiale
        finale = trouverDernierElement(trouverPionRafleDeplacementMaximale(damier, dameRafle, joueur->couleur, 3));

        usleep(1000000); // 1000000 µs = 1s
        joueur->temps += (int) (time(NULL) - start);
    }
    
    deplacement.caseInitiale.ligne = initiale->cases.ligne;
    deplacement.caseInitiale.colonne = initiale->cases.colonne;
    deplacement.caseFinale.ligne = finale->cases.ligne;
    deplacement.caseFinale.colonne = finale->cases.colonne;

    return deplacement;
}

Deplacement jouerHumain(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *pionDeplacement, Rafle *raflePossible, Rafle *pionRafle, Rafle *deplacementRafle, int *quitter) {
    int ligneInitiale, colonneInitiale;
    int ligneFinale, colonneFinale;
    Deplacement deplacement;
    time_t start = time(NULL);
    joueur->temps = 0;


    printf("====== Tour de %s ======\n", joueur->surnom);

    if(raflePossible == NULL) { // simple deplacement
        do {
            printf("Entrer la ligne initiale: ");
            scanf("%d", &ligneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne initiale: ");
            scanf("%d", &colonneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneInitiale < 0 || colonneInitiale < 0) {
                *quitter = 0;
            } else {
                if(rechercherRafle(pionDeplacement, ligneInitiale, colonneInitiale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneInitiale, colonneInitiale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } else if(verifierCaseVide(damier, ligneInitiale, colonneInitiale)) {
                        printf("La case est vide.Reessayer\n");
                    } else {
                        printf("Le pion n'est pas deplacable.Reessayer\n");
                    }
                } 
            }
        } while(rechercherRafle(pionDeplacement, ligneInitiale, colonneInitiale) == NULL && *quitter != 0);

        do {
            printf("\nEntrer la ligne finale: ");
            scanf("%d", &ligneFinale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne finale: ");
            scanf("%d", &colonneFinale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneFinale < 0 || colonneFinale < 0) {
                *quitter = 0;
            } else {
                if(rechercherRafle(deplacementPossible, ligneFinale, colonneFinale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneFinale, colonneFinale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } if(!verifierCaseVide(damier, ligneFinale, colonneFinale)) {
                        printf("La case n'est pas vide.Reessayer\n");
                    } else {
                        printf("Le pion ne peut pas se deplacer a ce point.Reessayer\n"); 
                    }
                }
            }
        } while(rechercherRafle(deplacementPossible, ligneFinale, colonneFinale) == NULL && *quitter != 0);
    } else { // Rafle disponible
        Rafle *pionMax, *deplacementMax;

        pionMax = trouverPionRafleDeplacementMaximale(damier, pionRafle, joueur->couleur, 1);
        deplacementMax = trouverPionRafleDeplacementMaximale(damier, pionRafle, joueur->couleur, 3);

        do {
            printf("Entrer la ligne initiale: ");
            scanf("%d", &ligneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne initiale: ");
            scanf("%d", &colonneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneInitiale < 0 || colonneInitiale < 0) {
                *quitter = 0;
            } else {
                if(rechercherRafle(pionRafle, ligneInitiale, colonneInitiale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneInitiale, colonneInitiale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } else if(verifierCaseVide(damier, ligneInitiale, colonneInitiale)) {
                        printf("La case est vide.Reessayer\n"); 
                    } else {
                        printf("Une rafle est disponible.Reessayer\n"); 
                    }
                }
                 
                if(rechercherRafle(pionMax, ligneInitiale, colonneInitiale) == NULL) {
                    printf("Deplacement incorrect: ");
                    printf("Une rafle Maximale est disponible.Reessayer\n"); 
                }
            }
        } while(rechercherRafle(pionMax, ligneInitiale, colonneInitiale) == NULL && *quitter != 0);

        do {
            printf("\nEntrer la ligne finale: ");
            scanf("%d", &ligneFinale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne finale: ");
            scanf("%d", &colonneFinale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneFinale < 0 || colonneFinale < 0) {
                *quitter = 0;
            } else {
                if(rechercherRafle(deplacementMax, ligneFinale, colonneFinale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneFinale, colonneFinale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } else if(!verifierCaseVide(damier, ligneFinale, colonneFinale)) {
                        printf("La case n'est pas vide.Reessayer\n"); 
                    } else {
                        printf("Le pion ne peut pas se deplacer a ce point.Reessayer\n"); 
                    }
                }
            }
        } while(rechercherRafle(deplacementMax, ligneFinale, colonneFinale) == NULL && *quitter != 0);
    }


    deplacement.caseInitiale.ligne = ligneInitiale;
    deplacement.caseInitiale.colonne = colonneInitiale;
    deplacement.caseFinale.ligne = ligneFinale;
    deplacement.caseFinale.colonne = colonneFinale;

    return deplacement;
}

Deplacement jouerHumainDame(Damier *damier, Joueur *joueur, Rafle *deplacementPossible, Rafle *dameDeplacement, Rafle *raflePossible, Rafle *dameRafle, Rafle *deplacementRafle, int *quitter) {
    int ligneInitiale, colonneInitiale;
    int ligneFinale, colonneFinale;
    Deplacement deplacement;
    time_t start = time(NULL);
    joueur->temps = 0;

    printf("====== Tour de %s ======\n", joueur->surnom);

    if(raflePossible == NULL) { // simple deplacement
        do {
            printf("Entrer la ligne initiale: ");
            scanf("%d", &ligneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne initiale: ");
            scanf("%d", &colonneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneInitiale < 0 || colonneInitiale < 0) {
                *quitter = 0;
            } else {
                if(rechercherRafle(dameDeplacement, ligneInitiale, colonneInitiale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneInitiale, colonneInitiale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } else if(verifierCaseVide(damier, ligneInitiale, colonneInitiale)) {
                        printf("La case est vide.Reessayer\n");
                    } else {
                        printf("Le dame n'est pas deplacable.Reessayer\n");
                    }
                }   
            }
        } while(rechercherRafle(dameDeplacement, ligneInitiale, colonneInitiale) == NULL && *quitter != 0);

        do {
            printf("\nEntrer la ligne finale: ");
            scanf("%d", &ligneFinale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne finale: ");
            scanf("%d", &colonneFinale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneFinale < 0 || colonneFinale < 0) {
                *quitter = 0;
            } else {
                if(rechercherRafle(deplacementPossible, ligneFinale, colonneFinale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneFinale, colonneFinale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } if(!verifierCaseVide(damier, ligneFinale, colonneFinale)) {
                        printf("La case n'est pas vide.Reessayer\n");
                    } else {
                        printf("Le dame ne peut pas se deplacer a ce point.Reessayer\n"); 
                    }
                }
            }
        } while(rechercherRafle(deplacementPossible, ligneFinale, colonneFinale) == NULL && *quitter != 0);
    } else { // Rafle disponible
        Rafle *dameMax, *deplacementMax;

        dameMax = trouverPionRafleDeplacementMaximale(damier, dameRafle, joueur->couleur, 1);
        deplacementMax = trouverPionRafleDeplacementMaximale(damier, dameRafle, joueur->couleur, 3);

        do {
            printf("Entrer la ligne initiale: ");
            scanf("%d", &ligneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne initiale: ");
            scanf("%d", &colonneInitiale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneInitiale < 0 || colonneInitiale < 0) {
                *quitter = 0;
            } else {
                if(rechercherRafle(dameDeplacement, ligneInitiale, colonneInitiale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneInitiale, colonneInitiale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } else if(verifierCaseVide(damier, ligneInitiale, colonneInitiale)) {
                        printf("La case est vide.Reessayer\n"); 
                    } else {
                        printf("Une rafle est disponible.Reessayer\n"); 
                    }
                }

                if(rechercherRafle(dameMax, ligneInitiale, colonneInitiale) == NULL) {
                    printf("Une rafle Maximale est disponible.Reessayer\n"); 
                }
            }
        } while(rechercherRafle(dameMax, ligneInitiale, colonneInitiale) == NULL && *quitter != 0);

        do {
            printf("\nEntrer la ligne finale: ");
            scanf("%d", &ligneFinale);

            joueur->temps += (int) (time(NULL) - start);

            printf("\nEntrer la colonne finale: ");
            scanf("%d", &colonneFinale);

            joueur->temps += (int) (time(NULL) - start);

            if(ligneFinale < 0 || colonneFinale) {
                *quitter = 0;
            } else {
                if(rechercherRafle(deplacementMax, ligneFinale, colonneFinale) == NULL) {
                    printf("Deplacement incorrect: ");

                    if(!verifierCaseValide(ligneFinale, colonneFinale)) {
                        printf("La case n'est pas valide.Reessayer\n"); 
                    } else if(!verifierCaseVide(damier, ligneFinale, colonneFinale)) {
                        printf("La case n'est pas vide.Reessayer\n"); 
                    } else {
                        printf("Le dame ne peut pas se deplacer a ce point.Reessayer\n"); 
                    }
                }
            }
        } while(rechercherRafle(deplacementMax, ligneFinale, colonneFinale) == NULL && *quitter != 0);
    }


    deplacement.caseInitiale.ligne = ligneInitiale;
    deplacement.caseInitiale.colonne = colonneInitiale;
    deplacement.caseFinale.ligne = ligneFinale;
    deplacement.caseFinale.colonne = colonneFinale;

    return deplacement;
}


/* Securise la saisie: 1 => tout s'est bien passe; 0 => une erreur */ 
int lire(char *chaine, int longueur) {
    char *positionEntree = NULL;

    if(fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        
        if (positionEntree != NULL) {
            *positionEntree = '\0';
        } else {
            viderBuffer();
        }

        return 1;
    } else {
        viderBuffer();
    
        return 0;
    }
}

/* Vide le buffer si on entre trop de caractere */ 
void viderBuffer() {
    int c = 0;

    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void enregistrerJoeur(int typeJoeur, Joueur *joueur1, Joueur *joueur2) {
    system("clear");
    viderBuffer();
    switch (typeJoeur) {
        case 1:
            // Enregistrement du Joueur Humain
            printf("====== Enregistrement du Joueur ======\n");
            printf("Surnom: ");
            lire(joueur1->surnom, 25);
            printf("\nNom: ");
            lire(joueur1->nom, 25);
            printf("\nPrenom: ");
            lire(joueur1->prenom, 25);
            printf("\nEmail: ");
            lire(joueur1->email, 25);
            joueur1->type = HUMAIN;
            joueur1->tour = 0;
            joueur1->couleur = PION_VERT;

            // Enregistrement du Joueur Machine
            char cpu[30];
            snprintf(cpu, sizeof(cpu), "%s_%d", "CPU", genererNombre(1, 100)); // concatene une chaine avec un nombre
            strcpy(joueur2->surnom, cpu);
            strcpy(joueur2->nom, cpu);
            strcpy(joueur2->prenom, cpu);
            strcpy(joueur2->email, cpu);
            joueur2->type = CPU;
            joueur2->tour = 0;
            joueur2->couleur = PION_ROUGE;
        break; 
        case 2: 
            // Enregistrement du Joueur Humain 1
            printf("====== Enregistrement du Joueur 1 ======\n");
            printf("Surnom: ");
            lire(joueur1->surnom, 25);
            printf("\nNom: ");
            lire(joueur1->nom, 25);
            printf("\nPrenom: ");
            lire(joueur1->prenom, 25);
            printf("\nEmail: ");
            lire(joueur1->email, 25);
            joueur1->type = HUMAIN;
            joueur1->tour = 0;
            joueur1->couleur = PION_VERT;

            // Enregistrement du Joueur Humain 2
            printf("====== Enregistrement du Joueur 2 ======\n");
            printf("Surnom: ");
            lire(joueur2->surnom, 25);
            printf("\nNom: ");
            lire(joueur2->nom, 25);
            printf("\nPrenom: ");
            lire(joueur2->prenom, 25);
            printf("\nEmail: ");
            lire(joueur2->email, 25);
            joueur2->type = HUMAIN;
            joueur2->tour = 0;
            joueur2->couleur = PION_ROUGE;
        break;
    }
}

int genererNombre(int minimum, int maximum) {
    static int limit = 0;

    if(limit == 0) {
        srand(time(NULL));
        limit = 1;
    }

    return (rand() % (maximum - minimum + 1)) + minimum;
}

void afficherAide() {
    system("clear");
    printf("\n====== Aide du Jeu de Dames ======\n");
    printf("Le jeu de dames est un jeu de plateau pour deux joueurs.\n");

    printf("Commandes :\n");
    printf("- Utilisez les coordonnées pour déplacer vos pions.\n");
    printf("- Exemple : '(1, 3) au (0, 4)' pour déplacer une pion de (1, 3) au (0, 4).\n");

    printf("=================================\n");
}

void tabuler(int nombre) {
    for(int i = 0; i < nombre; i++) {
        printf("\t");
    }
}

void cadre(char *nom1, char *nom2, int temps1, int temps2) {
    
    printf("\t\t  ______________________________\n\n");

    printf("\t\t\t%s VS %s\n", nom1, nom2);

    printf("\t\t\t_________________\n\n");

    printf("\t\t  < %d mn %d s > ---- < %d mn %d s >\n", temps1 / 60, temps1 % 60, temps2 / 60, temps2 % 60);

    printf("\t\t  ______________________________\n\n");

}

void initialiserDamier(Damier *damier) {
    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if ((i + j) % 2 == 0 && i < 4) { // Selection des cases blanches de la ligne 0 a 3 : Pion vert
                damier->plateau[i][j] = PION_VERT;
            } else if ((i + j) % 2 == 0 && i > 5) { // Selection des cases blanches de la ligne 6 a 9 : Pion rouge
                damier->plateau[i][j] = PION_ROUGE; 
            } // Les cases comprises entre 4 et 5 sont vides
        }
    }
}

void afficherDamier(Damier *damier, Rafle *rafle, char *nom1, char *nom2, int temps1, int temps2) {
    
    cadre(nom1, nom2, temps1, temps2);

    printf("\t\t   0  1  2  3  4  5  6  7  8  9\n");
    for (int i = 0; i < DIMENSION_PLATEAU; i++) {
        tabuler(2);
        printf("%d ", i);

        for (int j = 0; j < DIMENSION_PLATEAU; j++) {
            if ((i + j) % 2 == 0) { // Selection et Affichage des cases blanches
                if (damier->plateau[i][j] == PION_VERT) { // Affichage des pions verts
                    if(rafle == NULL){
                        printf("\033[47m\033[32m X ");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[43m\033[37m X ");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[32m X ");
                        }
                    }
                } else if(damier->plateau[i][j] == PION_ROUGE) { // Affichage des pions rouges
                    if(rafle == NULL){
                        printf("\033[47m\033[31m O ");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[41m\033[37m O ");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[31m O ");
                        }
                    } 
                } else if (damier->plateau[i][j] == 2 * PION_VERT) { // Affichage des dames verts
                    if(rafle == NULL){
                        printf("\033[47m\033[32m X*");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[43m\033[37m X ");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[32m X*");
                        }
                    }
                } else if(damier->plateau[i][j] == 2 * PION_ROUGE) { // Affichage des pions rouges
                    if(rafle == NULL){
                        printf("\033[47m\033[31m O*");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[41m\033[37m O*");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[31m O*");
                        }
                    }
                } else { // Affichages des cases vides
                    if(rafle == NULL){
                        printf("\033[47m\033[31m   ");
                    } else {
                        Rafle *prises = rafle;
                        int pionPris = 0;

                        while(prises != NULL) {
                            if(i == prises->cases.ligne && j == prises->cases.colonne) {
                                printf("\033[44m\033[37m   ");
                                pionPris = 1;
                                break;   
                            } 
                            prises = prises->suivante;
                        }

                        if(!pionPris) {
                            printf("\033[47m\033[31m   ");
                        }
                    }
                }
            } else { // Selection et Affichage des cases noires
                printf("\033[40m   ");
            }
        }
        printf("\033[0m %d\n", i);
    }
    printf("\t\t   0  1  2  3  4  5  6  7  8  9\n");
}

void nouvellePartie(Damier *damier, int option, int *quitter) {
    int typeJoeur;

    system("clear");
    printf("\nLancer une nouvelle partie...\n");

    do {
        afficherTypeJoeur();
        printf("Entrez le type de joueur: ");
        scanf("%d", &typeJoeur);

        switch (typeJoeur) {
            case 1: // Humain VS Machine
                Joueur humain, machine;
                enregistrerJoeur(1, &humain, &machine);
                humain.tour = 1;
                humain.temps = 0;
                machine.temps = 0;
                printf("\nC:%d\n", humain.couleur);
                jouerPartie(damier, humain, machine, option, 1, quitter);
            break;
            case 2: // Humain VS Humain
                Joueur humain1, humain2;
                enregistrerJoeur(2, &humain1, &humain2);
                humain1.tour = 1;
                humain1.temps = 0;
                humain2.temps = 0;
                jouerPartie(damier, humain1, humain2, option, 1, quitter);
            break;
            case 3:
                printf("Retour au menu principal!\n");
            break;
            case 0:
                *quitter = 0;
                quitterJeu(damier);
            break;
            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 2.\n");
            break;
        }

    } while(typeJoeur != 3 && typeJoeur != 0);
}

void partieExistante(Damier *damier, int *quitter) {
    Joueur joueur1, joueur2;
    int option, confirmation;
    char surnom[25], *nomFichier;

    system("clear");
    printf("\nCharger une partie existante...\n");
    viderBuffer();
    printf("Entrez le surnom: ");
    lire(surnom, 25);

    nomFichier = verifierFichier(surnom);

    if(nomFichier != NULL) { // Le fichier est trouve
        do {
            printf("\nFichier trouvé: %s\n", nomFichier);
            confirmerFichier();
            printf("Entrez la confirmation: ");
            scanf("%d", &confirmation);

            switch (confirmation) {
                case 1: // Fichier trouve confirmer
                    if(chargerPartie(damier, &joueur1, &joueur2, &option, nomFichier)) { // Partie chargee
                        jouerPartie(damier, joueur1, joueur2, option, 0, quitter);
                    } else {
                        printf("\nErreur de chargement...\n");
                    }
                break;
                case 2: // Partie existante
                    printf("Retour au menu principal\n");
                break;
                case 0: // Arreter le jeu
                    *quitter = 0;
                    quitterJeu(damier);
                break;
                default:
                    printf("\nChoix invalide. Veuillez confirmer.\n");
                break;
            }
        } while(confirmation != 2 && confirmation != 0);
    } else {
        printf("Aucun fichier correspondant trouvé.\n");
    }
}

void revisualiserPartie(Damier *damier, int *quitter) {
    Joueur joueur1, joueur2;
    int option, confirmation;
    char surnom[25], *nomFichier;
    long positionCourante = 0;

    system("clear");
    printf("\nCharger une partie existante...\n");
    viderBuffer();
    printf("Entrez le surnom: ");
    lire(surnom, 25);

    nomFichier = verifierFichier(surnom);

    if(nomFichier != NULL) { // Le fichier est trouve
        do {
            printf("\nFichier trouvé: %s\n", nomFichier);
            confirmerFichier();
            printf("Entrez la confirmation: ");
            scanf("%d", &confirmation);

            switch (confirmation) {
                case 1: // Fichier trouve confirmer
                    if(chargerRevisualisation(damier, &joueur1, &joueur2, &option, nomFichier, &positionCourante)) { // Partie chargee
                        afficherRevisualisation(damier, joueur1, joueur2, option, quitter);
                    } else {
                        printf("\nErreur de chargement...\n");
                    }
                break;
                case 2: // Partie existante
                    printf("Retour au menu principal\n");
                break;
                case 0: // Arreter le jeu
                    *quitter = 0;
                    quitterJeu(damier);
                break;
                default:
                    printf("\nChoix invalide. Veuillez confirmer.\n");
                break;
            }
        } while(confirmation != 2 && confirmation != 0);
    } else {
        printf("Aucun fichier correspondant trouvé.\n");
    }
}

void choisirOptions(int *option) {
    system("clear");
    do {
        afficherOptions();
        printf("Entrez le numéro de l'option : \n");
        scanf("%d", option);
    } while(*option != 1 && *option != 2 && *option != 3);
}

void jouerPartie(Damier *damier, Joueur joueur1, Joueur joueur2, int option, int initialiser, int *quitter) {
    Rafle *deplacementPossible = NULL, *raflePossible = NULL, *pionDeplacement = NULL, *pionRafle = NULL, *deplacementRafle = NULL;
    Deplacement deplacementJoeur;

    system("clear");

    if(initialiser ==  1) {
        initialiserDamier(damier);
    }

    while(verifierFinPartie(damier, joueur1, *quitter) && verifierFinPartie(damier, joueur2, *quitter)) {
        if(joueur1.tour) {
            if(verifierPromotionsPions(damier, joueur1.couleur)) { // Verification de l'existence d'un dame dans le plateau
                deplacementPossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 1);
                raflePossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 2);
                pionDeplacement = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 3);
                pionRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 4);
                deplacementRafle = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 5);

                if(raflePossible == NULL) {
                    afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);

                    deplacementJoeur = afficherTourJoueurDame(damier, &joueur1, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);
                    deplacerDame(damier, deplacementJoeur, raflePossible, joueur1.couleur);
                } else {
                    afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);

                    deplacementJoeur = afficherTourJoueurDame(damier, &joueur1, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);
                    
                    Rafle *pionMax, *rafleMax;

                    pionMax = creerRafle(deplacementJoeur.caseInitiale.ligne, deplacementJoeur.caseInitiale.colonne);
                
                    rafleMax = trouverPionRafleDeplacementMaximale(damier, pionMax, joueur1.couleur, 2);

                    deplacerDame(damier, deplacementJoeur, rafleMax, joueur1.couleur);
                }
            } else {
                deplacementPossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 1);
                raflePossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 2);
                pionDeplacement = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 3);
                pionRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 4); // Pion pouvant faire une rafle
                deplacementRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 5); // Deplacement possible lors d'une rafle

                if(raflePossible == NULL) {
                    afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);

                    deplacementJoeur = afficherTourJoueur(damier, &joueur1, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);
                    deplacerPion(damier, deplacementJoeur, raflePossible, joueur1.couleur);
                } else {
                    afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);

                    deplacementJoeur = afficherTourJoueur(damier, &joueur1, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);
                
                    Rafle *pionMax, *rafleMax;

                    pionMax = creerRafle(deplacementJoeur.caseInitiale.ligne, deplacementJoeur.caseInitiale.colonne);
                    
                    rafleMax = trouverPionRafleDeplacementMaximale(damier, pionMax, joueur1.couleur, 2);

                    deplacerPion(damier, deplacementJoeur, rafleMax, joueur1.couleur);
                }

                // Apres deplacement, verifions s'il ya pas lieu de promouvoir un pion en dame
                if(verifierPromotionPion(damier, deplacementJoeur.caseFinale.ligne, deplacementJoeur.caseFinale.ligne, joueur1.couleur)) {
                    promouvoirPion(damier, deplacementJoeur.caseFinale, joueur1.couleur);
                }
            }
            
            joueur1.tour = 0;
            joueur2.tour = 1;

            sauvegarderPartie(damier, joueur1, joueur2, option);
            sauvegarderRevisualisation(damier, joueur1, joueur2, option);
        } else if(joueur2.tour) {
            if(verifierPromotionsPions(damier, joueur1.couleur)) {
                deplacementPossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 1);
                raflePossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 2);
                pionDeplacement = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 3);
                pionRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 4);
                deplacementRafle = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 5);

                if(raflePossible == NULL) {
                    afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);

                    deplacementJoeur = afficherTourJoueurDame(damier, &joueur2, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);
                    deplacerDame(damier, deplacementJoeur, raflePossible, joueur2.couleur);
                } else {
                    afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
                    deplacementJoeur = afficherTourJoueurDame(damier, &joueur2, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);

                    Rafle *pionMax, *rafleMax;

                    pionMax = creerRafle(deplacementJoeur.caseInitiale.ligne, deplacementJoeur.caseInitiale.colonne);
                    
                    rafleMax = trouverPionRafleDeplacementMaximale(damier, pionMax, joueur2.couleur, 2);

                    deplacerDame(damier, deplacementJoeur, rafleMax, joueur2.couleur);
                }

                // deplacementJoeur = afficherTourJoueurDame(damier, &joueur2, deplacementPossible, raflePossible, pionDeplacement, deplacementRafle, option, quitter);
    
                // deplacerDame(damier, deplacementJoeur, raflePossible, joueur2.couleur);
            } else {
                deplacementPossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 1);
                raflePossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 2);
                pionDeplacement = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 3);
                pionRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 4); // Pion pouvant faire une rafle
                deplacementRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 5); // Deplacement possible lors d'une rafle

                if(raflePossible == NULL) {
                    afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);

                    deplacementJoeur = afficherTourJoueur(damier, &joueur2, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);
                    deplacerPion(damier, deplacementJoeur, raflePossible, joueur2.couleur);
                } else {
                    afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);

                    deplacementJoeur = afficherTourJoueur(damier, &joueur2, deplacementPossible, raflePossible, pionDeplacement, pionRafle, deplacementRafle, option, quitter);

                    Rafle *pionMax, *rafleMax;

                    pionMax = creerRafle(deplacementJoeur.caseInitiale.ligne, deplacementJoeur.caseInitiale.colonne);
                    
                    rafleMax = trouverPionRafleDeplacementMaximale(damier, pionMax, joueur2.couleur, 2);

                    deplacerPion(damier, deplacementJoeur, rafleMax, joueur2.couleur);
                }

                // Apres deplacement, verifions s'il ya pas lieu de promouvoir un pion en dame
                if(verifierPromotionPion(damier, deplacementJoeur.caseFinale.ligne, deplacementJoeur.caseFinale.ligne, joueur2.couleur)) {
                    promouvoirPion(damier, deplacementJoeur.caseFinale, joueur2.couleur);
                }
            }

            joueur2.tour = 0;
            joueur1.tour = 1;

            sauvegarderPartie(damier, joueur1, joueur2, option);
            sauvegarderRevisualisation(damier, joueur1, joueur2, option);
        }
    }

    if(verifierGagnant(damier, joueur1, joueur2, *quitter) != 0) {
        afficherGagnant(joueur1, joueur2, verifierGagnant(damier, joueur1, joueur2, *quitter));

        // On libere la memeoire et on quitte le jeu
        libererMemoire(NULL, pionDeplacement);
        libererMemoire(NULL, raflePossible);
        libererMemoire(NULL, pionRafle);
        libererMemoire(NULL, deplacementRafle);

        *quitter = 0;
    }
}

int VerifierRepertoire(char *chemin) {
    DIR *repertoire = opendir(chemin);

    if (repertoire) { // Le répertoire existe
        closedir(repertoire);

        return 1;
    } else { // Le répertoire n'existe pas ou une erreur s'est produite
        
        return 0;
    }
}

char * verifierFichier(char *nomFichier) {
    struct dirent *lecture;
    DIR *repertoire;

    repertoire = opendir("./Sauvegarde");  // Ouvre le répertoire
    
    if(repertoire == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");

        return 0;
    } else {
        while ((lecture = readdir(repertoire)) != NULL) {
            if (strstr(lecture->d_name, nomFichier) != NULL) { // Vérifie si le nom du fichier est contenu dans le nom actuel
                
                return lecture->d_name;
            }
        }
        closedir(repertoire);

        return NULL;   
    }
}

void sauvegarderPartie(Damier *damier, Joueur joueur1, Joueur joueur2, int option) {
    char source[255];
    FILE *file = NULL;

    if (!VerifierRepertoire("./Sauvegarde")) { // Le repertoire n'existe pas
        system("mkdir ./Sauvegarde");
    }

    snprintf(source, sizeof(source), "./%s/%s_%s.bagus", "Sauvegarde", joueur1.surnom, joueur2.surnom);

    printf("\n%s\n", source);

    file = fopen(source, "wb");

    if(file != NULL) {
        // Surnom Nom Prenom Email Type Couleur Tour
        fprintf(file, "%s %s %s %s %d %d %d %d\n", joueur1.surnom, joueur1.nom, joueur1.prenom, joueur1.email, joueur1.type, joueur1.couleur, joueur1.tour, joueur1.temps);
        // Surnom Nom Prenom Email Type Couleur Tour
        fprintf(file, "%s %s %s %s %d %d %d %d\n", joueur2.surnom, joueur2.nom, joueur2.prenom, joueur2.email, joueur2.type, joueur2.couleur, joueur2.tour, joueur2.temps);
        // Option
        fprintf(file, "%d\n", option);

        for (int i = 0; i < DIMENSION_PLATEAU; i++) {
            for (int j = 0; j < DIMENSION_PLATEAU; j++) {
                fprintf(file, "%d ", damier->plateau[i][j]);
            }

            fprintf(file, "\n");
        }

        fclose(file);
        // printf("Partie sauvegardée avec succès dans le fichier %s.\n", nomFichier);
    } else {
        printf("\nErreur de sauvegarde...\n");
    }
}

void sauvegarderRevisualisation(Damier *damier, Joueur joueur1, Joueur joueur2, int option) {
    char source[255];
    FILE *file = NULL;

    if (!VerifierRepertoire("./Revisualisation")) { // Le repertoire n'existe pas
        system("mkdir ./Revisualisation");
    }

    snprintf(source, sizeof(source), "./%s/%s_%s.bagus", "Revisualisation", joueur1.surnom, joueur2.surnom);

    printf("\n%s\n", source);

    file = fopen(source, "ab");

    if(file != NULL) {
        // Surnom Nom Prenom Email Type Couleur Tour
        fprintf(file, "%s %s %s %s %d %d %d %d\n", joueur1.surnom, joueur1.nom, joueur1.prenom, joueur1.email, joueur1.type, joueur1.couleur, joueur1.tour, joueur1.temps);
        // Surnom Nom Prenom Email Type Couleur Tour
        fprintf(file, "%s %s %s %s %d %d %d %d\n", joueur2.surnom, joueur2.nom, joueur2.prenom, joueur2.email, joueur2.type, joueur2.couleur, joueur2.tour, joueur2.temps);
        // Option
        fprintf(file, "%d\n", option);

        for (int i = 0; i < DIMENSION_PLATEAU; i++) {
            for (int j = 0; j < DIMENSION_PLATEAU; j++) {
                fprintf(file, "%d ", damier->plateau[i][j]);
            }

            fprintf(file, "\n");
        }

        fclose(file);
    } else {
        printf("\nErreur de sauvegarde...\n");
    }
}

int chargerPartie(Damier *damier, Joueur *joueur1, Joueur *joueur2, int *option, char *nomFichier) {
    char source[255];
    FILE *file = NULL;

    snprintf(source, sizeof(source), "./%s/%s", "Sauvegarde", nomFichier);

    file = fopen(source, "rb");

    if(file != NULL) {
        // Surnom Nom Prenom Email Type Couleur Tour
        fscanf(file, "%s %s %s %s %d %d %d %d\n", joueur1->surnom, joueur1->nom, joueur1->prenom, joueur1->email, &joueur1->type, &joueur1->couleur, &joueur1->tour, &joueur1->temps);
        // Surnom Nom Prenom Email Type Couleur Tour
        fscanf(file, "%s %s %s %s %d %d %d %d\n", joueur2->surnom, joueur2->nom, joueur2->prenom, joueur2->email, &joueur2->type, &joueur2->couleur, &joueur2->tour, &joueur2->temps);
        // Option
        fscanf(file, "%d\n", option);
        for (int i = 0; i < DIMENSION_PLATEAU; i++) {
            for (int j = 0; j < DIMENSION_PLATEAU; j++) {
                fscanf(file, "%d ", &damier->plateau[i][j]);
            }
        }
        fclose(file);

        return 1;
    } else {

        return 0;
    }
}

int chargerRevisualisation(Damier *damier, Joueur *joueur1, Joueur *joueur2, int *option, char *nomFichier, long *positionCourante) {
    char source[255];
    FILE *file = NULL;

    snprintf(source, sizeof(source), "./%s/%s", "Revisualisation", nomFichier);

    file = fopen(source, "rb");

    if(file != NULL) {

        fseek(file, *positionCourante, SEEK_SET);

        // Surnom Nom Prenom Email Type Couleur Tour
        fscanf(file, "%s %s %s %s %d %d %d %d\n", joueur1->surnom, joueur1->nom, joueur1->prenom, joueur1->email, &joueur1->type, &joueur1->couleur, &joueur1->tour, &joueur1->temps);
        // Surnom Nom Prenom Email Type Couleur Tour
        fscanf(file, "%s %s %s %s %d %d %d %d\n", joueur2->surnom, joueur2->nom, joueur2->prenom, joueur2->email, &joueur2->type, &joueur2->couleur, &joueur2->tour, &joueur2->temps);
        // Option
        fscanf(file, "%d\n", option);
        for (int i = 0; i < DIMENSION_PLATEAU; i++) {
            for (int j = 0; j < DIMENSION_PLATEAU; j++) {
                fscanf(file, "%d ", &damier->plateau[i][j]);
            }
        }

        *positionCourante = ftell(file);

        fclose(file);

        return 1;
    } else {

        return 0;
    }
}

void afficherRevisualisation(Damier *damier, Joueur joueur1, Joueur joueur2, int option, int *quitter) {
    Rafle *deplacementPossible = NULL, *raflePossible = NULL;
    // , *pionDeplacement = NULL, *pionRafle = NULL, *deplacementRafle = NULL;

    system("clear");

    if(joueur1.tour) {
        if(verifierPromotionsPions(damier, joueur1.couleur)) {
            deplacementPossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 1);
            raflePossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 2);
            // pionDeplacement = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 3);
            // deplacementRafle = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur1.couleur, 4);

            if(raflePossible == NULL) {
                afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            } else {
                afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            }
        } else {
            deplacementPossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 1);
            raflePossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 2);
            // pionDeplacement = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 3);
            // pionRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 4); // Pion pouvant faire une rafle
            // deplacementRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur1.couleur, 5); // Deplacement possible lors d'une rafle

            if(raflePossible == NULL) {
                afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            } else {
                afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            }
        }
    } else if(joueur2.tour) {
        if(verifierPromotionsPions(damier, joueur1.couleur)) {
            deplacementPossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 1);
            raflePossible = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 2);
            // pionDeplacement = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 3);
            // deplacementRafle = trouverDeplacementsEtRaflesPossiblesDames(damier, joueur2.couleur, 4);

            if(raflePossible == NULL) {
                afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            } else {
                afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            }
        } else {
            deplacementPossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 1);
            raflePossible = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 2);
            // pionDeplacement = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 3);
            // pionRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 4); // Pion pouvant faire une rafle
            // deplacementRafle = trouverDeplacementsEtRaflesPossiblesPions(damier, joueur2.couleur, 5); // Deplacement possible lors d'une rafle

            if(raflePossible == NULL) {
                afficherDamier(damier, deplacementPossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            } else {
                afficherDamier(damier, raflePossible, joueur1.surnom, joueur2.surnom, joueur1.temps, joueur2.temps);
            }
        }
    }
}

void afficherGagnant(Joueur joueur1, Joueur joueur2, int couleurPion) {
    printf("\t\t  ______________________________\n\n");

    printf("\t\t\t%s VS %s\n", joueur1.surnom, joueur2.surnom);

    printf("\t\t\t_________________\n\n");

    if(joueur1.couleur == couleurPion) {
        printf("\t\tBravo %s 🥳! Victoire méritée ! 🏆🎉\n", joueur1.surnom);
    } else {
        printf("\t\tBravo %s 🥳! Victoire méritée ! 🏆🎉\n", joueur2.surnom);
    }

    printf("\t\t_______________________________________\n\n");
}

void quitterJeu(Damier *damier) {    
    printf("\t\t  ______________________________\n\n");

    printf("\t\t\tArret du jeu...\n");
    printf("\t\t\tAurevoir\n");

    printf("\t\t\t_________________\n\n");
    
    libererMemoire(damier, NULL);
}
