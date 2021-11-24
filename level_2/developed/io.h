/** \file io.h
 * \brief inputs / outputs (header) 
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

/** 
 * \brief display of a grille 
 * \relatesalso grille
 * \param g grille to display 
 */
void affiche_grille (grille g);

/** 
 * \brief effacement d'une grille
 * \relatesalso grille
 * \param g grille à effacer
 */
void efface_grille (grille g);

/** 
 * \brief start a game 
 * \param g game grille 
 * \param gc buffer grid (necessary for the \ c function to evolve)
 */
void debut_jeu(grille *g, grille *gc);

#endif
