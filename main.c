#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Structure pour représenter une catégorie
typedef struct
{
    int id;
    char nom[50];
} Categorie;

// Structure pour représenter un produit
typedef struct
{
    int id;
    char nom[50];
    float prix;
    int quantite;
    Categorie categorie;
} Produit;

// Fonction pour vérifier si une catégorie existe déjà par son ID
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

// Fonction pour vérifier si un produit existe déjà par son ID
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

// Fonction pour sauvegarder les catégories dans un fichier texte
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

// Fonction pour ajouter une catégorie
void ajouterCategorie(Categorie categories[], int *nbCategories, int id, char *nom)
{
    if (categorieExiste(categories, *nbCategories, id))
    {
        printf("Erreur : Une catégorie avec cet ID existe déjà.\n");
        return;
    }
    categories[*nbCategories].id = id;
    strcpy(categories[*nbCategories].nom, nom);
    (*nbCategories)++;
    sauvegarderCategories(categories, *nbCategories); // Sauvegarder dans le fichier
    printf("Catégorie ajoutée avec succès.\n");
}

// Fonction pour ajouter un produit
void ajouterProduit(Produit produits[], int *nbProduits, int id, char *nom, float prix, int quantite, Categorie categorie)
{
    if (produitExiste(produits, *nbProduits, id))
    {
        printf("Erreur : Un produit avec cet ID existe déjà.\n");
        return;
    }
    produits[*nbProduits].id = id;
    strcpy(produits[*nbProduits].nom, nom);
    produits[*nbProduits].prix = prix;
    produits[*nbProduits].quantite = quantite;
    produits[*nbProduits].categorie = categorie;
    (*nbProduits)++;
    sauvegarderProduits(produits, *nbProduits); // Sauvegarder dans le fichier
    printf("Produit ajouté avec succès.\n");
}

// Fonction pour afficher toutes les catégories
void afficherCategories(Categorie categories[], int nbCategories)
{
    printf("\nListe des catégories :\n");
    for (int i = 0; i < nbCategories; i++)
    {
        printf("ID: %d | Nom: %s\n", categories[i].id, categories[i].nom);
    }
    if (nbCategories == 0)
    {
        printf("Aucune catégorie trouvée.\n");
    }
}

// Fonction pour afficher tous les produits
void afficherProduits(Produit produits[], int nbProduits)
{
    printf("\nListe des produits :\n");
    for (int i = 0; i < nbProduits; i++)
    {
        printf("ID: %d | Nom: %s | Prix: %.2f | Quantité: %d | Catégorie: %s\n",
               produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
    }
    if (nbProduits == 0)
    {
        printf("Aucun produit trouvé.\n");
    }
}

// Fonction pour supprimer une catégorie
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
            printf("Catégorie supprimée avec succès.\n");
            break;
        }
    }
    if (!trouve)
    {
        printf("Erreur : Catégorie introuvable.\n");
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
            printf("Produit supprimé avec succès.\n");
            break;
        }
    }
    if (!trouve)
    {
        printf("Erreur : Produit introuvable.\n");
    }
}

