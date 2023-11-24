/*---------------------------------------------------------------------------------------------
  Herman vanstapel

 ex07ti\ser.c :  Un serveur avec plusieurs clients qui affiche chaque fois l'ip et le port du client connecté
-----------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "structure.h"
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h> 

static void signal_handler(int sig)
{  
  // siglongjmp(env,sig);
  switch (sig)	 {
	case SIGINT:
	     printf("longjumped from interrupt CRTL C  %d\n",SIGINT);
	     exit(0) ;
             /* On fermerait les fichiers */
	     break;
	case SIGTSTP:
             printf("longjumped from interrupt CTRL Z  %d\n",SIGTSTP);
             printf("Demarrage du sleep \n") ;
             sleep(30) ;
             printf("Fin du sleep \n") ;
             break ;
     } ;
}

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc,char *argv[])
{
 int rc ;
 int Desc ;
 
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */

 u_long  IpSocket ;
 u_short PortSocket ;
 
 int tm ;
 struct Requete UneRequete ;
 char Tampon[40] ;
 int Ip, Port ;

 memset(&sthis,0,sizeof(struct sockaddr_in)) ;
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 
 printf("Ceci est le serveur\n") ;
 if ( argc!=3)
 {
  printf("ser ser port \n") ;
  exit(1) ;
 }
 
 /* Récupération IP & port   */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);
 
 if ( Desc == -1 )
    die("CreateSockets") ;
 else
    printf(" CreateSockets : %d \n",Desc) ;
 
 while(1) 
 {     

  signal(SIGINT, signal_handler);
  signal(SIGTSTP, signal_handler) ; 
  
  memset(&UneRequete,0,sizeof(UneRequete)) ;
  tm = sizeof(struct Requete) ;
  rc = ReceiveDatagram( Desc,&UneRequete ,tm, &sor ) ;
  if ( rc == -1 )
    die("ReceiveDatagram") ;
  else
     fprintf(stderr,"bytes:%d:%s:%d\n",rc,UneRequete.Message,ntohl(UneRequete.Compteur)); 
   
    printf("Received packet from %s:%d\n", inet_ntoa(sor.sin_addr), ntohs(sor.sin_port));
  /* reponse avec psor qui contient toujours l'adresse du dernier client */
 
  UneRequete.Type = htonl(Reponse) ; 
  strcat(UneRequete.Message," Client") ;
  rc = SendDatagram(Desc,&UneRequete,sizeof(struct Requete) ,&sor ) ;
  if ( rc == -1 )
    die("SendDatagram:") ;
  else
    fprintf(stderr,"bytes:%d\n",rc ) ;
 }
}
