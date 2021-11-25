/** \file io.h
 * \brief inputs / outputs (header) 

 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/** 
 * \brief horizontal line display (text mode) 
 * \param c numbe of columns 
 */
void affiche_trait (int c);

/** 
 * \brief display of a grille line (text mode)
 * \param c number of columns
 * \param ligne row in a grille (pointer)
 */
void affiche_ligne (int c, int* ligne);

/** 
 * \brief display of a grid (text mode)
 * \relatesalso grille
 * \param g grille to display
 */
void affiche_grille (grille g);

/** 
 * \brief deleting a grille (text mode)
 * \relatesalso grille
 * \param g grille to display
 */
void efface_grille (grille g);

/** 
 * \brief start a game (text mode)
 * \param g grille game
 * \param gc buffer grid (necessary for the \ c function to evolve)
 */
void debut_jeu(grille *g, grille *gc);

#endif
