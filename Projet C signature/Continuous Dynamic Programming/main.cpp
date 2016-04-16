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

/*tout les fichiers utilisé par le programme sont à passer en paramêtre lors de l'appel*/

int main(int argc, char* argv[])
{
	/* définition des matrices */

	double ** P;
	double * A;

	/*taille des matrices*/
	int nbEleVectRef;
	int nbEleVectTest;

	int tailleref = 0;
	int tailletest = 0;

	/*chemin vers le Fichier de requête*/
	char * fichierTest = argv[1];

	/*on extrait les données*/
	TableSize dimTest = countFileSize(fichierTest);
	tailletest = dimTest.nbColonne;
	nbEleVectTest = dimTest.nbLigne;


	/*déclaration du pointeur vers le fichier réference*/
	double ** test = createTable(fichierTest, tailletest, nbEleVectTest);

	/*chemin vers le fichier Séquence de ressource*/
	char * fichierRef = argv[2];

	/*on extrait les données*/
	TableSize dimRef = countFileSize(fichierRef);
	tailleref = dimRef.nbColonne;
	nbEleVectRef = dimRef.nbLigne;


	/*déclaration du pointeur vers le fichier test*/
	double ** reference = createTable(fichierRef, tailleref, nbEleVectRef);

	int nbEleVect;

	if (nbEleVectTest == nbEleVectRef) {
		nbEleVect = nbEleVectRef;
	}
	else {
		printf("Erreur ! Les Fichiers de Référence et de Test ont des vecteurs de longueurs différentes !");
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

		/*récupération des chemins vers les fichiers de sortie*/

		/*fichierResultat contiendra la matrice A et les index*/
		char * fichierResultat = argv[3];

		/*fichierMatriceP contiendra la matriceP*/
		char * fichierMatriceP = argv[4];

		resultat(A, P, tailleref, tailletest, fichierResultat, fichierMatriceP, seuil);

		/*libération des pointeurs*/

		free(reference);
		free(test);
		free(P);
		free(A);


	}
	return 0;
}
