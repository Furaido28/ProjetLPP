//  **********************************
//  Nom       :   Flipo       Makhloufi
//  Prénom    :   Ethan       Olivia
//  Classe    :   2BIA1
//  **********************************

//  Library public
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//  Library privé
#include "store.h"
#include "affichage.h"

// -------------
// Fonction main
// -------------
int main() {
    store *listeMagasins = NULL;
    char nomMagasin[100], nomProduit[80], nomCategorie[80], nomMarque[80], nomRayon[80];
    int quantiteProduit;
    float prixProduit;
    do {
        switch (afficherMenuPrincipal()) {
            case 1: {
                clearScreen();
                printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf(">>        \033[1;36mAjout d'un Nouveau Produit\033[0m        <<\n");
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

                printf("\033[1;32mNom du magasin\033[0m > ");
                scanf("%s", nomMagasin);

                // Rechercher ou créer le magasin
                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);

                if (magasin == NULL) {
                    magasin = creerMagasin(nomMagasin);
                    magasin->suivant = listeMagasins;
                    listeMagasins = magasin;
                }

                // Affichage du menu ajouter
                afficherMenuAjouter(nomProduit, nomCategorie, nomMarque, nomRayon, &quantiteProduit, &prixProduit);

                // Ajouter le produit au magasin
                ajouterProduit(magasin, nomProduit, nomCategorie, nomMarque, nomRayon, quantiteProduit, prixProduit);

                printf("\033[1;32mProduit '%s' ajout%c avec succ%cs au magasin '%s'.\033[0m\n", nomProduit, 130, 138, nomMagasin);

                printf("\nAppuyez sur Entr%ce pour revenir au menu principal...", 130);
                getchar(); getchar();
                break;
            }
            case 2: {
                char ancien_nom[80], ancienne_marque[80];
                clearScreen();
                printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf(">>         \033[1;36mModifier un Produit\033[0m         <<\n");
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");


                printf("\033[1;33mNom du magasin\033[0m > ");
                scanf("%99s", nomMagasin);
                printf("\033[1;33mNom du produit\033[0m > ");
                scanf("%99s", ancien_nom);
                printf("\033[1;33mMarque du produit\033[0m > ");
                scanf("%99s", ancienne_marque);

                switch (rechercherProduitMagasin(listeMagasins, nomMagasin, ancien_nom, ancienne_marque)) {
                    case 1:
                        traitement();
                        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                        printf(">>         \033[1;36mInformation du Produit\033[0m         <<\n");
                        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

                        // Affichage du menu ajouter
                        afficherMenuAjouter(nomProduit, nomCategorie, nomMarque, nomRayon, &quantiteProduit, &prixProduit);

                        store *magasin = rechercherMagasin(listeMagasins, nomMagasin);
                        // Modifier le produit
                        modifierProduit(magasin, ancien_nom, ancienne_marque, nomProduit, nomCategorie, nomMarque, nomRayon, quantiteProduit, prixProduit);
                        break;
                    default:
                        break;
                }
                break;
            }
            case 3: {
                clearScreen();
                printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                printf(">>         \033[1;36mSupprimer un Produit\033[0m         <<\n");
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

                printf("\n\033[1;33mNom du magasin\033[0m > ");
                scanf("%99s", nomMagasin);

                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);
                if (magasin == NULL) {
                    printf("\033[1;31mMagasin introuvable.\033[0m\n");
                    break;
                }

                // Affichage du menu de suppression
                afficherMenuSupprimer(nomProduit, nomMarque);
                // Appel la fonction de suppression de produit
                supprimerProduit(magasin, nomProduit, nomMarque);
                break;
            }
            case 4:
                // Affichage du menu de rechercher
                afficherMenuRechercher(nomProduit, nomMarque);
                // Appel la fonction de recherche d'un produit
                rechercherProduit(listeMagasins, nomProduit, nomMarque);
                break;
            case 5:
                switch (afficherMenuAffichage()) {
                    case 1:
                        afficherMagasin(listeMagasins);
                        break;
                    case 2:
                        afficherMagasinsEtProduits(listeMagasins);
                        break;
                    default:
                        break;
                }
                break;
            case 6:
                archiverListe(listeMagasins);
                break;
            case 7:
                importerListe(&listeMagasins);
                break;
            default: {
                switch (confirmer()) {
                    case 'Y':
                        traitement();
                        printf("\033[1;35mFermeture du programme...\033[0m\n");
                        Sleep(800);
                        return 0;
                    case 'N':
                        break;
                }
            }
        }
    }while(1);
    return 0;
}