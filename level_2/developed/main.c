/** \file main.c
 * \brief program running in a console:
  * load a grille and start the game 
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

/** 
 * \brief initialization and start of the game 
 * \param argc number of shell arguments 
 * \param argv shell arguments array 
 */
int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <file grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
