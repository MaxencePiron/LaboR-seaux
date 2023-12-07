/*---------------------------------------------------------------
   Vanstapel Herman
   ex02\cli.c

 Le client dit bonjour en utilisant un structure  et
 le serveur fait de même
------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "../udplib/udplib.h"
#include "RequeteMP.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

static void signal_handler(int sig){}

int main(int argc, char *argv[])
{
 int rc ;
 int Desc ;
 int tm ; 
 int choix;
 int BoucleAffichage = 1;
 char Tampon[80];
 int NumRequete = 1;
 int NumRecherche = 1;
 unsigned int time_interval;
 struct sigaction act;
 int ret;

 u_long  IpSocket , IpServer;
 u_short PortSocket, PortServer ; 
 
 struct sockaddr_in sthis ; /* this ce programme */
 struct sockaddr_in sos ; /* s = serveur */
 struct sockaddr_in sor ; /* r = remote */
 struct RequeteMP UneRequeteE;
 struct RequeteMP UneRequeteR;
 
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

  while(BoucleAffichage)
  {
   act.sa_handler = signal_handler;
   act.sa_flags = 0 ;
   sigemptyset (&act.sa_mask);
   rc = sigaction (SIGALRM, &act, NULL);

    printf("------------------------------\n");
    printf("1) Demander une reference\n");
    printf("2) Acheter un vehicule\n");
    printf("3) Quitter\n");
    printf("------------------------------\n");

    printf("Choix : ");
    fgets(Tampon,sizeof(Tampon),stdin);
    choix = atoi(Tampon);

    switch(choix)
    {
      case 1:
         memset(&UneRequeteE,0,sizeof(struct RequeteMP)) ;
         InitRequeteMP(&UneRequeteE);

         printf("Saisie reference vehicule : ");
         fgets(Tampon,sizeof(Tampon),stdin);
         UneRequeteE.Reference = atoi(Tampon);

         UneRequeteE.Numero = NumRecherche;
    
         UneRequeteE.Type = Question ; 
          
         rc = SendDatagram(Desc,&UneRequeteE,sizeof(struct RequeteMP) ,&sos ) ;

         if ( rc == -1 )
            die("SendDatagram") ;
         else
            printf("bytes écrits %d\n",rc ) ;

         while(1)
         {
            memset(&UneRequeteR,0,sizeof(struct RequeteMP)) ;
            InitRequeteMP(&UneRequeteR);
            tm = sizeof(struct RequeteMP);
         
            rc = ReceiveDatagram(Desc, &UneRequeteR, tm, &sor);
            if (rc <= 0)
            {
               perror("error sur receive:");
            }
            if (UneRequeteR.Numero != NumRecherche){ 
               printf("doublon 0 !!!!!\n");
               AfficheRequeteHV(stderr,UneRequeteR);
            }
            else
            { 
               AfficheRequeteHV(stderr,UneRequeteR);
               break;
            }
         }

         break;

      case 2:
      {
         memset(&UneRequeteE, 0, sizeof(struct RequeteMP));
         InitRequeteMP(&UneRequeteE);
         UneRequeteE.Type = Achat;
         UneRequeteE.Numero = NumRequete;

         printf("NomClient :");
         fgets(UneRequeteE.NomClient, sizeof(UneRequeteE.NomClient), stdin);
         printf("Reference :");
         fgets(Tampon, sizeof(Tampon), stdin);
         UneRequeteE.Reference = atoi(Tampon);
         printf("Quantite:");
         fgets(Tampon, sizeof(Tampon), stdin);
         UneRequeteE.Quantite = atoi(Tampon);

         rc = SendDatagram(Desc, &UneRequeteE, sizeof(struct RequeteMP), &sos);

         if (rc == -1)
            die("SendDatagram");
         else
            printf("bytes écrits %d\n", rc);

         redo:
         time_interval = 9;
         ret = alarm(time_interval);
         rc = SendDatagram(Desc, &UneRequeteE, sizeof(struct RequeteMP), &sos);

         if (rc == -1)
            die("SendDatagram");
         else
            fprintf(stderr, "Envoi du message %d avec %d bytes\n", UneRequeteE.Numero, rc);

         while (1) /* on boucle tant que l'on ne reçoit pas le bon message */
         {
            memset(&UneRequeteR, 0, sizeof(struct RequeteMP));
            InitRequeteMP(&UneRequeteR);
            tm = sizeof(struct RequeteMP);
            rc = ReceiveDatagram(Desc, &UneRequeteR, tm, &sor);
            if (rc <= 0)
            {
               perror("error sur receive:");
               goto redo;
            }
            if (UneRequeteR.Numero != NumRequete){ 
               printf("doublon !!!!!\n");
            }
            else
            { 
               break;
            }
         }

         /* fin de l'alarme */
         ret = alarm(0);
         fprintf(stderr, "bytes:%d:Compteur %d:%s\n", rc, UneRequeteR.Numero, UneRequeteR.Message);
         NumRequete++;
         sleep(5);

         break;
      }

      case 3: BoucleAffichage = 0;
         break;

      default: printf("Entrer un numero valide !\n");
    }
 }

 close(Desc) ;
}
