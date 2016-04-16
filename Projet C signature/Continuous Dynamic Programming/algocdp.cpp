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


/*calcul de la matrice P :

cdp :
– Entrée :
– reference, test : les tableaux des matrices référence et test de types double**.
– sizeRef : nombre de colonnes de la matrice référence de type int.
– sizeTest : nombre de colonnes de la matrice test de type int.
– nbEleVect : nombre de ligne des matrices test et référence de type int.
– Sortie : le tableau de type double** correspondant au cumule des distances entre la matrice test
et la matrice référence.

*/

double ** cdp(double ** reference, double ** test, int sizeRef, int sizeTest, int nbEleVect) {

	/*déclaration du pointeur vers la matrice résultat*/
	double **matriceP;

	/*variable d'accès*/
	int j;
	int i;

	/*initialisation de la matrice*/

	matriceP = (double**)malloc((sizeRef + 2)*sizeof(double*));
	if (matriceP == NULL) {
		printf("erreur malloc matriceP");
		return NULL;
	}
	else {
		/* alocation d'un tableau d'entier pour chaque ligne de la matrice P*/
		for (i = 0; i < sizeRef + 2; i++) {
			matriceP[i] = (double*)malloc(sizeTest*sizeof(double));
			if (*matriceP == NULL) {
				printf("erreur malloc matriceP");
				return NULL;
			}
		}

		for (j = 0; j<sizeTest; j++) {
			matriceP[0][j] = 9999999;
			matriceP[1][j] = 9999999;
		}
		for (i = 2; i<(sizeRef + 2); i++) {

			matriceP[i][0] = 3 * distance(reference, test, i - 2, 0, nbEleVect);

			if (i <= 2) {
				matriceP[i][1] = min((matriceP[i - 1][0] + 3 * distance(reference, test, i - 2, 1, nbEleVect)), (matriceP[i][0] + 3 * distance(reference, test, i - 2, 1, nbEleVect)));
			}
			else {
				matriceP[i][1] = min(min((matriceP[i - 2][0] + 2 * distance(reference, test, i - 3, 1, nbEleVect) + distance(reference, test, i - 2, 1, nbEleVect)), (matriceP[i - 1][0] + 3 * distance(reference, test, i - 2, 1, nbEleVect))), (matriceP[i][0] + 3 * distance(reference, test, i - 2, 1, nbEleVect)));
			}

			for (j = 2; j<sizeTest; j++) {
				if (i <= 2) {
					matriceP[i][j] = min((matriceP[i - 1][j - 1] + 3 * distance(reference, test, i - 2, j, nbEleVect)), (matriceP[i - 1][j - 2] + 3 * distance(reference, test, i - 2, j - 1, nbEleVect) + 3 * distance(reference, test, i - 2, j, nbEleVect)));
				}
				else {
					matriceP[i][j] = min(min((matriceP[i - 2][j - 1] + 2 * distance(reference, test, i - 3, j, nbEleVect) + distance(reference, test, i - 2, j, nbEleVect)), (matriceP[i - 1][j - 1] + 3 * distance(reference, test, i - 2, j, nbEleVect))), (matriceP[i - 1][j - 2] + 3 * distance(reference, test, i - 2, j - 1, nbEleVect) + 3 * distance(reference, test, i - 2, j, nbEleVect)));
				}
			}
		}
		return matriceP;

	}

	return NULL;

}



/*fonction resultat final



resultatA :
– Entrée :
– matriceP : le tableau de réel de la matrice calculé par CDP, de type double.
– sizeRef : nombre de colonne de la matrice P.
– sizeTest : nombre de ligne de la matrice P.
– Sortie : retourne un tableau de type double* qui correspond à la dernière colonne de la matriceP
normalisé.



*/
double * resultatA(double** matriceP, int sizeRef, int sizeTest) {

	int i;
	double * A = (double *)malloc(sizeRef*sizeof(double));
	if (A == NULL) {
		printf("Erreur allocation A");
		return NULL;
	}

	for (i = 0; i<sizeRef; i++) {
		A[i] = (matriceP[i + 2][sizeTest - 1]) / (3 * sizeTest);
		/*A[i]=(matriceP[i+2][sizeTest-1]);*/
	}

	return A;

}




/*
* Initialisation d'une liste contenant les indexs
init_listIndex :
– Entrée : newIndex : un pointeur sur une structure listIndex.
– Sortie : initialise la structure listIndex (voir ci-dessous).
*/
void init_listIndex(listIndex * newIndex) {
	newIndex->index = 0;
	newIndex->nxt = NULL;
}


/*

findIndexSubSequence :
– Entrée :
– table : un tableau de réel de dimention 1 de type double *.
– sizeHeight : la taille du tableau de type int.
– seuil : le seuil de type double utilisé afin de trouver les index des minimums du tableau.
– Sortie : une structure de type listIndex qui contient les index des minimums du tableau (voir-ci
dessous).


*/
listIndex * findIndexSubSequence(double * table, int sizeHeight, double seuil) {


	int i = 0;
	int j = 0;

	listIndex * listeIndex = NULL;

	for (i = 1; i<sizeHeight; i++) {
		if (table[i] <= seuil && table[i - 1]>table[i]) {
			j = i;
			while (table[i] >= table[j] && j<sizeHeight) {
				i = j;
				j++;
			}
			/* i=j;*/
			listIndex * newIndex = (listIndex*)malloc(sizeof(listIndex));
			init_listIndex(newIndex);
			newIndex->index = i;
			newIndex->nxt = listeIndex;
			listeIndex = newIndex;
		}
	}
	return listeIndex;
}

