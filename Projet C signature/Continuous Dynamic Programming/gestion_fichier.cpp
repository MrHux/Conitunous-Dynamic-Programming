//
//  algo_cdp.c
//  algo
//
//  Created by Charles & Paul on 02/06/2014.
//  Copyright (c) 2014 Charles & Paul. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "struct.h"


/*
compteur de taille de fichier

countFileSize :
� Entr�e : monFichier : une chaine de caract�re de type char* qui contient un nom de fichier.csv
(contenant une matrice).
� Sortie : retourne la taille du fichier sous la forme d�une structure TableSize (voir-ci apr�s).

*/

TableSize countFileSize(char * monFichier) {

	int j = 0;
	int k = 0;

	FILE * fichier = NULL;

	TableSize FileSize;
	FileSize.nbColonne = 0;
	FileSize.nbLigne = 0;

	/*d�claration de la variable permettant de lire un caractere du fichier*/
	char caractereActuel = 0;

	int vide = 0;
	fichier = fopen(monFichier, "r+");/*ouverture du fichier*/
	if (fichier != NULL)
	{
		// On peut lire et �crire dans le fichier

		// Boucle de lecture des caract�res un � un
		j = 0;/*compteur des lignes du tableau initialiser � 0*/
		while (caractereActuel != EOF) { /*On continue tant que fgetc n'a pas retourn� EOF (fin de fichier)*/

			k = 0;/*compteur des colonnes du tableau initialiser � 0*/
			while (caractereActuel != (char)'\n' && caractereActuel != EOF) {/*boucle effectuer si on est pas � la fin d'une ligne*/

				if (vide == 0) {/*si on a pas encore lu le fichier caractereActuel est vide*/
					caractereActuel = fgetc(fichier); /* On lit le caract�re*/
				}
				vide = 0;
				while (caractereActuel != (char)',' && caractereActuel != (char)'\n' && caractereActuel != EOF) {/*boucle effectuer jusqu'� ce qu'on arrive � la fin d'une cellule.*/
					caractereActuel = fgetc(fichier); /* On lit le caract�re*/
				}
				/*on consid�re que le fichier csv ne poss�de pas de cellule vide, cela n'aurait aucun int�r�t*/
				k++;
			}
			/*ici caractereActuel est soit un "," soit un ";"*/
			caractereActuel = fgetc(fichier); /* On lit le caract�re , ici caractereActuel est soit un int soit la fin du fichier*/
			vide = 1;/*on a commenc� � lire le fichier caractereActuel est non vide*/
			j++;
		}
		FileSize.nbColonne = k;
		FileSize.nbLigne = j;
		fclose(fichier); // On ferme le fichier qui a �t� ouvert
	}
	else
	{
		// On affiche un message d'erreur si on veut
		printf("Impossible d'ouvrir le fichier ");
		return FileSize;
	}

	return FileSize;

}



/*cr�ation de tableau � multidimention*/
/*createTable :
� Entr�e :
� monFichier : une chaine de caract�re de type char* qui contient un nom du fichier.
� nbColonne : le nombre de colonne de vecteurs dans le fichier de type int.
� nbEleVect : le nombre de caract�ristique d�un vecteur dans le fichier (nombre de ligne) de type int.
� Sortie : retourne un pointeur sur un tableau de r�el de type double** � deux dimensions allouer
dynamiquement.
*/


