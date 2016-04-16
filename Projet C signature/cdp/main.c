#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*
* calcul du minimum entre deux entiers
* en entrée : deux entiers x et y
* en sortie : le minimum.
*/

double min(double x,double y){
    if(x<y)return x;
    else return y;

}


/*
* calcul de la distance entre deux entiers situé dans deux tableaux
* en entrée : deux tableaux d'entier, i et j la position respective des entiers dans le tableau.
* en sortie : la distance entre les deux entiers.
*/
double distance(int ** table1, int ** table2 ,int indexTable1, int indexTable2, int nbElement){

double somme = 0 ;

if(table1==NULL || table2==NULL){
    printf("Erreur");
    return -1;
}

int k = 0; /*permet de parcourir les composante d'un vecteur*/

    for(k=0 ; k<nbElement ;k++){
        somme = somme + (double)((table1[k][indexTable1]-table2[k][indexTable2])*(table1[k][indexTable1]-table2[k][indexTable2]));
    }

return sqrt(somme);
}

/*calcul de la matrice P :

Matrice de cumule des distances entre les deux matrices en paramêtre

*/

double ** cdp(int ** test , int ** reference, int sizeTest, int sizeRef, int nbEleVect){

/*déclaration du pointeur vers la matrice résultat*/
double **matriceP;

/*variable d'accès*/
int j;
int i;

/*initialisation de la matrice*/

matriceP =(double**)malloc((sizeTest+2)*sizeof(double*));
if(matriceP==NULL){
        printf("erreur malloc matriceP");
        return NULL;
}
else{
        /* alocation d'un tableau d'entier pour chaque ligne de la matrice P*/
    for(i = 0 ; i < sizeTest+2 ; i++){
            matriceP[i]=(double*)malloc(sizeRef*sizeof(double));
            if(*matriceP==NULL){
            printf("erreur malloc matriceP");
            return NULL;
            }
    }

    for( j=0 ; j<sizeRef ; j++){
        matriceP[0][j]=9999;
        matriceP[1][j]=9999;
    }
    for(i =2 ; i<(sizeTest+2) ; i++){

        matriceP[i][0] = 3*distance(test,reference,i-2,0, nbEleVect);

        if(i<=2){
            matriceP[i][1]=min((matriceP[i-1][0]+3*distance(test,reference,i-2,1,nbEleVect)),(matriceP[i][0]+3*distance(test,reference,i-2,1,nbEleVect)));
        }
        else{
            matriceP[i][1]=min(min((matriceP[i-2][0]+2*distance(test,reference,i-3,1,nbEleVect)+distance(test,reference,i-2,1,nbEleVect)),(matriceP[i-1][0]+3*distance(test,reference,i-2,1,nbEleVect))),(matriceP[i][0]+3*distance(test,reference,i-2,1,nbEleVect)));
        }

        for(j=2 ; j<sizeRef ; j++){
            if(i<=2){
                matriceP[i][j]= min((matriceP[i-1][j-1]+3*distance(test,reference,i-2,j,nbEleVect)),(matriceP[i-1][j-2]+3*distance(test,reference,i-2,j-1,nbEleVect)+3*distance(test,reference,i-2,j,nbEleVect)));
            }
            else{
                matriceP[i][j]=min(min((matriceP[i-2][j-1]+2*distance(test,reference,i-3,j,nbEleVect)+distance(test,reference,i-2,j,nbEleVect)),(matriceP[i-1][j-1]+3*distance(test,reference,i-2,j,nbEleVect))),(matriceP[i-1][j-2]+3*distance(test,reference,i-2,j-1,nbEleVect)+3*distance(test,reference,i-2,j,nbEleVect)));
            }
        }
    }
    return matriceP;

}

return NULL;

}

void afficheMatriceP(double **table , int sizeHeight , int sizeLength){

int j;
int i;

for(i=0 ; i<sizeHeight ; i++){
    printf("\n");
    for(j=0 ; j<sizeLength; j++){
        printf("\t");
        printf(" %f ",table[i][j]);
        printf("\t");
    }
    printf("\n");
}

}

void afficheMatrice(int **table , int sizeHeight , int sizeLength){
    
    int j;
    int i;
    
    for(i=0 ; i<sizeHeight ; i++){
        printf("\n");
        for(j=0 ; j<sizeLength; j++){
            printf("\t");
            printf(" %d ",table[i][j]);
            printf("\t");
        }
        printf("\n");
    }
    
}

/*fonction resultat final*/
double * resultatA(double** matriceP , int sizeTest, int sizeRef , int nbEleVect){

int i;
double * A=(double *)malloc(sizeTest*sizeof(int));
if(A==NULL){
    printf("Erreur allocation A");
    return NULL;
}

for(i=0 ; i<sizeTest ; i++){
    A[i]=(matriceP[i+2][sizeRef-1])/(3*sizeRef);
}

return A;

}



