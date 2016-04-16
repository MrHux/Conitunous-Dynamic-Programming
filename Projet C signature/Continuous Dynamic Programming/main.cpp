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

/*tout les fichiers utilis� par le programme sont � passer en param�tre lors de l'appel*/

int main(int argc, char* argv[])
{
	/* d�finition des matrices */

	double ** P;
	double * A;

	/*taille des matrices*/
	int nbEleVectRef;
	int nbEleVectTest;

	int tailleref = 0;
	int tailletest = 0;

	/*chemin vers le Fichier de requ�te*/
	char * fichierTest = argv[1];

	/*on extrait les donn�es*/
	TableSize dimTest = countFileSize(fichierTest);
	tailletest = dimTest.nbColonne;
	nbEleVectTest = dimTest.nbLigne;


	/*d�claration du pointeur vers le fichier r�ference*/
	double ** test = createTable(fichierTest, tailletest, nbEleVectTest);

	/*chemin vers le fichier S�quence de ressource*/
	char * fichierRef = argv[2];

	/*on extrait les donn�es*/
	TableSize dimRef = countFileSize(fichierRef);
	tailleref = dimRef.nbColonne;
	nbEleVectRef = dimRef.nbLigne;


	/*d�claration du pointeur vers le fichier test*/
	double ** reference = createTable(fichierRef, tailleref, nbEleVectRef);

	int nbEleVect;

	if (nbEleVectTest == nbEleVectRef) {
		nbEleVect = nbEleVectRef;
	}
	else {
		printf("Erreur ! Les Fichiers de R�f�rence et de Test ont des vecteurs de longueurs diff�rentes !");
		return 0;
	}

	/*si les fichier sont vide on affiche une erreur*/
	if (test == NULL || reference == NULL) {
		printf("test ou ref == NULL");
		return 0;
	}
	else
	{

		P = cdp(reference, test, tailleref, tailletest, nbEleVect);

		A = resultatA(P, tailleref, tailletest, nbEleVect);


		//affichetout(A,P,tailletest,tailleref,nbEleVect ,test,reference);

		printf("\n \n rentrer le seuil \n \n");
		double seuil = 0;
		scanf("%lf", &seuil);

		/*r�cup�ration des chemins vers les fichiers de sortie*/

		/*fichierResultat contiendra la matrice A et les index*/
		char * fichierResultat = argv[3];

		/*fichierMatriceP contiendra la matriceP*/
		char * fichierMatriceP = argv[4];

		resultat(A, P, tailleref, tailletest, fichierResultat, fichierMatriceP, seuil);

		/*lib�ration des pointeurs*/

		free(reference);
		free(test);
		free(P);
		free(A);


	}
	return 0;
}
