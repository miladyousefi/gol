/** \file io.c
 * \brief entrees / sorties (code source)
 */

#include "../include/io_texte.h"

/** \brief defined in jeu.c*/
extern int (*compte_voisins_vivants) (int, int, grille); 
/** \brief defined in jeu.c*/
extern void (*set_continue_vie) (int, int, grille); 
/** \brief counting of the passing time: static global variable: only known in io.c*/
static int temps = 0;
/** \brief period of oscillation of the colony: 0 for non-oscillating, 1 and + for oscillating */
static int periode = 0;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); 
		else if (ligne[i] == -1) printf ("| X "); 
		else printf ("| %d ",ligne[i]); 
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("temps t = %d\n", temps); 
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 6); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // 'q' for quit
	{ 
		switch (c) {
			case '\n' : 
			{ // enter for countinue
				evolue(g,gc);
				temps++; 
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'c' : 
			{ // key "c" to activate / deactivate the cyclic neighborhood
				if (compte_voisins_vivants == compte_voisins_cyclique){
					compte_voisins_vivants = compte_voisins_non_cyclique;
					printf("voisinage non cyclique    \n");
				}
				else {
					compte_voisins_vivants = compte_voisins_cyclique;
					printf("voisinage cyclique      \n");
				}
				
				while(getchar() != '\n');
				printf("\n\e[%dA",3); 
				break;
			}
			case 'v' : 
			{ // "v" key to activate / deactivate cell aging
				if (set_continue_vie == set_ne_viellit_pas){
					set_continue_vie = set_viellit;
					printf("viellissement ON     \n");
				}
				else {
					set_continue_vie = set_ne_viellit_pas;
					printf("viellissement OFF    \n");
				}
				while(getchar() != '\n');
				printf("\n\e[%dA",3); 
				break;
			}
			case 'o' :
			{ // test if the colony is oscillating
				periode = cherche_oscillation(g,100);
				if (periode==0) printf("Colonie non-oscillante    \n");
				else printf("Colonie oscillante (période : %d)\n",periode);
				while(getchar() != '\n');
				printf("\n\e[%dA",3); 
				break;
			}
			default : 
			{ // key not processed
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
