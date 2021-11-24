#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef struct {int nbl; int nbc; int** cellules;} grille;
 

void alloue_grille (int l, int c, grille* g);


void libere_grille (grille* g);

void init_grille_from_file (char * filename, grille* g);

static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}


void copie_grille (grille gs, grille gd);

#endif
