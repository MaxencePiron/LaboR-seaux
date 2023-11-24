/*---------------------------------------------------------------
   Vanstapel Herman
   ex01\cli.c

 ex01 Le client dit bonjour et
      le serveur fait de même
------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[])
{
 int rc ;
 int Desc ;
 char *message ;
 char reponse[100 ] ; 
 int tm ; 
 u_long  IpSocket , IpServer;
 u_short PortSocket, PortServer ; 
 
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */

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
 message = "Bonjour " ;
 
 /*******************************************************/                           
 
  sos.sin_family = AF_INET ;
  sos.sin_addr.s_addr= IpServer ;
  sos.sin_port = htons(PortServer) ;
 
  /**********************************************************/

 rc = SendDatagram(Desc,message,strlen(message)+1 ,&sos ) ;

 if ( rc == -1 )
    die("SendDatagram") ;
 else
   fprintf(stderr,"Envoi de %d bytes\n",rc ) ;
 
  memset(reponse,0,sizeof(reponse)) ;
 tm = sizeof(reponse) ;
 rc = ReceiveDatagram( Desc, reponse,tm, &sor ) ;
 if ( rc == -1 )
    die("ReceiveDatagram") ;
 else
   fprintf(stderr,"bytes recus:%d:%s\n",rc,reponse ) ;
 
 close(Desc) ;
}
