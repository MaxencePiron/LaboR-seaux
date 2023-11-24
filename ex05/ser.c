/*--------------------------------------
  Herman Vanstapel 
  ex05\ser.c 
  Un serveur multiport multiclients
----------------------------------------*/

#include <stdio.h>
#include <string.h>
/* include pour le select */
#include <sys/types.h>
#include <sys/time.h>

#include "../udplib/udplib.h"
#include "structure.h"


void die(char *s)
{
    perror(s);
    exit(1);
}

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

void TraitementRequete(int Desc )
{
  struct sockaddr_in sor ; /* r = remote */
  
  int tm ;
 struct Requete UneRequete ;
 char Tampon[40] ;
 int Ip, Port ;
 int rc ;
 
 printf("Traitement requete sur %d \n",Desc ) ;
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 tm = sizeof(struct Requete) ;
  rc = ReceiveDatagram( Desc,&UneRequete ,tm, &sor ) ;
  if ( rc == -1 )
    perror("ReceiveDatagram") ;
  else
     fprintf(stderr,"bytes:%d:%s:type %d\n",rc,UneRequete.Message,UneRequete.Type ) ;
  
  printf("Received packet from %s:%d\n", inet_ntoa(sor.sin_addr), ntohs(sor.sin_port));
  /* reponse avec sor qui contient toujours l'adresse du dernier client */
 
  UneRequete.Type = Reponse ; 
  strcat(UneRequete.Message," Client") ;
  rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
  if ( rc == -1 )
    perror("SendDatagram:") ;
  else
    fprintf(stderr,"bytes:%d\n",rc ) ;
}


int main(int argc,char *argv[])
{
 int rc ;
 int Desc1, Desc2 ;
 char car ;
 
 struct sockaddr_in sthis1 ; /* this ce programme */
 struct sockaddr_in sthis2 ; /* this ce programme */
 fd_set readfs ;
 struct timeval tv ;
 u_long  IpSocket ;
 u_short PortSocket ;

 memset(&sthis1,0,sizeof(struct sockaddr_in)) ;
 memset(&sthis2,0,sizeof(struct sockaddr_in)) ; 
   
 printf("Ceci est le serveur\n") ;
 if ( argc!=5)
 {
  printf("ser ser port ser port \n") ;
  exit(1) ;
 }
 
 /* Récupération IP & port   */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc1=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis1);
 if ( Desc1 == -1 )
    die("CreateSockets") ;
 else
    printf(" CreateSockets 1 : %d \n",Desc1) ;
 
 IpSocket   = inet_addr(argv[3]);
 PortSocket = atoi(argv[4]);
 Desc2 = creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis2);
 if ( Desc2 == -1 )
    perror("CreateSockets") ;
 else
    printf(" CreateSockets 2 : %d \n",Desc2) ;
 
 while(1) 
 {
   
   FD_ZERO(&readfs) ;
   FD_SET(0,     &readfs); /* on teste le clavier */
   FD_SET(Desc1, &readfs);
   FD_SET(Desc2, &readfs);
   
   tv.tv_sec = 30 ; /* 30 secondes de timeout */
   tv.tv_usec = 100000 ; /* temps en micro secondes */
    
   // FD_SETSIZE Taille Maximum du set , Conseil de Doms Etienne */
   if((rc = select( FD_SETSIZE, &readfs, NULL, NULL, &tv)) < 0)
      die("select()");
    else
    if ( rc == 0 )
        printf ("Timeout !!!!!!! \n" ) ;
    else
    if(FD_ISSET( 0, &readfs))
     {
       car =  ReadChar() ;  /* fonction bibliothèque */
       printf("La touche pressee est %c \n", car  ) ;
       if (( car == 'q') || ( car == 'Q'))
	   exit(0) ;
     }
    else
    if(FD_ISSET(Desc1, &readfs))
    {
      TraitementRequete(Desc1 ) ;      
    }
    else
    if(FD_ISSET(Desc2, &readfs))
    {
      TraitementRequete(Desc2 ) ;      
    }
 }
}
