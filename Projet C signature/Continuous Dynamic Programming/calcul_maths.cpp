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
* calcul du minimum entre deux entiers
* en entrée : deux entiers x et y
* en sortie : le minimum.
*/
double min(double x, double y) {
	if (x<y)return x;
	else return y;

}

/*
* calcul de la distance entre deux entiers situé dans deux tableaux
* en entrée : deux tableaux d'entier, i et j la position respective des entiers dans le tableau.
* en sortie : la distance entre les deux entiers.
*/
double distance(double ** table1, double ** table2, int indexTable1, int indexTable2, int nbElement) {

	double somme = 0;

	if (table1 == NULL || table2 == NULL) {
		printf("Erreur");
		return -1;
	}

	int k = 0; /*permet de parcourir les composante d'un vecteur*/

	for (k = 0; k<nbElement; k++) {
		somme = somme + (double)((table1[k][indexTable1] - table2[k][indexTable2])*(table1[k][indexTable1] - table2[k][indexTable2]));
	}

	return sqrt(somme);
}




