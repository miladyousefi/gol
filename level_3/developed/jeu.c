/** \file jeu.c
 * \brief game development algorithms (source code)
 */

#include "jeu.h"

/** \brief function pointer (count of the number of neighbors):
  * points to account_voisins_cyclique or account_voisins_non_cyclique (according to the current rule)
 */
int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_non_cyclique ;
/** \brief function pointer (updates a living cell):
  * points to set_viellit or to set_ne_viellit_pas (depending on the current rule) 
 */
void (*set_continue_vie)(int,int,grille) = set_ne_viellit_pas ; 

int compte_voisins_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_non_cyclique (int i, int j, grille g){ 
	int v = 0, l=g.nbl, c = g.nbc;
	if (i>0) { // neighbors to the left
		if ( j > 0 ) v+= est_vivante(i-1,j-1,g);
		v+= est_vivante(i-1,j,g);
		if ( j < c-1) v+= est_vivante(i-1,j+1,g);
	}

	// neighbors up and down
	if ( j > 0 ) v+= est_vivante(i,j-1,g);
	if ( j < c-1) v+= est_vivante(i,j+1,g);

	if (i < l-1 ) { // neighbors on the right
		if ( j > 0 ) v+= est_vivante(i+1,j-1,g);
		v+= est_vivante(i+1,j,g);
		if ( j < c-1) v+= est_vivante(i+1,j+1,g);
	}
	
	return v; 
}

void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // temporary copy of the grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (est_viable(i,j,*g)){ // developed
				v = compte_voisins_vivants (i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution of a living cell
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
					else set_continue_vie(i,j,*g); 
				}
				else 
				{ // evolution of a dead cell
					if ( v==3 ) set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}
