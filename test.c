// // switch (choix) {
// //         case 1: // Deplacement possible
// //             return deplacement;
// //         break;
// //         case 2: // Deplacement a gauche
// //             return deplacementG;
// //         break;
// //         case 3: // Deplacement a droite
// //             return deplacementD;
// //         break;
// //         case 4: // Rafle possible
// //             return rafle;
// //         break;
// //         case 5: // Rafle a gauche
// //             return rafleG;
// //         break;
// //         case 6: // Rafle arriere a gauche
// //             return rafleAG;
// //         break;
// //         case 7: // Rafle a droite
// //             return rafleD;
// //         break;
// //         case 8: // Rafle arriere a droite
// //             return rafleAD;
// //         break;
// //         case 9: // Pions deplacables a gauche
// //             return pionDeplacementG;
// //         break;
// //         case 10: // Pions deplacables arriere a gauche
// //             return pionDeplacementAG;
// //         break;
// //         case 11: // Pions deplacables a droite
// //             return pionDeplacementD;
// //         break;
// //         case 12: // Pions deplacables arriere a droite
// //             return pionDeplacementAD;
// //         break;
// //         case 13: // Pion pouvant rafler a gauche
// //             return pionRafleG;
// //         break;
// //         case 14: // Pion pouvant rafler arriere a gauche
// //             return pionRafleAG;
// //         break;
// //         case 15: // Pion pouvant rafler a droite
// //             return pionRafleD;
// //         break;
// //         case 16: // Pion pouvant rafler arriere a droite
// //             return pionRafleAD;
// //         break;
// //         case 17: // Deplacement possible des pions pouvant rafler a gauche
// //             return deplacementRafleG;
// //         break;
// //         case 18: // Deplacement possible des pions pouvant rafler arriere a gauche
// //             return deplacementRafleAG;
// //         break;
// //         case 19: // Deplacement possible des pions pouvant rafler a droite
// //             return deplacementRafleD;
// //         break;
// //         case 20: // Deplacement possible des pions pouvant rafler arriere a droite
// //             return deplacementRafleAD;
// //         break;
// //         default:
// //             return NULL;
// //         break;
// //     }





// Rafle * deplacementEtRaflePossiblesPion(Damier *damier, int ligne, int colonne, int couleurPion, int choix) {
//     // Rafle *deplacement = NULL, *rafle = NULL, *pionDeplacement = NULL, *pionRafle = NULL, *deplacementRafle = NULL;
//     Rafle *deplacement = NULL, *rafle = NULL;
//     Rafle *deplacementG = NULL, *rafleG = NULL;
//     Rafle *deplacementD = NULL, *rafleD = NULL;
//     Rafle *rafleAD = NULL;
//     Rafle *rafleAG = NULL;
//     Rafle *pionDeplacementG = NULL, *pionRafleG = NULL, *deplacementRafleG = NULL;
//     Rafle *pionDeplacementD = NULL, *pionRafleD = NULL, *deplacementRafleD = NULL;
//     Rafle *pionDeplacementAD = NULL, *pionRafleAD = NULL, *deplacementRafleAD = NULL;
//     Rafle *pionDeplacementAG = NULL, *pionRafleAG = NULL, *deplacementRafleAG = NULL;

//     if((damier->plateau[ligne][colonne] == PION_VERT) && (couleurPion == PION_VERT)) { // Selection des pions Verts
//         if(verifierCaseValide(ligne + 1, colonne - 1)) { // Deplacement a gauche possible
//             if(damier->plateau[ligne + 1][colonne - 1] == CASE_VIDE) {
//                 pionDeplacementG = insererRafle(pionDeplacementG, creerRafle(ligne, colonne));
//                 deplacementG = insererRafle(deplacementG, creerRafle(ligne + 1, colonne - 1));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne - 1));
//             } else if((damier->plateau[ligne + 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
//                 damier->plateau[ligne + 2][colonne - 2] = PION_VERT; // On suppose que la prise est bonne, donc on avance
                
//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 4); // Verification d'une rafle disponible


//                 pionRafleG = insererRafle(pionRafleG, creerRafle(ligne, colonne));
//                 rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne - 1));
//                 rafleG = insererRafle(rafleG, creerRafle(ligne + 1, colonne - 1));
//                 deplacementRafleG = insererRafle(deplacementRafleG, creerRafle(ligne + 2, colonne - 2));

//                 if(recursif != NULL) { // Recherche de toutes les rafles disponibles recursivements
//                     pionRafleG = insererRafle(pionRafleG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 13));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 4));
//                     rafleG = insererRafle(rafleG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 5));
//                     deplacementRafleG = insererRafle(deplacementRafleG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 17));
//                 }

//                 damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE; // Fin du supposition
//             }
//         }

//         if(verifierCaseValide(ligne + 1, colonne + 1)) { // Deplacement a droite possible
//             if(damier->plateau[ligne + 1][colonne + 1] == CASE_VIDE) {
//                 pionDeplacementD = insererRafle(pionDeplacementD, creerRafle(ligne, colonne));
//                 deplacementD = insererRafle(deplacementD, creerRafle(ligne + 1, colonne + 1));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne + 1));
//             } else if((damier->plateau[ligne + 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
//                 damier->plateau[ligne + 2][colonne + 2] = PION_VERT;

//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 4);

