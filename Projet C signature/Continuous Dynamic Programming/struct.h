#pragma once
//
//  struct.h
//  algo
//
//  Created by Charles on 27/05/2014.
//  Copyright (c) 2014 Charles. All rights reserved.
//



#ifndef algo_struct_h
#define algo_struct_h

/*
Structure qui permet de stocker la taille des tableaux:

nbColonne : contient le nombre de colonne du tableau;
nbLigne : contient le nombre de ligne du tableau;
*/
typedef struct TableSize TableSize;
struct TableSize
{
	int nbColonne;
	int nbLigne;
};


/* permet de stocker les index*/
typedef struct listIndex {
	int index;
	struct listIndex *nxt;
} listIndex;


/*min :
– Entrée : x,y : deux réels de type double.
– Sortie : retourne le minimum en type double.
*/

double min(double x, double y);


/*

distance :
– Entrée :
– table1, table2 : deux tableaux de réel à deux dimensions de type double **.
– indexTable1, indexTable2 : les index des colonnes de ces deux tableaux de type int.
– nbElement : le nombre d’éléments dans chaque colonnes de ces tableaux de type int.
– Sortie : retourne la distance euclidienne entre les deux colonnes.

*/
double distance(double ** table1, double ** table2, int indexTable1, int indexTable2, int nbElement);

/*
cdp :
– Entrée :
– reference, test : les tableaux des matrices référence et test de types double**.
– sizeRef : nombre de colonnes de la matrice référence de type int.
– sizeTest : nombre de colonnes de la matrice test de type int.
– nbEleVect : nombre de ligne des matrices test et référence de type int.
– Sortie : le tableau de type double** correspondant au cumule des distances entre la matrice test
et la matrice référence.


**/



double ** cdp(double ** test, double ** reference, int sizeTest, int sizeRef, int nbEleVect);


/*
resultatA :
– Entrée :
– matriceP : le tableau de réel de la matrice calculé par CDP, de type double.
– sizeRef : nombre de colonne de la matrice P.
– sizeTest : nombre de ligne de la matrice P.
– Sortie : retourne un tableau de type double* qui correspond à la dernière colonne de la matriceP
normalisé.


*/
double * resultatA(double** matriceP, int sizeTest, int sizeRef, int nbEleVect);

/*

countFileSize :
– Entrée : monFichier : une chaine de caractère de type char* qui contient un nom de fichier.csv
(contenant une matrice).
– Sortie : retourne la taille du fichier sous la forme d’une structure TableSize (voir-ci après).
*/
TableSize countFileSize(char * monFichier);
/*
createTable :
– Entrée :
– monFichier : une chaine de caractère de type char* qui contient un nom du fichier.
– nbColonne : le nombre de colonne de vecteurs dans le fichier de type int.
– nbEleVect : le nombre de caractèristique d’un vecteur dans le fichier (nombre de ligne) de type int.
– Sortie : retourne un pointeur sur un tableau de réel de type double** à deux dimensions allouer
dynamiquement.
*/
double ** createTable(char * monFichier, int n, int m);


/*
init_listIndex :
– Entrée : newIndex : un pointeur sur une structure listIndex.
– Sortie : initialise la structure listIndex (voir ci-dessous).
*/
void init_listIndex(listIndex * newIndex);

/**

findIndexSubSequence :
– Entrée :
– table : un tableau de réel de dimention 1 de type double *.
– sizeHeight : la taille du tableau de type int.
– seuil : le seuil de type double utilisé afin de trouver les index des minimums du tableau.
– Sortie : une structure de type listIndex qui contient les index des minimums du tableau (voir-ci
dessous).

*/

listIndex * findIndexSubSequence(double * table, int sizeHeight, double seuil);


/*

resultat :
– Entrée :
– A : un tableau de réel de une dimensions de type double*.
– P : un tableau de réel de deux dimensions de type double**.
– tailleREf : le nombre de colonne du tableau ref de type int.
– tailleTest : le nombre de colonne du tableau test de typeint.
– fichierResultat : la chaine de caractère de type char* qui contient le chemin vers le fichier resultat.
– fichierMatriceP : la chaine de caractère de type char* qui contient le chemin vers le fichier matrice
P.
– seuil : le seuilde type double utilisé par l’algorithme afin de trouver les index des minimums.
– Sortie : écris la matrice A dans la le fichier résultats et écrit la matrice P dans le fichier matrice P.

*/
void resultat(double * A, double ** P, int tailleTest, int tailleRef, char * fichierResultat, char * fichierMatriceP, double seuil);

#endif
