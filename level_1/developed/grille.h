#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/** \struct grille
 */
typedef struct {
	int nbl; /**< number of lines*/
	int nbc; /**< number of columns */
	int** cellules; /**< array (of size nbl) of arrays (of size nbc) of cells 
*/
} grille;
 
/** 
 * \brief allocates cells in a grille and initializes all cells to "dead 
"
 * \relatesalso grille
 * \param l number of lines
 * \param c number of columns
 * \param g pointer to grille 
 */
void alloue_grille (int l, int c, grille* g);

/** 
 * \brief frees cells from a grille 
 * \relatesalso grille
 * \param g pointer to grille 

 */
void libere_grille (grille* g);

/** 
 * \brief allocates and initializes cells of a grille from a file 

 * \relatesalso grille
 * \param filename file name
 * \param g 
 */
void init_grille_from_file (char * filename, grille* g);

/** 
 * \brief makes the cell (i, j) of the grille g alive
 * \param i cell row index 
 * \param j cell column index 
 * \param g 
 * \pre i < g.nbl
 * \pre j < g.nbc
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/** 
 * \brief makes the cell (i, j) of the grille g alive
 * \param i cell row index 
 * \param j cell column index 
 * \param g 
 * \pre i < g.nbl
 * \pre j < g.nbc
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/** 
 * \brief tests if cell (i, j) of grille g is alive 
 * \param i cell row index 
 * \param j cell column index 
 * \param g 
 * \pre i < g.nbl
 * \pre j < g.nbc
 */

static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}

/** 
 * \brief copy a grille (without allocation) 
 * \relatesalso grille
 * \param gs grille source
 * \param gd grille destination
 * \pre \b gs and \b gd are allocated and have the same size 

 */
void copie_grille (grille gs, grille gd);

#endif
