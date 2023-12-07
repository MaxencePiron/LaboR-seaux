enum TypeRequete {
    Question = 1 ,
    Achat = 2 ,
    Livraison= 3 ,
    OK = 4,
    Fail = 5
};

struct RequeteMP
{
    enum TypeRequete Type ;
    int Numero ; // Contient le numéro de la requete
    int NumeroFacture ;
    time_t Date ;
    int Reference ; // la référence de la voiture
    int Quantite ; 
    int Prix ;
    char Constructeur[30] ;
    char Modele[30] ;
    int Puissance;
    char NomClient[80] ;
    char Message[30];
};

#include <stdio.h>

void AfficheRequeteHV(FILE *fp, struct RequeteMP R)
{
    fprintf(fp,">TypeRequete %d \n", R.Type ) ;
    fprintf(fp," Reference %d \n", R.Numero ) ;
    fprintf(fp," NumeroFacture %d \n", R.NumeroFacture ) ;
    fprintf(fp," Date %ld \n", R.Date ) ;
    fprintf(fp," Reference %d \n", R.Reference ) ;
    fprintf(fp," Places %d \n", R.Quantite ) ;
    fprintf(fp," Prix %d \n", R.Prix ) ;
    fprintf(fp,"Constructeur %s \n", R.Constructeur ) ;
    fprintf(fp,"Modele %s \n", R.Modele ) ;
    fprintf(fp,"Puissance %d \n",R.Puissance);
    fprintf(fp," Client %s \n\n", R.NomClient ) ;
    return ;
}

void InitRequeteMP(struct RequeteMP* R)
{
    R->Type = 4;
    R->NumeroFacture = 0;
    R->Date = 0;
    R->Reference = 0;
    R->Quantite = 0;
    R->Prix = 0;
    R->Puissance = 0;
    return;
}