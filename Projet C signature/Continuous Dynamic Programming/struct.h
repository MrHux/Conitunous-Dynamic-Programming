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
� Entr�e : x,y : deux r�els de type double.
� Sortie : retourne le minimum en type double.
*/

double min(double x, double y);


/*

distance :
� Entr�e :
� table1, table2 : deux tableaux de r�el � deux dimensions de type double **.
� indexTable1, indexTable2 : les index des colonnes de ces deux tableaux de type int.
� nbElement : le nombre d��l�ments dans chaque colonnes de ces tableaux de type int.
� Sortie : retourne la distance euclidienne entre les deux colonnes.

*/
double distance(double ** table1, double ** table2, int indexTable1, int indexTable2, int nbElement);

/*
cdp :
� Entr�e :
� reference, test : les tableaux des matrices r�f�rence et test de types double**.
� sizeRef : nombre de colonnes de la matrice r�f�rence de type int.
� sizeTest : nombre de colonnes de la matrice test de type int.
� nbEleVect : nombre de ligne des matrices test et r�f�rence de type int.
� Sortie : le tableau de type double** correspondant au cumule des distances entre la matrice test
et la matrice r�f�rence.


**/



double ** cdp(double ** test, double ** reference, int sizeTest, int sizeRef, int nbEleVect);


/*
resultatA :
� Entr�e :
� matriceP : le tableau de r�el de la matrice calcul� par CDP, de type double.
� sizeRef : nombre de colonne de la matrice P.
� sizeTest : nombre de ligne de la matrice P.
� Sortie : retourne un tableau de type double* qui correspond � la derni�re colonne de la matriceP
normalis�.


*/
double * resultatA(double** matriceP, int sizeTest, int sizeRef, int nbEleVect);

/*

countFileSize :
� Entr�e : monFichier : une chaine de caract�re de type char* qui contient un nom de fichier.csv
(contenant une matrice).
� Sortie : retourne la taille du fichier sous la forme d�une structure TableSize (voir-ci apr�s).
*/
TableSize countFileSize(char * monFichier);
/*
createTable :
� Entr�e :
� monFichier : une chaine de caract�re de type char* qui contient un nom du fichier.
� nbColonne : le nombre de colonne de vecteurs dans le fichier de type int.
� nbEleVect : le nombre de caract�ristique d�un vecteur dans le fichier (nombre de ligne) de type int.
� Sortie : retourne un pointeur sur un tableau de r�el de type double** � deux dimensions allouer
dynamiquement.
*/
double ** createTable(char * monFichier, int n, int m);


/*
init_listIndex :
� Entr�e : newIndex : un pointeur sur une structure listIndex.
� Sortie : initialise la structure listIndex (voir ci-dessous).
*/
void init_listIndex(listIndex * newIndex);

/**

findIndexSubSequence :
� Entr�e :
� table : un tableau de r�el de dimention 1 de type double *.
� sizeHeight : la taille du tableau de type int.
� seuil : le seuil de type double utilis� afin de trouver les index des minimums du tableau.
� Sortie : une structure de type listIndex qui contient les index des minimums du tableau (voir-ci
dessous).

*/

listIndex * findIndexSubSequence(double * table, int sizeHeight, double seuil);


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
void resultat(double * A, double ** P, int tailleTest, int tailleRef, char * fichierResultat, char * fichierMatriceP, double seuil);

#endif
