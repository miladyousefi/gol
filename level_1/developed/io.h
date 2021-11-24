/** \file io.h
 * \brief entrees / sorties (header)
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/** 
 * \brief horizontal line display 
 * \param c number of columns 

 */
void affiche_trait (int c);

/** 
 * \brief display of a grid line 
 * \param c number of columns 
 * \param ligne row in a grid (pointer) 
 */
void affiche_ligne (int c, int* ligne);


void affiche_grille (grille g);


void efface_grille (grille g);

void debut_jeu(grille *g, grille *gc);

#endif
