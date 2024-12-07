#ifndef STORE_H
  #define STORE_H
    // Library public
    #include <windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

    // Library privé
    #include "affichage.h"

  // --------------------------
  // Déclaration des structures
  // --------------------------

  typedef struct product {
      char nom_produit[80], nom_categorie[80], nom_marque[80], nom_rayon[80];
      int quantite;
      float prix;
      struct product *suivant;
  } product;

  typedef struct store {
      char nom_magasin[100];
      product *produits; // Pointeur vers une liste de produits
      struct store *suivant;
  } store;

  // --------------------------
  // Prototype des fonctions
  // --------------------------
  store* creerMagasin(char*);
  store* rechercherMagasin(store*, char*);
  void ajouterProduit(store*, char*, char*, char*, char*, int, float);
  void modifierProduit(store*, char*, char*, char*, char*, char*, char*, int, float);
  void supprimerProduit(store*, char*, char*);
  void rechercherProduit(store*, char[], char[]);
  void afficherMagasinsEtProduits(store*);
  void archiverListe(store *listeMagasins);
  void importerListe(store **listeMagasins);
#endif // STORE_H