//                 pionRafleD = insererRafle(pionRafleD, creerRafle(ligne, colonne));
//                 rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne + 1));
//                 rafleD = insererRafle(rafleD, creerRafle(ligne + 1, colonne + 1));
//                 deplacementRafleD = insererRafle(deplacementRafleD, creerRafle(ligne + 2, colonne + 2));

//                 if(recursif != NULL) {
//                     pionRafleD = insererRafle(pionRafleD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 15));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 4));
//                     rafleD = insererRafle(rafleD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 7));
//                     deplacementRafleD = insererRafle(deplacementRafleD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 19));
//                 }

//                 damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE;
//             }
//         }


//         if(verifierCaseValide(ligne - 1, colonne + 1)) { // Rafle arriere a droite possible
//             if((damier->plateau[ligne - 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { 
//                 damier->plateau[ligne - 2][colonne + 2] = PION_VERT;
                
//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 4);

//                 pionRafleAD = insererRafle(pionRafleAD, creerRafle(ligne, colonne));
//                 rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne + 1));
//                 rafleAD = insererRafle(rafleAD, creerRafle(ligne - 1, colonne + 1));
//                 deplacementRafleAD = insererRafle(deplacementRafleAD, creerRafle(ligne - 2, colonne + 2));

//                 if(recursif != NULL) {
//                     pionRafleAD = insererRafle(pionRafleAD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 16));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 4));
//                     rafleAD = insererRafle(rafleAD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 8));
//                     deplacementRafleAD = insererRafle(deplacementRafleAD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 20));
//                 }

//                 damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE;
//             }
//         }

//         if(verifierCaseValide(ligne - 1, colonne - 1)) { // Rafle arriere a gauche possible
//             if((damier->plateau[ligne - 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { 
//                 damier->plateau[ligne - 2][colonne - 2] = PION_VERT;
                
//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 4);

//                 pionRafleAG = insererRafle(pionRafleAG, creerRafle(ligne, colonne));
//                 rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne - 1));
//                 rafleAG = insererRafle(rafleAG, creerRafle(ligne - 1, colonne - 1));
//                 deplacementRafleAG = insererRafle(deplacementRafleAG, creerRafle(ligne - 2, colonne - 2));

//                 if(recursif != NULL) {
//                     pionRafleAG = insererRafle(pionRafleAG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 14));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 4));
//                     rafleAG = insererRafle(rafleAG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 6));
//                     deplacementRafleAG = insererRafle(deplacementRafleAG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 18));
//                 }

//                 damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE;
//             }
//         }
//     } else if((damier->plateau[ligne][colonne] == PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des pions Rouges
//         if(verifierCaseValide(ligne - 1, colonne + 1)) { // Deplacement a droite possible
//             if(damier->plateau[ligne - 1][colonne + 1] == CASE_VIDE) { 
//                 pionDeplacementD = insererRafle(pionDeplacementD, creerRafle(ligne, colonne));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne + 1));
//                 deplacementD = insererRafle(deplacementD, creerRafle(ligne - 1, colonne + 1));
//             } else if((damier->plateau[ligne - 1][colonne + 1] == PION_VERT || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions verts a droite
//                 damier->plateau[ligne - 2][colonne + 2] = PION_ROUGE;
                
//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 4);

//                 pionRafleD = insererRafle(pionRafleD, creerRafle(ligne, colonne));
//                 rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne + 1));
//                 rafleD = insererRafle(rafleD, creerRafle(ligne - 1, colonne + 1));
//                 deplacementRafleD = insererRafle(deplacementRafleD, creerRafle(ligne - 2, colonne + 2));

//                 if(recursif != NULL) {
//                     pionRafleD = insererRafle(pionRafleD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 15));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 4));
//                     rafleD = insererRafle(rafleD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 7));
//                     deplacementRafleD = insererRafle(deplacementRafleD, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 19));
//                 }

//                 damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE;
//             }
//         }

//         if(verifierCaseValide(ligne - 1, colonne - 1)) { // Deplacement a gauche possible
//             if(damier->plateau[ligne - 1][colonne - 1] == CASE_VIDE) { 
//                 pionDeplacementG = insererRafle(pionDeplacementG, creerRafle(ligne, colonne));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne - 1));
//                 deplacementG = insererRafle(deplacementG, creerRafle(ligne - 1, colonne - 1));
//             } else if((damier->plateau[ligne - 1][colonne - 1] == PION_VERT || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions verts a gauche
//                 damier->plateau[ligne - 2][colonne - 2] = PION_ROUGE;
                
//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 4);

//                 pionRafleG = insererRafle(pionRafleG, creerRafle(ligne, colonne));
//                 rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne - 1));
//                 rafleG = insererRafle(rafleG, creerRafle(ligne - 1, colonne - 1));
//                 deplacementRafleG = insererRafle(deplacementRafleG, creerRafle(ligne - 2, colonne - 2));

//                 if(recursif != NULL) {
//                     pionRafleG = insererRafle(pionRafleG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 13));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 4));
//                     rafleG = insererRafle(rafleG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 5));
//                     deplacementRafleG = insererRafle(deplacementRafleG, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 17));
//                 }

//                 damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE;
//             }
//         }


