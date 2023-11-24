/*---------------------------------------------------------------
   Vanstapel Herman
   ex02\cli.c

 Le client dit bonjour en utilisant un structure  et
 le serveur fait de même
------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "RequeteMP.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
 int rc ;
 int Desc ;
 int tm ; 
 
 u_long  IpSocket , IpServer;
 u_short PortSocket, PortServer ; 
 
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */
 struct RequeteMP UneRequete ;

 memset(&sthis,0,sizeof(struct sockaddr_in)) ;
 memset(&sos,0,sizeof(struct sockaddr_in)) ; 
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 
 if (argc!=5)
  
{
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 
 /* Récupération IP & port   */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 
 IpServer = inet_addr(argv[3]) ;
 PortServer = atoi(argv[4]);
 
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);
 
 if ( Desc == -1 )
    die("CreateSockets:") ; 
 else
    fprintf(stderr,"CreateSockets %d\n",Desc) ;
 
  sos.sin_family = AF_INET ;
  sos.sin_addr.s_addr= IpServer ;
  sos.sin_port = htons(PortServer) ;

  char Tampon[80];
  printf("Saisie reference vehicule : ");
  fgets(Tampon,sizeof(Tampon),stdin);
   UneRequete.Reference = atoi(Tampon);

   UneRequete.Numero = 1;
   UneRequete.NumeroFacture = 0;
   UneRequete.Quantite = 0;
 
 UneRequete.Type = Question ; 
 
 rc = SendDatagram(Desc,&UneRequete,sizeof(struct RequeteMP) ,&sos ) ;

 if ( rc == -1 )
    die("SendDatagram") ;
 else
   printf("bytes écrits %d\n",rc ) ;
 
 memset(&UneRequete,0,sizeof(struct RequeteMP)) ;
 tm = sizeof(struct RequeteMP) ;
 
  rc = ReceiveDatagram( Desc, &UneRequete,tm, &sor ) ;
 if ( rc == -1 )
    die("ReceiveDatagram") ;
 else
 {
   printf("bytes lus:%d\nConstructeur, modele, puissance :%s %s %d\n",rc,UneRequete.Constructeur,UneRequete.Modele,UneRequete.Puissance ) ;
   AfficheRequeteHV(stderr,UneRequete);
 }
 
 close(Desc) ;
}
