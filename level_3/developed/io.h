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
 * \brief display of a line of the grille
 * \param c number of columns
 * \param ligne row in a grille (pointer)
 */
void affiche_ligne (int c, int* ligne);

/** 
 * \brief display of a grille
 * \relatesalso grille
 * \param g grille to display
 */
void affiche_grille (grille g);

/** 
 * \brief deleting a grille
 * \relatesalso grille
 * \param g grille to clear
 */
void efface_grille (grille g);

/** 
 * \brief start a game
 * \param g grille 
 * \param gc grille buffer (necessary for the \ c function to evolve)
 */
void debut_jeu(grille *g, grille *gc);

#endif
