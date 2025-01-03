#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Structure pour repr�senter une cat�gorie
typedef struct
{
    int id;
    char nom[50];
} Categorie;

// Structure pour repr�senter un produit
typedef struct
{
    int id;
    char nom[50];
    float prix;
    int quantite;
    Categorie categorie;
} Produit;

// Fonction pour v�rifier si une cat�gorie existe d�j� par son ID
int categorieExiste(Categorie categories[], int nbCategories, int id)
{
    for (int i = 0; i < nbCategories; i++)
    {
        if (categories[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

// Fonction pour v�rifier si un produit existe d�j� par son ID
int produitExiste(Produit produits[], int nbProduits, int id)
{
    for (int i = 0; i < nbProduits; i++)
    {
        if (produits[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

// Fonction pour sauvegarder les cat�gories dans un fichier texte
void sauvegarderCategories(Categorie categories[], int nbCategories)
{
    FILE *fichier = fopen("categories.txt", "w");
    if (fichier == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier categories.txt\n");
        return;
    }
    for (int i = 0; i < nbCategories; i++)
    {
        fprintf(fichier, "%d;%s\n", categories[i].id, categories[i].nom);
    }
    fclose(fichier);
}

// Fonction pour sauvegarder les produits dans un fichier texte
void sauvegarderProduits(Produit produits[], int nbProduits)
{
    FILE *fichier = fopen("produits.txt", "w");
    if (fichier == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier produits.txt\n");
        return;
    }
    for (int i = 0; i < nbProduits; i++)
    {
        fprintf(fichier, "%d;%s;%.2f;%d;%d;%s\n",
                produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite,
                produits[i].categorie.id, produits[i].categorie.nom);
    }
    fclose(fichier);
}

// Fonction pour ajouter une cat�gorie
void ajouterCategorie(Categorie categories[], int *nbCategories, int id, char *nom)
{
    if (categorieExiste(categories, *nbCategories, id))
    {
        printf("Erreur : Une cat�gorie avec cet ID existe d�j�.\n");
        return;
    }
    categories[*nbCategories].id = id;
    strcpy(categories[*nbCategories].nom, nom);
    (*nbCategories)++;
    sauvegarderCategories(categories, *nbCategories); // Sauvegarder dans le fichier
    printf("Cat�gorie ajout�e avec succ�s.\n");
}

// Fonction pour ajouter un produit
void ajouterProduit(Produit produits[], int *nbProduits, int id, char *nom, float prix, int quantite, Categorie categorie)
{
    if (produitExiste(produits, *nbProduits, id))
    {
        printf("Erreur : Un produit avec cet ID existe d�j�.\n");
        return;
    }
    produits[*nbProduits].id = id;
    strcpy(produits[*nbProduits].nom, nom);
    produits[*nbProduits].prix = prix;
    produits[*nbProduits].quantite = quantite;
    produits[*nbProduits].categorie = categorie;
    (*nbProduits)++;
    sauvegarderProduits(produits, *nbProduits); // Sauvegarder dans le fichier
    printf("Produit ajout� avec succ�s.\n");
}

// Fonction pour afficher toutes les cat�gories
void afficherCategories(Categorie categories[], int nbCategories)
{
    printf("\nListe des cat�gories :\n");
    for (int i = 0; i < nbCategories; i++)
    {
        printf("ID: %d | Nom: %s\n", categories[i].id, categories[i].nom);
    }
    if (nbCategories == 0)
    {
        printf("Aucune cat�gorie trouv�e.\n");
    }
}

// Fonction pour afficher tous les produits
void afficherProduits(Produit produits[], int nbProduits)
{
    printf("\nListe des produits :\n");
    for (int i = 0; i < nbProduits; i++)
    {
        printf("ID: %d | Nom: %s | Prix: %.2f | Quantit�: %d | Cat�gorie: %s\n",
               produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
    }
    if (nbProduits == 0)
    {
        printf("Aucun produit trouv�.\n");
    }
}

// Fonction pour supprimer une cat�gorie
void supprimerCategorie(Categorie categories[], int *nbCategories, int id)
{
    int trouve = 0;
    for (int i = 0; i < *nbCategories; i++)
    {
        if (categories[i].id == id)
        {
            trouve = 1;
            for (int j = i; j < *nbCategories - 1; j++)
            {
                categories[j] = categories[j + 1];
            }
            (*nbCategories)--;
            sauvegarderCategories(categories, *nbCategories); // Sauvegarder dans le fichier
            printf("Cat�gorie supprim�e avec succ�s.\n");
            break;
        }
    }
    if (!trouve)
    {
        printf("Erreur : Cat�gorie introuvable.\n");
    }
}

// Fonction pour supprimer un produit
void supprimerProduit(Produit produits[], int *nbProduits, int id)
{
    int trouve = 0;
    for (int i = 0; i < *nbProduits; i++)
    {
        if (produits[i].id == id)
        {
            trouve = 1;
            for (int j = i; j < *nbProduits - 1; j++)
            {
                produits[j] = produits[j + 1];
            }
            (*nbProduits)--;
            sauvegarderProduits(produits, *nbProduits); // Sauvegarder dans le fichier
            printf("Produit supprim� avec succ�s.\n");
            break;
        }
    }
    if (!trouve)
    {
        printf("Erreur : Produit introuvable.\n");
    }
}

// Fonction pour modifier une cat�gorie
void modifierCategorie(Categorie categories[], int nbCategories, int id)
{
    for (int i = 0; i < nbCategories; i++)
    {
        if (categories[i].id == id)
        {
            printf("Nouveau nom de la cat�gorie : ");
            char nom[50];
            scanf(" %49[^\n]", nom);
            strcpy(categories[i].nom, nom);
            sauvegarderCategories(categories, nbCategories); // Sauvegarder dans le fichier
            printf("Cat�gorie modifi�e avec succ�s.\n");
            return;
        }
    }
    printf("Erreur : Cat�gorie introuvable.\n");
}

// Fonction pour modifier un produit
void modifierProduit(Produit produits[], int nbProduits, Categorie categories[], int nbCategories, int id)
{
    for (int i = 0; i < nbProduits; i++)
    {
        if (produits[i].id == id)
        {
            printf("Nouveau nom du produit : ");
            char nom[50];
            scanf(" %49[^\n]", nom);
            strcpy(produits[i].nom, nom);

            printf("Nouveau prix : ");
            scanf("%f", &produits[i].prix);

            printf("Nouvelle quantit� : ");
            scanf("%d", &produits[i].quantite);

            afficherCategories(categories, nbCategories);
            printf("ID de la nouvelle cat�gorie : ");
            int idCategorie;
            scanf("%d", &idCategorie);

            for (int j = 0; j < nbCategories; j++)
            {
                if (categories[j].id == idCategorie)
                {
                    produits[i].categorie = categories[j];
                    sauvegarderProduits(produits, nbProduits); // Sauvegarder dans le fichier
                    printf("Produit modifi� avec succ�s.\n");
                    return;
                }
            }

            printf("Erreur : Cat�gorie introuvable.\n");
            return;
        }
    }
    printf("Erreur : Produit introuvable.\n");
}
// Fonction pour charger les cat�gories depuis un fichier texte
int chargerCategories(Categorie categories[], int *nbCategories)
{
    FILE *fichier = fopen("categories.txt", "r");
    if (fichier == NULL)
    {
        printf("Avertissement : Impossible d'ouvrir le fichier categories.txt.\n");
        return 0;
    }
    *nbCategories = 0;
    while (fscanf(fichier, "%d;%49[^\n]\n", &categories[*nbCategories].id, categories[*nbCategories].nom) == 2)
    {
        (*nbCategories)++;
    }
    fclose(fichier);
    return 1;
}

// Fonction pour charger les produits depuis un fichier texte
int chargerProduits(Produit produits[], int *nbProduits, Categorie categories[], int nbCategories)
{
    FILE *fichier = fopen("produits.txt", "r");
    if (fichier == NULL)
    {
        printf("Avertissement : Impossible d'ouvrir le fichier produits.txt.\n");
        return 0;
    }
    *nbProduits = 0;
    int idCategorie;
    char nomCategorie[50];
    while (fscanf(fichier, "%d;%49[^;];%f;%d;%d;%49[^\n]\n",
                  &produits[*nbProduits].id,
                  produits[*nbProduits].nom,
                  &produits[*nbProduits].prix,
                  &produits[*nbProduits].quantite,
                  &idCategorie,
                  nomCategorie) == 6)
    {
        // Associer la cat�gorie au produit
        for (int i = 0; i < nbCategories; i++)
        {
            if (categories[i].id == idCategorie)
            {
                produits[*nbProduits].categorie = categories[i];
                break;
            }
        }
        (*nbProduits)++;
    }
    fclose(fichier);
    return 1;
}
void afficherProduitsParCategorie(Produit produits[], int nbProduits, Categorie categories[], int nbCategories)
{
    int idCategorie;
    int produitsTrouves = 0;

    // Demander l'ID de la cat�gorie jusqu'� obtenir une entr�e valide
    do {
        printf("Entrez l'ID de la cat�gorie pour filtrer les produits : ");
        int valid = scanf("%d", &idCategorie);
        if (valid != 1) {
            printf("Erreur : veuillez entrer un nombre entier valide.\n");
            while (getchar() != '\n'); // Vide le tampon d'entr�e
        }
    } while (idCategorie <= 0); // V�rifie que l'ID soit un nombre positif

    // V�rifier si la cat�gorie existe
    int categorieTrouvee = 0;
    for (int i = 0; i < nbCategories; i++)
    {
        if (categories[i].id == idCategorie)
        {
            categorieTrouvee = 1;
            break;
        }
    }

    if (!categorieTrouvee)
    {
        printf("Erreur : Cat�gorie introuvable.\n");
        return;
    }

    printf("\nListe des produits dans la cat�gorie :\n");
    for (int i = 0; i < nbProduits; i++)
    {
        if (produits[i].categorie.id == idCategorie)
        {
            printf("ID: %d | Nom: %s | Prix: %.2f | Quantit�: %d | Cat�gorie: %s\n",
                   produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
            produitsTrouves = 1;
        }
    }

    if (!produitsTrouves)
    {
        printf("Aucun produit trouv� dans cette cat�gorie.\n");
    }
}



// Fonction pour afficher les produits dans une plage de prix
void afficherProduitsParPrix(Produit produits[], int nbProduits)
{
    float prixMin, prixMax;
    printf("Entrez le prix minimum : ");
    scanf("%f", &prixMin);
    printf("Entrez le prix maximum : ");
    scanf("%f", &prixMax);

    printf("\nProduits dans la plage de prix %.2f - %.2f :\n", prixMin, prixMax);
    int trouve = 0;
    for (int i = 0; i < nbProduits; i++)
    {
        if (produits[i].prix >= prixMin && produits[i].prix <= prixMax)
        {
            printf("ID: %d | Nom: %s | Prix: %.2f | Quantit�: %d | Cat�gorie: %s\n",
                   produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
            trouve = 1;
        }
    }
    if (!trouve)
    {
        printf("Aucun produit trouv� dans cette plage de prix.\n");
    }
}
// Fonction pour afficher le menu principal
void afficherMenu()
{
    printf("\n=== Menu ===\n");
    printf("1. Ajouter une cat�gorie\n");
    printf("2. Ajouter un produit\n");
    printf("3. Afficher les cat�gories\n");
    printf("4. Afficher les produits\n");
    printf("5. Supprimer une cat�gorie\n");
    printf("6. Supprimer un produit\n");
    printf("7. Modifier une cat�gorie\n");
    printf("8. Modifier un produit\n");
    printf("9. Filtrer les produits par cat�gorie\n");
    printf("10. Filtrer les produits par prix\n");
    printf("11. Quitter\n");
    printf("Choix : ");
}

int main()
{
    setlocale(LC_ALL, ""); // Configurer l'encodage pour UTF-8

    Produit produits[100];
    Categorie categories[50];
    int nbProduits = 0, nbCategories = 0;

    // Charger les donn�es depuis les fichiers
    chargerCategories(categories, &nbCategories);
    chargerProduits(produits, &nbProduits, categories, nbCategories);

    while (1)
    {
        afficherMenu();
        int choix;
        scanf("%d", &choix);

        if (choix == 11) break;

        int id;
        char nom[50];
        float prix;
        int quantite, idCategorie;
        switch (choix)
        {
        case 1:
            printf("ID de la cat�gorie : ");
            scanf("%d", &id);
            printf("Nom de la cat�gorie : ");
            scanf(" %49[^\n]", nom);
            ajouterCategorie(categories, &nbCategories, id, nom);
            break;
        case 2:
            if (nbCategories == 0)
            {
                printf("Erreur : Ajoutez une cat�gorie avant d'ajouter un produit.\n");
                break;
            }
            printf("ID du produit : ");
            scanf("%d", &id);
            printf("Nom du produit : ");
            scanf(" %49[^\n]", nom);
            printf("Prix : ");
            scanf("%f", &prix);
            printf("Quantit� : ");
            scanf("%d", &quantite);
            afficherCategories(categories, nbCategories);
            printf("ID de la cat�gorie : ");
            scanf("%d", &idCategorie);

            for (int i = 0; i < nbCategories; i++)
            {
                if (categories[i].id == idCategorie)
                {
                    ajouterProduit(produits, &nbProduits, id, nom, prix, quantite, categories[i]);
                    break;
                }
            }
            break;
        case 3:
            afficherCategories(categories, nbCategories);
            break;
        case 4:
            afficherProduits(produits, nbProduits);
            break;
        case 5:
            afficherCategories(categories, nbCategories);
            printf("ID de la cat�gorie � supprimer : ");
            scanf("%d", &id);
            supprimerCategorie(categories, &nbCategories, id);
            break;
        case 6:
            afficherProduits(produits, nbProduits);
            printf("ID du produit � supprimer : ");
            scanf("%d", &id);
            supprimerProduit(produits, &nbProduits, id);
            break;
        case 7:
            afficherCategories(categories, nbCategories);
            printf("ID de la cat�gorie � modifier : ");
            scanf("%d", &id);
            modifierCategorie(categories, nbCategories, id);
            break;
        case 8:
            afficherProduits(produits, nbProduits);
            printf("ID du produit � modifier : ");
            scanf("%d", &id);
            modifierProduit(produits, nbProduits, categories, nbCategories, id);
            break;
        case 9:
            afficherProduitsParCategorie(produits, nbProduits, categories, nbCategories);
            break;
        case 10:
            afficherProduitsParPrix(produits, nbProduits);
            break;
        default:
            printf("Erreur : Choix invalide.\n");
        }
    }

    return 0;
}
