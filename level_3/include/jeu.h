/** \file jeu.h
 * \brief game development algorithms (header)
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/** 
 * \brief modulo modified to correctly handle cyclic edges: 
 * \param i dividend
 * \param m divider
 * \return integer = \ b i modulo \ b m
 * \return particularity for edges: modulo (-1, m) returns (m-1)
 * \pre \b m > 0
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/** 
 * \brief counts the number of living neighbors of a cell (cyclic edges)
 * \relatesalso grille
 * \param i cell row index
 * \param j cell column index
 * \param g grille
 * \return integer = number of neighbors of (\ b i, \ b j) living in \ b g
 */
int compte_voisins_cyclique (int i, int j, grille g);

/** 
 * \brief counts the number of living neighbors of a cell (non-cyclic edges)
 * \relatesalso grille
 * \param i cell row index
 * \param j cell column index
 * \param g grille
 * \return integer = number of neighbors of (\ b i, \ b j) living in \ b g
 */
int compte_voisins_non_cyclique (int i, int j, grille g);

/** 
 * \brief make the \b g grid evolve by one time step
 * \relatesalso grille
 * \param g (pointer to) the evolving grid
 * \param gc (pointer to) the buffer grid
 * \pre \b g and \b gc are allocated and have the same size
 */
void evolue (grille *g, grille *gc);

/** 
 * \brief indicates whether a grid is oscillating or not
 * \relatesalso grille
 * \param g     the grid to be evaluated
 * \return an integer, the period of oscillation or 0
 */
int oscillante(grille g);


#endif
