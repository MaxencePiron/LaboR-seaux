/******************************************
  Herman Vanstapel
  Lecture
  2015
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

void DelNewLine(char *Chaine)
{
 Chaine[strlen(Chaine)-1] = 0 ;
}

char ReadChar()
{
 char Tampon[80] ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 return Tampon[0] ;
} 


void AfficheRecord(struct Record *UnRecord)
{
printf("%d\n",UnRecord->Numero ) ;
 printf("%d\n",UnRecord->Valeur ) ;
 printf("%s\n",UnRecord->Memo) ;
 printf("-----------------------\n") ;
}

void SaiSieRecord(struct Record *UnRecord )
{
 char Tampon[80] ;
 printf("Saisie numero :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Numero = atoi(Tampon) ;
 printf("Saisie valeur :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Valeur = atoi(Tampon) ;
 printf("Saisie Tampon :") ;
 fgets(UnRecord->Memo,sizeof UnRecord->Memo,stdin ) ;
 DelNewLine(UnRecord->Memo) ;
 AfficheRecord(UnRecord) ;
 return ;
}

int Lecture(const char*NomFichier , struct Record *UnRecord )
{
 
/* Pour Lecture il n'est pas nécessaire de passer un pointeur */
/* L'objetif est de vous rappeler la mécanique des record passé par pointeur */
/* On notera que UnRecord contiendra toujours le dernier record lu */
/* La fonction retourne 1 si il y'a au moins un record dans le fichier */
 FILE *sortie ;
 int AuMoinsUn ;
 int nbr ;
 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;
 nbr = fread(UnRecord,sizeof(struct Record),1,sortie) ;
  while ( !feof(sortie) ) /* On peut remplace !feof(sortie ) par nbr */
 {
  int nbr ;
  AuMoinsUn = 1 ;
  fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
  AfficheRecord(UnRecord) ;
  nbr = fread(UnRecord,sizeof(struct Record),1,sortie) ;
 }
 fclose(sortie) ;
 return(AuMoinsUn ) ;
}

main()
{
 struct Record UnRecord ;
 int AuMoinsUn ;

 
 char Tampon[80] ;
 char NomFichier[40] ;
 int  Numero ;
 int  nbr ;

 printf("Le nom de fichier à Lire :)") ;
 fgets(NomFichier,sizeof NomFichier,stdin) ;
 DelNewLine(NomFichier) ;

 AuMoinsUn = Lecture( NomFichier , &UnRecord ) ;
 if (AuMoinsUn)
 	AfficheRecord(&UnRecord) ;
}
