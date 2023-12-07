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

int ReservationHV(char* NomFichier,int Reference,int Quantite)
{
    FILE* fp;
    struct VehiculeHV UnRecord;
    int i = 0;

    fp = fopen(NomFichier,"r+");
    if (fp == NULL)
    {
        fprintf(stderr,"Echec Ouverture\n");
        exit(0);
    }

    while(fread(&UnRecord,sizeof(struct VehiculeHV),1,fp) == 1)
    {
        if(UnRecord.Reference == Reference && UnRecord.Quantite >= Quantite)
        {
            UnRecord.Quantite -= Quantite;
            fseek(fp, -sizeof(struct VehiculeHV), SEEK_CUR);
            fwrite(&UnRecord,sizeof(struct VehiculeHV),1,fp);
            i = 1;
            break;
        }
    }

    fclose(fp);

    return i;
}

int FacturationHV(char NomFichier[80],char NomClient[60],time_t Date,int Quantite,int Reference)
{
    FILE* fp;
    struct FactureHV UneFacture;
    int NumeroFacturation;

    fp = fopen(NomFichier,"a");

    if (fp == NULL)
    {
        fprintf(stderr,"Echec Ouverture\n");
        exit(0);
    }

    fseek(fp, 0, SEEK_END);
    NumeroFacturation = ftell(fp) / sizeof(struct FactureHV)+1;

    UneFacture.NumeroFacturation = NumeroFacturation;
    strcpy(UneFacture.Acheteur,NomClient);
    UneFacture.DateFacturation = Date;
    UneFacture.Quantite = Quantite;
    UneFacture.Reference = Reference;

    fwrite(&UneFacture,sizeof(struct FactureHV),1,fp);
    fclose(fp);

    return NumeroFacturation;
}