void afficheMatriceA(double *table , int sizeHeight){

int i;

for(i=0 ; i<sizeHeight ; i++){
    printf("\n");
        printf(" %f ",table[i]);
    printf("\n");
}

}


/*création de tableau à multidimention*/
/* n et m sont les tailles du tableau du fichier*/


int ** createTable(char * monFichier , int n , int m){
    char buffer[10]="";

    /*déclaration et initialisation des compteurs*/
    int i=0;
    int j=0;
    int k=0;

    /*déclaration du tableau*/
    int ** table = NULL;
    /*déclaration du pointeur sur le fichier*/
    FILE* fichier; // = NULL;

    /*déclaration de la variable permettant de lire un caractere du fichier*/
    char caractereActuel=0;
    /*déclaration d'un boolean permettant de savoir si la variable caractereActuel est vide*/
    int vide=0;/*caractereActuel est vide*/

/*Allocation dynamique du tableau de taille n*m */
    table =(int**)malloc(n*sizeof(int*));
    if(table==NULL){
            printf("erreur malloc table");
            return NULL;
    }
    while(i<n){
            table[i] = (int*)malloc(m*sizeof(int));
            if(table[i]==NULL){
                printf("erreur malloc table");
                return NULL;
            }
            i++;
    }


    fichier = fopen(monFichier, "r+");/*ouverture du fichier*/
    if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier

       // Boucle de lecture des caractères un à un
        j=0;/*compteur des lignes du tableau initialiser à 0*/
        while (caractereActuel != EOF){ /*On continue tant que fgetc n'a pas retourné EOF (fin de fichier)*/

            k=0;/*compteur des colonnes du tableau initialiser à 0*/
            while(caractereActuel!=(char)';' && caractereActuel != EOF){/*boucle effectuer si on est pas à la fin d'une ligne*/
                    i=0;/*on réinitialise le compteur du buffer*/

                    if(vide==0){/*si on a pas encore lu le fichier caractereActuel est vide*/
                        caractereActuel=fgetc(fichier); /* On lit le caractère*/
                    }

                    while(caractereActuel!=(char)',' && caractereActuel!=(char)'\n' && caractereActuel != EOF){/*boucle effectuer jusqu'à ce qu'on arrive à la fin d'une cellule.*/
                        buffer [i]=caractereActuel; /*enregistrement des valeurs contenu dans la cellule*/
                        caractereActuel=fgetc(fichier); /* On lit le caractère*/
                        i++;
                    }
                    /*on considère que le fichier csv ne possède pas de cellule vide, cela n'aurait aucun intérêt*/

                    table[j][k]=atoi(buffer);/*convertion de la valeur du buffer en int et ajout de cette valeur au tableau*/
                    k++;
                }
            /*ici caractereActuel est soit un "," soit un ";"*/
            caractereActuel=fgetc(fichier); /* On lit le caractère , ici caractereActuel est soit un int soit la fin du fichier*/
            vide=1;/*on a commencé à lire le fichier caractereActuel est non vide*/
            j++;
        }

        fclose(fichier); // On ferme le fichier qui a été ouvert
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier ");
        return NULL;
    }


    return table;/*on retourne le tableau*/

}



int main()
{
/* définition des matrices */

int nbEleVect =3;
double ** P;
double * A;

/*Fichier de Référence*/
char fichierRef []= "/Users/Charles/Documents/test/algo/algo/ref.txt";

/*déclaration du pointeur vers le fichier*/
int ** reference=createTable(fichierRef, 6 , nbEleVect);

/*Fichier à comparer*/
char fichierTest[] = "/Users/Charles/Documents/test/algo/algo/test.txt";

/*déclaration du pointeur vers le fichier*/
int ** test=createTable(fichierTest , 6 , nbEleVect);

/*si les fichier sont vide on affiche une erreur*/
if(test== NULL || reference==NULL){
        printf("test ou ref == NULL");
    return 0;
}


else{


printf("\n");

printf("\n \n \n Matrice P :");

P=cdp(test, reference, 6 , 6, nbEleVect);
afficheMatriceP(P, 8, 6);
    afficheMatrice(test,3,6);
    afficheMatrice(reference, 3, 6);
    double y;
    for(int i=0;i<6;i++)
    {
    y=distance(test, reference, 0, i, nbEleVect);
    printf(" \n \n valeur y : %f ",y);
    }
printf("\n \n \n Matrice A");

A=resultatA(P, 6, 6 , nbEleVect);
afficheMatriceA(A,6);

free(reference);
free(test);
free(P);
free(A);
}
return 0;
}