//         if(verifierCaseValide(ligne + 1, colonne - 1)) { // Rafle arriere a gauche possible
//             if((damier->plateau[ligne + 1][colonne - 1] == PION_VERT || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
//                 damier->plateau[ligne + 2][colonne - 2] = PION_ROUGE;
                
//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 4);

//                 pionRafleAG = insererRafle(pionRafleAG, creerRafle(ligne, colonne));
//                 rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne - 1));
//                 rafleAG = insererRafle(rafleAG, creerRafle(ligne + 1, colonne - 1));
//                 deplacementRafleAG = insererRafle(deplacementRafleAG, creerRafle(ligne + 2, colonne - 2));

//                 if(recursif != NULL) {
//                     pionRafleAG = insererRafle(pionRafleAG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 14));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 4));
//                     rafleAG = insererRafle(rafleAG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 6));
//                     deplacementRafleAG = insererRafle(deplacementRafleAG, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 18));
//                 }

//                 damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE;
//             }
//         }

//         if(verifierCaseValide(ligne + 1, colonne + 1)) { // Rafle arriere a droite possible
//             if((damier->plateau[ligne + 1][colonne + 1] == PION_VERT || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
//                 damier->plateau[ligne + 2][colonne + 2] = PION_ROUGE;
                
//                 Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 4);

//                 pionRafleAD = insererRafle(pionRafleAD, creerRafle(ligne, colonne));
//                 rafleAD = insererRafle(rafleAD, creerRafle(ligne + 1, colonne + 1));
//                 deplacementRafleAD = insererRafle(deplacementRafleAD, creerRafle(ligne + 2, colonne + 2));

//                 if(recursif != NULL) {
//                     pionRafleAD = insererRafle(pionRafleAD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 16));
//                     rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 4));
//                     rafleAD = insererRafle(rafleAD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 8));
//                     deplacementRafleAD = insererRafle(deplacementRafleAD, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 20));
//                 }

//                 damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE;
//             }
//         }
//     }

//     switch (choix) {
//         case 1: // Deplacement possible
//             return deplacement;
//         break;
//         case 2: // Deplacement a gauche
//             return deplacementG;
//         break;
//         case 3: // Deplacement a droite
//             return deplacementD;
//         break;
//         case 4: // Rafle possible
//             return rafle;
//         break;
//         case 5: // Rafle a gauche
//             return rafleG;
//         break;
//         case 6: // Rafle arriere a gauche
//             return rafleAG;
//         break;
//         case 7: // Rafle a droite
//             return rafleD;
//         break;
//         case 8: // Rafle arriere a droite
//             return rafleAD;
//         break;
//         case 9: // Pions deplacables a gauche
//             return pionDeplacementG;
//         break;
//         case 10: // Pions deplacables arriere a gauche
//             return pionDeplacementAG;
//         break;
//         case 11: // Pions deplacables a droite
//             return pionDeplacementD;
//         break;
//         case 12: // Pions deplacables arriere a droite
//             return pionDeplacementAD;
//         break;
//         case 13: // Pion pouvant rafler a gauche
//             return pionRafleG;
//         break;
//         case 14: // Pion pouvant rafler arriere a gauche
//             return pionRafleAG;
//         break;
//         case 15: // Pion pouvant rafler a droite
//             return pionRafleD;
//         break;
//         case 16: // Pion pouvant rafler arriere a droite
//             return pionRafleAD;
//         break;
//         case 17: // Deplacement possible des pions pouvant rafler a gauche
//             return deplacementRafleG;
//         break;
//         case 18: // Deplacement possible des pions pouvant rafler arriere a gauche
//             return deplacementRafleAG;
//         break;
//         case 19: // Deplacement possible des pions pouvant rafler a droite
//             return deplacementRafleD;
//         break;
//         case 20: // Deplacement possible des pions pouvant rafler arriere a droite
//             return deplacementRafleAD;
//         break;
//         default:
//             return NULL;
//         break;
//     }
// }



switch (choix) {
        case 1: // Deplacement possible
            return deplacement;
        break;
        case 2: // Deplacement a gauche
            return deplacementG;
        break;
        case 3: // Deplacement a droite
            return deplacementD;
        break;
        case 4: // Rafle possible
            return rafle;
        break;
        case 5: // Rafle a gauche
            return rafleG;
        break;
        case 6: // Rafle arriere a gauche
            return rafleAG;
        break;
        case 7: // Rafle a droite
            return rafleD;
        break;
        case 8: // Rafle arriere a droite
            return rafleAD;
        break;
        case 9: // Pions deplacables possible
            return pionDeplacement;
        break;
        case 10: // Pions deplacables a gauche
            return pionDeplacementG;
        break;
        case 11: // Pions deplacables arriere a gauche
            return pionDeplacementAG;
        break;
        case 12: // Pions deplacables a droite
            return pionDeplacementD;
        break;
        case 13: // Pions deplacables arriere a droite
            return pionDeplacementAD;
        break;
        case 14: // Pion pouvant rafler possible
            return pionRafle;
        break;
        case 15: // Pion pouvant rafler a gauche
            return pionRafleG;
        break;
        case 16: // Pion pouvant rafler arriere a gauche
            return pionRafleAG;
        break;
        case 17: // Pion pouvant rafler a droite
            return pionRafleD;
        break;
        case 18: // Pion pouvant rafler arriere a droite
            return pionRafleAD;
        break;
        case 19: // Deplacement possible des pions pouvant rafler
            return deplacementRafle;
        break;
        case 20: // Deplacement possible des pions pouvant rafler a gauche
            return deplacementRafleG;
        break;
        case 21: // Deplacement possible des pions pouvant rafler arriere a gauche
            return deplacementRafleAG;
        break;
        case 22: // Deplacement possible des pions pouvant rafler a droite
            return deplacementRafleD;
        break;
        case 23: // Deplacement possible des pions pouvant rafler arriere a droite
            return deplacementRafleAD;
        break;
        default:
            return NULL;
        break;
    }



    /***********************/

