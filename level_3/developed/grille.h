/** \file grille.h
 * \brief grille management (header)
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/** \struct grille
 */
typedef struct {
	int nbl; /**< number of lines */
	int nbc; /**< numbe of columns */
	int** cellules; /** array (of size nbl) of arrays (of size nbc) of cells*/
} grille;
 
/** 
 * \brief allocates cells in a grid and initializes all cells to "dead" 

 * \relatesalso grille
 * \param l number of lines 
 * \param c number of columns
 * \param g pointer to grid
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
 * \param g pointeur vers la grille
 */
void init_grille_from_file (char * filename, grille* g);

/** 
 * \brief makes the cell (i, j) of the grid g alive
 * \param i cell row index 
 * \param j cell column index
 * \param g grille
 * \pre i < g.nbl
 * \pre j < g.nbc
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/** 
 * \brief makes dead cell (i, j) of grid g
 * \param i cell row index
 * \param j cell column index
 * \param g grille
 * \pre i < g.nbl
 * \pre j < g.nbc
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/** 
 * \brief makes cell (i, j) of grid g non-viable
 * \param i cell row index
 * \param j cell column index
 * \param g grille
 * \pre i < g.nbl
 * \pre j < g.nbc
 */
static inline void set_nonviable(int i, int j, grille g){g.cellules[i][j] = -1;} // developed

/** 
 * \brief tests if cell (i, j) of grille g is alive
 * \param i cell row index
 * \param j cell column index
 * \param g grille
 * \return integer (boolean) is equal to 1 if the cell is alive, 0 otherwise 

 * \pre i < g.nbl
 * \pre j < g.nbc
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] > 0;}

/** 
 * \brief tests if cell (i, j) of grid g is viable
 * \param i cell row index
 * \param j cell column index
 * \param g grille
 * \return integer (boolean) is equal to 1 if the cell is alive, 0 otherwise 

 * \pre i < g.nbl
 * \pre j < g.nbc
 */
static inline int est_viable(int i, int j, grille g){return g.cellules[i][j] >= 0;} // CORRECTION

/** 
 * \brief update cell (i, j): continue to live without aging
 * \param i cell row index
 * \param j cell column index
 * \param g grille
 * \pre i < g.nbl
 * \pre j < g.nbc
 */
void set_ne_viellit_pas(int i, int j, grille g); 

/** 
 * \brief update cell (i, j): age 1, and die if its age exceeds 8
* \param i cell row index
 * \param j cell column index
 * \param g grille
 * \pre i < g.nbl
 * \pre j < g.nbc
 */
void set_viellit(int i, int j, grille g); 

/** 
 * \brief copy a grille (without allocation)
 * \relatesalso grille
 * \param gs grille source
 * \param gd grille destination
 * \pre \ b gs and \ b gd are allocated and have the same size
 */
void copie_grille (grille gs, grille gd);

#endif
