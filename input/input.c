#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void purge()
{
  while (getchar() != '\n');
}

// scanf("%c%c",&ch,&chb) ;

main()
{
 char  tampon[80] ;
 int val ;
 char ch,chb ;
 while(1)
 {
  printf("Saisie chaine") ;
  scanf("%s",tampon) ;
  purge() ;
  printf("Saisie Caractere") ;
  scanf("%c",&ch) ;
  purge() ;
  printf("Saisie entier:") ;
  scanf("%d",&val) ;
  purge() ;
  printf("Le résultat est %s ,%c , %d \n", tampon,ch,val) ;
 }
}
