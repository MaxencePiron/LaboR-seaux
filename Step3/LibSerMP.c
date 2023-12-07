#include "LibSerMP.h"

void AProposServeurHV(char *Version,char *Nom1,char* Nom2)
{
    printf("Version : %s \n",Version);
    printf("Prenom : %s \n",Nom1);
    printf("Nom : %s \n",Nom2);
}

int RechercheHV(char *NomFichier,int Reference,struct VehiculeHV *UnRecord)
{
    FILE *fp;
    int i=0;

    fp = fopen(NomFichier,"r");
    if(fp == NULL)
    {
        fprintf(stderr,"Echec Ouverture\n");
        exit(0);
    }

    while(fread(UnRecord,sizeof(struct VehiculeHV),1,fp) == 1)
    {
        if(UnRecord->Reference == Reference)
        {
            i = 1;
            break;
        }
    }

    fclose(fp);

    return i;
}