// Fonction pour modifier une catégorie
void modifierCategorie(Categorie categories[], int nbCategories, int id)
{
    for (int i = 0; i < nbCategories; i++)
    {
        if (categories[i].id == id)
        {
            printf("Nouveau nom de la catégorie : ");
            char nom[50];
            scanf(" %49[^\n]", nom);
            strcpy(categories[i].nom, nom);
            sauvegarderCategories(categories, nbCategories); // Sauvegarder dans le fichier
            printf("Catégorie modifiée avec succès.\n");
            return;
        }
    }
    printf("Erreur : Catégorie introuvable.\n");
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

            printf("Nouvelle quantité : ");
            scanf("%d", &produits[i].quantite);

            afficherCategories(categories, nbCategories);
            printf("ID de la nouvelle catégorie : ");
            int idCategorie;
            scanf("%d", &idCategorie);

            for (int j = 0; j < nbCategories; j++)
            {
                if (categories[j].id == idCategorie)
                {
                    produits[i].categorie = categories[j];
                    sauvegarderProduits(produits, nbProduits); // Sauvegarder dans le fichier
                    printf("Produit modifié avec succès.\n");
                    return;
                }
            }

            printf("Erreur : Catégorie introuvable.\n");
            return;
        }
    }
    printf("Erreur : Produit introuvable.\n");
}
// Fonction pour charger les catégories depuis un fichier texte
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
        // Associer la catégorie au produit
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

    // Demander l'ID de la catégorie jusqu'à obtenir une entrée valide
    do {
        printf("Entrez l'ID de la catégorie pour filtrer les produits : ");
        int valid = scanf("%d", &idCategorie);
        if (valid != 1) {
            printf("Erreur : veuillez entrer un nombre entier valide.\n");
            while (getchar() != '\n'); // Vide le tampon d'entrée
        }
    } while (idCategorie <= 0); // Vérifie que l'ID soit un nombre positif

    // Vérifier si la catégorie existe
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
        printf("Erreur : Catégorie introuvable.\n");
        return;
    }

    printf("\nListe des produits dans la catégorie :\n");
    for (int i = 0; i < nbProduits; i++)
    {
        if (produits[i].categorie.id == idCategorie)
        {
            printf("ID: %d | Nom: %s | Prix: %.2f | Quantité: %d | Catégorie: %s\n",
                   produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
            produitsTrouves = 1;
        }
    }

    if (!produitsTrouves)
    {
        printf("Aucun produit trouvé dans cette catégorie.\n");
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
            printf("ID: %d | Nom: %s | Prix: %.2f | Quantité: %d | Catégorie: %s\n",
                   produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
            trouve = 1;
        }
    }
    if (!trouve)
    {
        printf("Aucun produit trouvé dans cette plage de prix.\n");
    }
}
// Fonction pour afficher le menu principal
void afficherMenu()
{
    printf("\n=== Menu ===\n");
    printf("1. Ajouter une catégorie\n");
    printf("2. Ajouter un produit\n");
    printf("3. Afficher les catégories\n");
    printf("4. Afficher les produits\n");
    printf("5. Supprimer une catégorie\n");
    printf("6. Supprimer un produit\n");
    printf("7. Modifier une catégorie\n");
    printf("8. Modifier un produit\n");
    printf("9. Filtrer les produits par catégorie\n");
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

    // Charger les données depuis les fichiers
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
            printf("ID de la catégorie : ");
            scanf("%d", &id);
            printf("Nom de la catégorie : ");
            scanf(" %49[^\n]", nom);
            ajouterCategorie(categories, &nbCategories, id, nom);
            break;
        case 2:
            if (nbCategories == 0)
            {
                printf("Erreur : Ajoutez une catégorie avant d'ajouter un produit.\n");
                break;
            }
            printf("ID du produit : ");
            scanf("%d", &id);
            printf("Nom du produit : ");
            scanf(" %49[^\n]", nom);
            printf("Prix : ");
            scanf("%f", &prix);
            printf("Quantité : ");
            scanf("%d", &quantite);
            afficherCategories(categories, nbCategories);
            printf("ID de la catégorie : ");
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
            printf("ID de la catégorie à supprimer : ");
            scanf("%d", &id);
            supprimerCategorie(categories, &nbCategories, id);
            break;
        case 6:
            afficherProduits(produits, nbProduits);
            printf("ID du produit à supprimer : ");
            scanf("%d", &id);
            supprimerProduit(produits, &nbProduits, id);
            break;
        case 7:
            afficherCategories(categories, nbCategories);
            printf("ID de la catégorie à modifier : ");
            scanf("%d", &id);
            modifierCategorie(categories, nbCategories, id);
            break;
        case 8:
            afficherProduits(produits, nbProduits);
            printf("ID du produit à modifier : ");
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
