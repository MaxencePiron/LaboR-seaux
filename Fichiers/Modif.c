/******************************************
  Herman Vanstapel
  2007
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

int Remplace (const char *NomFichier,int Numero ,int Valeur) 
{
 struct Record UnRecord ;
 FILE *Fichier ;
 int  nbr,nbr2,pos ;
 int Trouve ;
Fichier = fopen(NomFichier,"r+") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( Fichier == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;
Trouve = 0 ;
 nbr = fseek(Fichier,0,SEEK_SET) ;
 /* fseek ne retourne pas la nouvelle position mais ftell */
 pos = ftell(Fichier) ;
 fprintf(stderr,"Nbr doit être début fichier %d\n",nbr) ;
 nbr2 = fread(&UnRecord,sizeof(struct Record),1,Fichier) ;
 while ( !feof(Fichier) && (!Trouve) )
 {
   if (UnRecord.Numero == Numero )
     {
      Trouve = 1 ;
      /* On recule pour modifier l'enregistrement */
      nbr = fseek(Fichier,-sizeof(struct Record),SEEK_CUR) ;
      pos = ftell(Fichier) ;
      printf("Nbr est la position du record à modifier %d\n",pos) ;
      UnRecord.Valeur = Valeur ;
      nbr2 = fwrite(&UnRecord,sizeof(struct Record),1,Fichier) ;  
      break ;
     }
  nbr2 = fread(&UnRecord,sizeof(struct Record),1,Fichier) ;
  pos = ftell(Fichier) ;
 fprintf(stderr, "Position courante %d\n",nbr) ;
 }
 fclose(Fichier) ;
 if (Trouve)
    return (pos ) ;
 else
    return 0 ;    
}

main()
{
 struct Record UnRecord ;
 char NomFichier[80] ;
 char Tampon[80] ;
 int  Numero ;
 int Trouve ;
 
 int Valeur ;

 printf("Le nom de fichier Ã  Lire :)") ;
 fgets(NomFichier,sizeof NomFichier,stdin) ;
 DelNewLine(NomFichier) ;
 
 printf("Saisie numero :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 Numero = atoi(Tampon) ;
 /* pour montrer les possibilités de l accés direct on commence par la fin */

 printf("Saisie valeur :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 Valeur = atoi(Tampon) ;

 Trouve = Remplace (NomFichier,Numero ,Valeur) ;
  
 
}