Rafle * deplacementPossiblesPion(Damier *damier, int ligne, int colonne, int couleurPion, int choix) {
    Rafle *deplacement = NULL, *pionDeplacement = NULL, *deplacementD = NULL;
    
    if((damier->plateau[ligne][colonne] == PION_VERT) && (couleurPion == PION_VERT)) { // Selection des pions Verts
        if(verifierCaseValide(ligne + 1, colonne - 1)) { // Deplacement a gauche possible
            if(damier->plateau[ligne + 1][colonne - 1] == CASE_VIDE) {
                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne - 1));
            }
        }

        if(verifierCaseValide(ligne + 1, colonne + 1)) { // Deplacement a droite possible
            if(damier->plateau[ligne + 1][colonne + 1] == CASE_VIDE) {
                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne + 1));
            }
        }
    } else if((damier->plateau[ligne][colonne] == PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des pions Rouges
        if(verifierCaseValide(ligne - 1, colonne + 1)) { // Deplacement a droite possible
            if(damier->plateau[ligne - 1][colonne + 1] == CASE_VIDE) { 
                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne + 1));
            }
        }

        if(verifierCaseValide(ligne - 1, colonne - 1)) { // Deplacement a gauche possible
            if(damier->plateau[ligne - 1][colonne - 1] == CASE_VIDE) { 
                pionDeplacementG = insererRafle(pionDeplacementG, creerRafle(ligne, colonne));
                deplacementG = insererRafle(deplacementG, creerRafle(ligne - 1, colonne - 1));
                
                pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
                deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne - 1));
            }
        }
    }

    switch (choix) {
        case 1: // Deplacement possible
            return deplacement;
        break;
        case 2: // Pions deplacables possible
            return pionDeplacement;
        break;
        default:
            return NULL;
        break;
    }
}


/*****************/ 
Rafle * raflePossiblesPion(Damier *damier, int ligne, int colonne, int couleurPion, int choix) {
    Rafle *rafle = NULL, *pionRafle = NULL, *deplacementRafle = NULL;

    if((damier->plateau[ligne][colonne] == PION_VERT) && (couleurPion == PION_VERT)) { // Selection des pions Verts
        if(verifierCaseValide(ligne + 1, colonne - 1)) { // rafle a gauche possible
            if((damier->plateau[ligne + 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
                damier->plateau[ligne + 2][colonne - 2] = PION_VERT; // On suppose que la prise est bonne, donc on avance
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 4); // Verification d'une rafle disponible

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne - 2));

                if(recursif != NULL) { // Recherche de toutes les rafles disponibles recursivements
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 14)); 
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 4)); 
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_VERT, 19)); 
                }

                damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE; // Fin du supposition
            }
        }

        if(verifierCaseValide(ligne + 1, colonne + 1)) { // Deplacement a droite possible
            if((damier->plateau[ligne + 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
                damier->plateau[ligne + 2][colonne + 2] = PION_VERT;

                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 4);

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_VERT, 19));
                }

                damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE;
            }
        }


        if(verifierCaseValide(ligne - 1, colonne + 1)) { // Rafle arriere a droite possible
            if((damier->plateau[ligne - 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { 
                damier->plateau[ligne - 2][colonne + 2] = PION_VERT;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 4);

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_VERT, 19));
                }

                damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE;
            }
        }

        if(verifierCaseValide(ligne - 1, colonne - 1)) { // Rafle arriere a gauche possible
            if((damier->plateau[ligne - 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { 
                damier->plateau[ligne - 2][colonne - 2] = PION_VERT;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 4);

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne - 2));

                if(recursif != NULL) {
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_VERT, 19));
                }

                damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE;
            }
        }
    } else if((damier->plateau[ligne][colonne] == PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des pions Rouges
        if(verifierCaseValide(ligne - 1, colonne + 1)) { // Deplacement a droite possible
            if((damier->plateau[ligne - 1][colonne + 1] == PION_VERT || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions verts a droite
                damier->plateau[ligne - 2][colonne + 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 4);

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne + 2, PION_ROUGE, 19));
                }

                damier->plateau[ligne - 2][colonne + 2] = CASE_VIDE;
            }
        }

        if(verifierCaseValide(ligne - 1, colonne - 1)) { // Deplacement a gauche possible
            if((damier->plateau[ligne - 1][colonne - 1] == PION_VERT || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions verts a gauche
                damier->plateau[ligne - 2][colonne - 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 4);

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne - 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2, colonne - 2));

                if(recursif != NULL) {
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne - 2, colonne - 2, PION_ROUGE, 19));
                }

                damier->plateau[ligne - 2][colonne - 2] = CASE_VIDE;
            }
        }


        if(verifierCaseValide(ligne + 1, colonne - 1)) { // Rafle arriere a gauche possible
            if((damier->plateau[ligne + 1][colonne - 1] == PION_VERT || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
                damier->plateau[ligne + 2][colonne - 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 1);

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne - 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne - 2));

                if(recursif != NULL) {
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 14));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 4));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne - 2, PION_ROUGE, 19));
                }

                damier->plateau[ligne + 2][colonne - 2] = CASE_VIDE;
            }
        }

        if(verifierCaseValide(ligne + 1, colonne + 1)) { // Rafle arriere a droite possible
            if((damier->plateau[ligne + 1][colonne + 1] == PION_VERT || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
                damier->plateau[ligne + 2][colonne + 2] = PION_ROUGE;
                
                Rafle *recursif = deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 1);

                pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
                rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne + 1));
                deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne + 2));

                if(recursif != NULL) {
                    pionRafle = insererRafle(pionRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 2));
                    rafle = insererRafle(rafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 1));
                    deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesPion(damier, ligne + 2, colonne + 2, PION_ROUGE, 3));
                }

                damier->plateau[ligne + 2][colonne + 2] = CASE_VIDE;
            }
        }
    }

    switch (choix) {
        case 1: // Rafle possible
            return rafle;
        break;
        case 2: // Pion pouvant rafler possible
            return pionRafle;
        break;
        case 3: // Deplacement possible des pions pouvant rafler
            return deplacementRafle;
        break;
        default:
            return NULL;
        break;
    }
}

