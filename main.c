//  **********************************
//  Nom     :   Flipo       Makhloufi
//  Prénom  :   Ethan       Olivia
//  Classe  :   2BIA1
//  **********************************

//  Library public
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//  Library privé
#include "store.h"
#include "affichage.h"

// -------------
// Fonction main
// -------------
int main() {
    store *listeMagasins = NULL;
    char nomMagasin[100], nomProduit[80], nomCategorie[80], nomMarque[80], nomRayon[80], confirmation;
    int quantiteProduit, input;
    float prixProduit;

    do {
        input = afficherMenuPrincipal();

        switch (input) {
            case 1: {
                printf("============================================\n");
                printf("        \033[1;36m*** Ajouter un Produit ***\033[0m\n");
                printf("============================================\n\n");

                printf("\n\033[1;33mNom du magasin\033[0m > ");
                scanf("%99s", nomMagasin);

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
                break;
            }
            case 2: {
                printf("============================================\n");
                printf("        \033[1;36m*** Supprimer un Produit ***\033[0m\n");
                printf("============================================\n\n");

                printf("\n\033[1;33mNom du magasin\033[0m > ");
                scanf("%99s", nomMagasin);

                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);
                if (magasin == NULL) {
                    printf("\033[1;31mMagasin introuvable.\033[0m\n");
                    break;
                }

                // Affichage du menu supprimer
                afficherMenuSupprimer(nomProduit, nomMarque);
                // Appel la fonction de suppression de produit
                supprimerProduit(magasin, nomProduit, nomMarque);
                break;
            }
            case 3:
                // Affichage du menu rechercher
                afficherMenuRechercher(nomProduit, nomMagasin);
                // Appel la fonction de recherche d'un produit
                rechercherProduit(listeMagasins, nomProduit, nomProduit);
                break;
            case 4:
                afficherMagasinsEtProduits(listeMagasins);
                break;
            case 5:
                archiverListe(listeMagasins);
                break;
            case 6:
                importerListe(&listeMagasins);
                break;
            case 0: {
                confirmation = confirmer();
                switch (confirmation) {
                    case 'Y':
                        break;
                    case 'N':
                        input = -1;
                        Sleep(550);
                }
            }
        }
    } while (input != 0);

    printf("\033[1;35mFermeture du programme...\033[0m\n");
    Sleep(1000);
    return 0;
}