double ** createTable(char * monFichier, int nbColonne, int nbEleVect) {
	char buffer[100] = "";

	/*d�claration et initialisation des compteurs*/
	int i = 0;
	int j = 0;
	int k = 0;

	/*d�claration du tableau*/
	double ** table = NULL;
	/*d�claration du pointeur sur le fichier*/
	FILE* fichier; // = NULL;

				   /*d�claration de la variable permettant de lire un caractere du fichier*/
	char caractereActuel = 0;
	/*d�claration d'un boolean permettant de savoir si la variable caractereActuel est vide*/
	int vide = 0;/*caractereActuel est vide*/

				 /*Allocation dynamique du tableau de taille n*m */
	table = (double**)malloc(nbEleVect*sizeof(double*));
	if (table == NULL) {
		printf("erreur malloc table");
		return NULL;
	}
	i = 0;
	while (i<nbEleVect) {
		table[i] = (double*)malloc(nbColonne*sizeof(double));
		if (table[i] == NULL) {
			printf("erreur malloc table");
			return NULL;
		}
		i++;
	}


	fichier = fopen(monFichier, "r+");/*ouverture du fichier*/
	if (fichier != NULL)
	{
		// On peut lire et �crire dans le fichier

		// Boucle de lecture des caract�res un � un
		j = 0;/*compteur des lignes du tableau initialiser � 0*/
		while (caractereActuel != EOF) { /*On continue tant que fgetc n'a pas retourn� EOF (fin de fichier)*/

			k = 0;/*compteur des colonnes du tableau initialiser � 0*/
			while (caractereActuel != (char)'\n' && caractereActuel != EOF) {/*boucle effectuer si on est pas � la fin d'une ligne*/
				i = 0;/*on r�initialise le compteur du buffer*/

				if (vide == 0) {/*si on a pas encore lu le fichier caractereActuel est vide*/
					caractereActuel = fgetc(fichier); /* On lit le caract�re*/
				}
				vide = 0;
				while (caractereActuel != (char)',' && caractereActuel != (char)'\n' && caractereActuel != EOF) {/*boucle effectuer jusqu'� ce qu'on arrive � la fin d'une cellule.*/
					buffer[i] = caractereActuel; /*enregistrement des valeurs contenu dans la cellule*/
					caractereActuel = fgetc(fichier); /* On lit le caract�re*/
					i++;
				}
				buffer[i] = '\0';
				/*on consid�re que le fichier csv ne poss�de pas de cellule vide, cela n'aurait aucun int�r�t*/
				table[j][k] = strtod(buffer, NULL);/*convertion de la valeur du buffer en int et ajout de cette valeur au tableau*/
				k++;
			}
			/*ici caractereActuel est soit un "," soit un ";"*/
			caractereActuel = fgetc(fichier); /* On lit le caract�re , ici caractereActuel est soit un int soit la fin du fichier*/
			vide = 1;/*on a commenc� � lire le fichier caractereActuel est non vide*/
			j++;
		}

		fclose(fichier); // On ferme le fichier qui a �t� ouvert
	}
	else
	{
		// On affiche un message d'erreur si on veut
		printf("Impossible d'ouvrir le fichier ");
		return NULL;
	}


	return table;/*on retourne le tableau*/

}

/*
resultat :
� Entr�e :
� A : un tableau de r�el de une dimensions de type double*.
� P : un tableau de r�el de deux dimensions de type double**.
� tailleREf : le nombre de colonne du tableau ref de type int.
� tailleTest : le nombre de colonne du tableau test de typeint.
� fichierResultat : la chaine de caract�re de type char* qui contient le chemin vers le fichier resultat.
� fichierMatriceP : la chaine de caract�re de type char* qui contient le chemin vers le fichier matrice
P.
� seuil : le seuilde type double utilis� par l�algorithme afin de trouver les index des minimums.
� Sortie : �cris la matrice A dans la le fichier r�sultats et �crit la matrice P dans le fichier matrice P.
*/



void resultat(double * A, double ** P, int tailleRef, int tailleTest, char * fichierResultat, char * fichierMatriceP, double seuil) {


	char s[100] = "";

	int j;
	int i;

	FILE* fichier;

	fichier = fopen(fichierMatriceP, "w+");

	if (fichier != NULL) {



		fputs("Matrice P : \n", fichier);

		for (i = 0; i<tailleRef + 2; i++) {

			fputs("\n", fichier);
			for (j = 0; j<tailleTest; j++) {
				sprintf(s, "%f", P[i][j]);
				fputs(s, fichier);
				fputs(",", fichier);
			}
		}

	}
	else {
		// On affiche un message d'erreur si on veut
		printf("Impossible d'ouvrir le fichier matrice P ");
	}

	fichier = fopen(fichierResultat, "w+");/*ouverture du fichier*/
	if (fichier != NULL) {


		fputs("Le(s) index trouv�(s) est(sont) : ", fichier);
		listIndex * indexSubSeq = NULL;

		indexSubSeq = findIndexSubSequence(A, tailleRef, seuil);


		while (indexSubSeq != NULL) {

			sprintf(s, "%d\t", indexSubSeq->index);
			fputs(s, fichier);

			indexSubSeq = indexSubSeq->nxt;
		}

		fputs("\n \n", fichier);

		fputs("Matrice A : \n \n", fichier);

		for (j = 0; j<tailleRef; j++) {
			fputs("\n", fichier);
			sprintf(s, "%d\t%f", j, A[j]);
			fputs(s, fichier);
		}



		fclose(fichier);
		free(indexSubSeq);
	}

	else {
		// On affiche un message d'erreur si on veut
		printf("Impossible d'ouvrir le fichier resultat ");
	}

}