/*****************/ 
 





 Rafle * trouverRafleMaximale(Damier *damier, Rafle *pionRafle, int couleurPion) {
    Rafle *p = pionRafle, *rafleMaximale = NULL; 
    int longueurMaximale = 0; 

    while (p != NULL) {
        int longueurGauche = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 20));
        int longueurArriereGauche = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 21));
        int longueurDroite = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 22));
        int longueurArriereDroite = longueurRafle(deplacementEtRaflePossiblesPion(damier, p->cases.ligne, p->cases.colonne, couleurPion, 23));

        // Comparaison des longueurs et mise à jour de la rafle maximale
        if (longueurGauche > longueurMaximale) {
            longueurMaximale = longueurGauche;
            rafleMaximale = p;
        } else if (longueurArriereGauche > longueurMaximale) {
            longueurMaximale = longueurArriereGauche;
            rafleMaximale = p;
        } else if (longueurDroite > longueurMaximale) {
            longueurMaximale = longueurDroite;
            rafleMaximale = p;
        } else if (longueurArriereDroite > longueurMaximale) {
            longueurMaximale = longueurArriereDroite;
            rafleMaximale = p;
        }

        p = p->suivante;
    }

    return rafleMaximale;
}




switch (choix) {
        case 1: // Deplacement possible
            return deplacement;
        break;
        case 2: // Deplacement a gauche
            return deplacementG;
        break;
        case 3: // Deplacement arriere a gauche
            return deplacementAG;
        break;
        case 4: // Deplacement a droite
            return deplacementD;
        break;
        case 5: // Deplacement arriere a droite
            return deplacementAD;
        break;
        case 6: // Rafle possible
            return rafle;
        break;
        case 7: // Rafle a gauche
            return rafleG;
        break;
        case 8: // Rafle arriere a gauche
            return rafleAG;
        break;
        case 9: // Rafle a droite
            return rafleD;
        break;
        case 10: // Rafle arriere a droite
            return rafleAD;
        break;
        case 11: // Pions deplacables possible
            return dameDeplacement;
        break;
        case 12: // Pions deplacables a gauche
            return dameDeplacementG;
        break;
        case 13: // Pions deplacables arriere a gauche
            return dameDeplacementAG;
        break;
        case 14: // Pions deplacables a droite
            return dameDeplacementD;
        break;
        case 15: // Pions deplacables arriere a droite
            return dameDeplacementAD;
        break;
        case 16: // Pion pouvant rafler possible
            return dameRafle;
        break;
        case 17: // Pion pouvant rafler a gauche
            return dameRafleG;
        break;
        case 18: // Pion pouvant rafler arriere a gauche
            return dameRafleAG;
        break;
        case 19: // Pion pouvant rafler a droite
            return dameRafleD;
        break;
        case 20: // Pion pouvant rafler arriere a droite
            return dameRafleAD;
        break;
        case 21: // Deplacement possible des pions pouvant rafler
            return deplacementRafle;
        break;
        case 22: // Deplacement possible des pions pouvant rafler a gauche
            return deplacementRafleG;
        break;
        case 23: // Deplacement possible des pions pouvant rafler arriere a gauche
            return deplacementRafleAG;
        break;
        case 24: // Deplacement possible des pions pouvant rafler a droite
            return deplacementRafleD;
        break;
        case 25: // Deplacement possible des pions pouvant rafler arriere a droite
            return deplacementRafleAD;
        break;
        default:
            return NULL;
        break;




// Rafle * deplacementEtRaflePossiblesPion(Damier *damier, int ligne, int colonne, int couleurPion, int choix) {
//     Rafle *deplacement = NULL, *rafle = NULL, *pionDeplacement = NULL, *pionRafle = NULL, *deplacementRafle = NULL;

//     if((damier->plateau[ligne][colonne] == PION_VERT) && (couleurPion == PION_VERT)) { // Selection des pions Verts
//         if(verifierCaseValide(ligne + 1, colonne - 1)) { // Deplacement a gauche possible
//             if(damier->plateau[ligne + 1][colonne - 1] == CASE_VIDE) {
//                 pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne - 1));
//             } else if((damier->plateau[ligne + 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
//                 int i = 0;

//                 while((damier->plateau[ligne + 1 + i][colonne - 1 - i] == PION_ROUGE || damier->plateau[ligne + 1 + i][colonne - 1 - i] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2 + i, colonne - 2 - i) && damier->plateau[ligne + 2 + i][colonne - 2 - i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne + 1 + i, colonne - 1 - i));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2 + i, colonne - 2 - i));

//                     i += 2;
//                 }
//             }
//         }

//         if(verifierCaseValide(ligne + 1, colonne + 1)) { // Deplacement a droite possible
//             if(damier->plateau[ligne + 1][colonne + 1] == CASE_VIDE) {
//                 pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne + 1, colonne + 1));
//             } else if((damier->plateau[ligne + 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
//                 int i = 0;

//                 while((damier->plateau[ligne + 1 + i][colonne + 1 + i] == PION_ROUGE || damier->plateau[ligne + 1 + i][colonne + 1 + i] == 2 * PION_ROUGE) && verifierCaseValide(ligne + 2 + i, colonne + 2 + i) && damier->plateau[ligne + 2 + i][colonne + 2 + i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne + 1, colonne + 1));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2, colonne + 2));

//                     i += 2;
//                 }
//             }
//         }


//         if(verifierCaseValide(ligne - 1, colonne + 1)) { // Rafle arriere a droite possible
//             if((damier->plateau[ligne - 1][colonne + 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { 
//                 int i = 0;

//                 while((damier->plateau[ligne - 1 - i][colonne + 1 + i] == PION_ROUGE || damier->plateau[ligne - 1 - i][colonne + 1 + i] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2 - i, colonne + 2 + i) && damier->plateau[ligne - 2 - i][colonne + 2 + i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne - 1 - i, colonne + 1 + i));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2 - i, colonne + 2 + i));

//                     i += 2;
//                 }
//             }
//         }

//         if(verifierCaseValide(ligne - 1, colonne - 1)) { // Rafle arriere a gauche possible
//             if((damier->plateau[ligne - 1][colonne - 1] == PION_ROUGE || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { 
//                 int i = 0;

//                 while((damier->plateau[ligne - 1 - i][colonne - 1 - i] == PION_ROUGE || damier->plateau[ligne - 1 - i][colonne - 1 - i] == 2 * PION_ROUGE) && verifierCaseValide(ligne - 2 - i, colonne - 2 - i) && damier->plateau[ligne - 2 - i][colonne - 2 - i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne - 1 - i, colonne - 1 - i));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2 - i, colonne - 2 - i));

//                     i += 2;
//                 }
//             }
//         }
//     } else if((damier->plateau[ligne][colonne] == PION_ROUGE) && (couleurPion == PION_ROUGE)) { // Selection des pions Rouges
//         if(verifierCaseValide(ligne - 1, colonne + 1)) { 
//             if(damier->plateau[ligne - 1][colonne + 1] == CASE_VIDE) { // Deplacement a droite possible
//                 pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne + 1));
//             } else if((damier->plateau[ligne - 1][colonne + 1] == PION_VERT || damier->plateau[ligne - 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne + 2) && damier->plateau[ligne - 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions verts a droite
//                 int i = 0;

//                 while((damier->plateau[ligne - 1 - i][colonne + 1 + i] == PION_VERT || damier->plateau[ligne - 1 - i][colonne + 1 + i] == 2 * PION_VERT) && verifierCaseValide(ligne - 2 - i, colonne + 2 + i) && damier->plateau[ligne - 2 - i][colonne + 2 + i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne - 1 - i, colonne + 1 + i));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2 - i, colonne + 2 + i));

//                     i += 2;
//                 }
//             }
//         }

//         if(verifierCaseValide(ligne - 1, colonne - 1)) { 
//             if(damier->plateau[ligne - 1][colonne - 1] == CASE_VIDE) { // Deplacement a gauche possible
//                 pionDeplacement = insererRafle(pionDeplacement, creerRafle(ligne, colonne));
//                 deplacement = insererRafle(deplacement, creerRafle(ligne - 1, colonne - 1));
//             } else if((damier->plateau[ligne - 1][colonne - 1] == PION_VERT || damier->plateau[ligne - 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne - 2, colonne - 2) && damier->plateau[ligne - 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions verts a gauche
//                 int i = 0;

//                 while((damier->plateau[ligne - 1 - i][colonne - 1 - i] == PION_VERT || damier->plateau[ligne - 1 - i][colonne - 1 - i] == 2 * PION_VERT) && verifierCaseValide(ligne - 2 - i, colonne - 2 - i) && damier->plateau[ligne - 2 - i][colonne - 2 - i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne - 1 - i, colonne - 1 - i));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - 2 - i, colonne - 2 - i));

//                     i += 2;
//                 }
//             }
//         }


//         if(verifierCaseValide(ligne + 1, colonne - 1)) { // Rafle arriere a gauche possible
//             if((damier->plateau[ligne + 1][colonne - 1] == PION_VERT || damier->plateau[ligne + 1][colonne - 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne - 2) && damier->plateau[ligne + 2][colonne - 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a gauche
//                 int i = 0;

//                 while((damier->plateau[ligne + 1 + i][colonne - 1 - i] == PION_VERT || damier->plateau[ligne + 1 + i][colonne - 1 - i] == 2 * PION_VERT) && verifierCaseValide(ligne + 2 + i, colonne - 2 - i) && damier->plateau[ligne + 2 + i][colonne - 2 - i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne + 1 + i, colonne - 1 - i));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2 + i, colonne - 2 - i));

//                     i += 2;
//                 }
//             }
//         }

//         if(verifierCaseValide(ligne + 1, colonne + 1)) { // Rafle arriere a droite possible
//             if((damier->plateau[ligne + 1][colonne + 1] == PION_VERT || damier->plateau[ligne + 1][colonne + 1] == 2 * PION_VERT) && verifierCaseValide(ligne + 2, colonne + 2) && damier->plateau[ligne + 2][colonne + 2] == CASE_VIDE) { // Selection des rafles des Pions rouges a droite
//                 int i = 0;

//                 while((damier->plateau[ligne + 1 + i][colonne + 1 + i] == PION_VERT || damier->plateau[ligne + 1 + i][colonne + 1 + i] == 2 * PION_VERT) && verifierCaseValide(ligne + 2 + i, colonne + 2 + i) && damier->plateau[ligne + 2 + i][colonne + 2 + i] == CASE_VIDE) {
//                     pionRafle = insererRafle(pionRafle, creerRafle(ligne, colonne));
//                     rafle = insererRafle(rafle, creerRafle(ligne + 1 + i, colonne + 1 + i));
//                     deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + 2 + i, colonne + 2 + i));

//                     i += 2;
//                 }
//             }
//         }
//     }

//     switch (choix) {
//         case 1: // Deplacement possible
//             return deplacement;
//         break;
//         case 2: // Rafle possible
//             return rafle;
//         break;
//         case 3: // Pions deplacables
//             return pionDeplacement;
//         break;
//         case 4: // Pion pouvant rafler
//             return pionRafle;
//         break;
//         case 5: // Deplacement possible des pions pouvant rafler
//             return deplacementRafle;
//         break;
//         default:
//             return NULL;
//         break;
//     }
// }


/**************/ 

for(int x = 1; x < DIMENSION_PLATEAU; x++) {
            if(verifierCaseValide(ligne - x, colonne + x)) { // Deplacement en haut a droite possible
                if(damier->plateau[ligne - x][colonne + x] == CASE_VIDE) {
                    dameDeplacementD = insererRafle(dameDeplacementD, creerRafle(ligne, colonne));
                    deplacementD = insererRafle(deplacementD, creerRafle(ligne - x, colonne + x));

                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne - x, colonne + x));
                } else if((damier->plateau[ligne - x][colonne + x] != couleurPion && damier->plateau[ligne - x][colonne + x] != CASE_VIDE) && verifierCaseValide(ligne - x - 1, colonne + x + 1) && damier->plateau[ligne - x - 1][colonne + x + 1] == CASE_VIDE) {
                    damier->plateau[ligne - x - 1][colonne + x + 1] = 2 * couleurPion;
                
                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 6);

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne - x - 1][colonne + x + 1] = CASE_VIDE;
                    }

                    dameRafleD = insererRafle(dameRafleD, creerRafle(ligne, colonne));
                    rafleD = insererRafle(rafleD, creerRafle(ligne - x, colonne + x));
                    deplacementRafleD = insererRafle(deplacementRafleD, creerRafle(ligne - x - 1, colonne + x + 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne - x, colonne + x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - x - 1, colonne + x + 1));

                    if(recursif != NULL) {
                        dameRafleD = insererRafle(dameRafleD, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 16));
                        rafleD = insererRafle(rafleD, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafleD = insererRafle(deplacementRafleD, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 21));

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 16));
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne + x + 1, couleurPion, 21));
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne - x - 1][colonne + x + 1] = CASE_VIDE;
                    }
                } else {
                    break;
                }
            }
        }

        for(int x = 1; x < DIMENSION_PLATEAU; x++) {
            if(verifierCaseValide(ligne - x, colonne - x)) { // Deplacement en haut a gauche possible
                if(damier->plateau[ligne - x][colonne - x] == CASE_VIDE) {
                    dameDeplacementG = insererRafle(dameDeplacementG, creerRafle(ligne, colonne));
                    deplacementG = insererRafle(deplacementG, creerRafle(ligne - x, colonne - x));
                
                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne - x, colonne - x));
                } else if((damier->plateau[ligne - x][colonne - x] != couleurPion && damier->plateau[ligne - x][colonne - x] != CASE_VIDE) && verifierCaseValide(ligne - x - 1, colonne - x - 1) && damier->plateau[ligne - x - 1][colonne - x - 1] == CASE_VIDE) {
                    damier->plateau[ligne - x - 1][colonne - x - 1] = 2 * couleurPion;
                    
                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 6);

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne - x - 1][colonne - x - 1] = CASE_VIDE;
                    }

                    dameRafleG = insererRafle(dameRafleG, creerRafle(ligne, colonne));
                    rafleG = insererRafle(rafleG, creerRafle(ligne - x, colonne - x));
                    deplacementRafleG = insererRafle(deplacementRafleG, creerRafle(ligne - x - 1, colonne - x - 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne - x, colonne - x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne - x - 1, colonne - x - 1));

                    if(recursif != NULL) {
                        dameRafleG = insererRafle(dameRafleG, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 16));
                        rafleG = insererRafle(rafleG, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 6));
                        deplacementRafleG = insererRafle(deplacementRafleG, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 21));

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 16));
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 6));
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne - x - 1, colonne - x - 1, couleurPion, 21));
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne - x - 1][colonne - x - 1] = CASE_VIDE;
                    }
                } else {
                    break;
                }
            }
        }
        
        
        for(int x = 1; x < DIMENSION_PLATEAU; x++) {
            if(verifierCaseValide(ligne + x, colonne - x)) { // Deplacement en bas a gauche possible
                if(damier->plateau[ligne + x][colonne - x] == CASE_VIDE) {
                    dameDeplacementAG = insererRafle(dameDeplacementAG, creerRafle(ligne, colonne));
                    deplacementAG = insererRafle(deplacementAG, creerRafle(ligne + x, colonne - x));
                
                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne + x, colonne - x));
                } else if((damier->plateau[ligne + x][colonne - x] != couleurPion && damier->plateau[ligne + x][colonne - x] != CASE_VIDE) && verifierCaseValide(ligne + x + 1, colonne - x - 1) && damier->plateau[ligne + x + 1][colonne - x - 1] == CASE_VIDE) {
                    damier->plateau[ligne + x + 1][colonne - x - 1] = 2 * couleurPion;
                
                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 6);

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne + x + 1][colonne - x - 1] = CASE_VIDE;
                    }

                    dameRafleAG = insererRafle(dameRafleAG, creerRafle(ligne, colonne));
                    rafleAG = insererRafle(rafleAG, creerRafle(ligne + x, colonne - x));
                    deplacementRafleAG = insererRafle(deplacementRafleAG, creerRafle(ligne + x + 1, colonne - x - 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne + x, colonne - x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + x + 1, colonne - x - 1));

                    if(recursif != NULL) {
                        dameRafleAG = insererRafle(dameRafleAG, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 16));
                        rafleAG = insererRafle(rafleAG, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 6));
                        deplacementRafleAG = insererRafle(deplacementRafleAG, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 21));

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 16));
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 6));
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne - x - 1, couleurPion, 21));
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne + x + 1][colonne - x - 1] = CASE_VIDE;
                    }
                } else {
                    break;
                }
            }
        }

        for(int x = 1; x < DIMENSION_PLATEAU; x++) {
            if(verifierCaseValide(ligne + x, colonne + x)) { // Deplacement en bas a droite possible
                if(damier->plateau[ligne + x][colonne + x] == CASE_VIDE) {
                    dameDeplacementAD = insererRafle(dameDeplacementAD, creerRafle(ligne, colonne));
                    deplacementAD = insererRafle(deplacementAD, creerRafle(ligne + x, colonne + x));
                
                    dameDeplacement = insererRafle(dameDeplacement, creerRafle(ligne, colonne));
                    deplacement = insererRafle(deplacement, creerRafle(ligne + x, colonne + x));
                } else if((damier->plateau[ligne + x][colonne + x] != couleurPion && damier->plateau[ligne + x][colonne + x] != CASE_VIDE) && verifierCaseValide(ligne + x + 1, colonne + x + 1) && damier->plateau[ligne + x + 1][colonne + x + 1] == CASE_VIDE) {
                    damier->plateau[ligne + x + 1][colonne + x + 1] = 2 * couleurPion;
                
                    Rafle *recursif = deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 6);

                    if(choix >= 16 && choix <= 20) {
                        damier->plateau[ligne + x + 1][colonne + x + 1] = CASE_VIDE;
                    }

                    dameRafleAD = insererRafle(dameRafleAD, creerRafle(ligne, colonne));
                    rafleAD = insererRafle(rafleAD, creerRafle(ligne + x, colonne + x));
                    deplacementRafleAD = insererRafle(deplacementRafleAD, creerRafle(ligne + x + 1, colonne + x + 1));

                    dameRafle = insererRafle(dameRafle, creerRafle(ligne, colonne));
                    rafle = insererRafle(rafle, creerRafle(ligne + x, colonne + x));
                    deplacementRafle = insererRafle(deplacementRafle, creerRafle(ligne + x + 1, colonne + x + 1));

                    if(recursif != NULL) {
                        dameRafleAD = insererRafle(dameRafleAD, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 16));
                        rafleAD = insererRafle(rafleAD, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafleAD = insererRafle(deplacementRafleAD, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 21));

                        dameRafle = insererRafle(dameRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 16));
                        rafle = insererRafle(rafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 6));
                        deplacementRafle = insererRafle(deplacementRafle, deplacementEtRaflePossiblesDame(damier, ligne + x + 1, colonne + x + 1, couleurPion, 21));
                    }

                    if(choix < 16 || choix > 20) {
                        damier->plateau[ligne + x + 1][colonne + x + 1] = CASE_VIDE;
                    }
                } else {
                    break;
                }
            }
        }



