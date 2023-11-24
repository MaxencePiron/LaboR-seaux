/*--------------------------------------
  Herman Vanstapel
  
  ex02\ser.c 
  
  Un serveur recevant une structure 
----------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../udplib/udplib.h"
#include "RequeteMP.h" // remplace structure.h
#include "LibSerMP.h"
#include "data.h"


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
 struct RequeteMP UneRequeteR;
 struct RequeteMP UneRequeteE;
 struct VehiculeHV UnRecord;

 memset(&sthis,0,sizeof(struct sockaddr_in)) ;
 memset(&sos,0,sizeof(struct sockaddr_in)) ; 
 memset(&sor,0,sizeof(struct sockaddr_in)) ; 
 
 printf("Ceci est le serveur\n") ;
 if ( argc!=3)
 {
  printf("ser ser port cli\n") ;
  exit(1) ;
 }
 
 /* Récupération IP & port   */
 IpSocket= inet_addr(argv[1]);
 PortSocket = atoi(argv[2]);
 // Desc = CreateSockets(&psoo,&psos,,atoi(argv[2]),argv[3],atoi(argv[4])) ;
 Desc=creer_socket(SOCK_DGRAM,&IpSocket,PortSocket,&sthis);
 
 if ( Desc == -1 )
    die("CreateSockets:") ;
 else
    fprintf(stderr,"CreateSockets %d\n",Desc) ;

 tm = sizeof(struct RequeteMP) ;

 //int Reference = 0;

 while(1)
 {
    InitRequeteMP(&UneRequeteR);


    rc = ReceiveDatagram( Desc,&UneRequeteR ,tm, &sor ) ;
    if ( rc == -1 )
       die("ReceiveDatagram") ;
    else
    {
      printf("bytes lus:%d Reference :%d\n",rc,UneRequeteR.Reference);
      //Reference++;
    }
    
    printf("Type recu %d\n", UneRequeteR.Type) ;

     // Le traitement doit être s&paré des requetes réseaux */
    printf("Received packet from %s:%d\n", inet_ntoa(sor.sin_addr), ntohs(sor.sin_port));
    fprintf(stderr,"Received packet from %s:%d\n", inet_ntoa(sor.sin_addr), ntohs(sor.sin_port));

    InitRequeteMP(&UneRequeteE);

    switch(UneRequeteR.Type)
    {
      case Question:
            res = RechercheHV("VehiculesHV",UneRequeteR.Reference ,&UnRecord) ;
            fprintf(stderr,"res :%d Reference:%s %s\n",res,UnRecord.Marque, UnRecord.Modele) ;
            /* reponse avec psor qui contient toujours l'adresse du dernier client */

             memset(&UneRequeteE,0,sizeof(struct RequeteHV));
             if(res==1)
             {
               UneRequeteE.Reference = UneRequeteR.Reference ;
               strncpy(UneRequeteE.Marque,UnRecord.Marque,sizeof(UneRequeteE.Marque)) ;
               strncpy(UneRequeteE.Modele,UnRecord.Modele,sizeof(UneRequeteE.Modele)) ;
               UneRequeteE.Puissance = UnRecord.Puissance;
               UneRequeteE.Quantite = UnRecord.Quantite;
            }
   }     

    UneRequete.Type = OK ; 
    strcat(UneRequete.Message," Client") ; 
    AfficheRequeteHV(stderr,UneRequete);
    rc = SendDatagram(Desc,&UneRequete,sizeof(struct RequeteMP) ,&sor ) ;
    if ( rc == -1 )
       die("SendDatagram:") ;
    else
      printf("bytes écrits:%d\n",rc ) ;
 
 }

 close(Desc) ;
}
