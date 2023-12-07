#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"

void AProposServeurHV(char *Version,char *Nom1,char* Nom2);
int RechercheHV(char *NomFichier,int Reference,struct VehiculeHV *UnRecord);
int ReservationHV(char* NomFichier,int Reference,int Quantite);
int FacturationHV(char NomFichier[80],char NomClient[60],time_t Date,int Quantite,int Reference);