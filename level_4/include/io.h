/** \file io.h
 * \brief management of inputs / outputs with cairo (header)
 */

#ifndef __IO_H
#define __IO_H
#define XK_LATIN1

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>
#include "grille.h"
#include "jeu.h"

#define SIZEX 640
#define SIZEY 640

#define TMAX 1000

/** 
 * \brief display of a grille (graphics mode)
 * \relatesalso grille
 * \param surface cairo surface to paint
 * \param g grid to display
 * \param periode grid at period of oscillation of the grille
 */
void paint(cairo_surface_t *surface, grille g, int periode);

/** 
 * \brief mode graphique
 * \param g grille game
 * \param gc grille buffer 
 * \param dpy display X11 
 * \param cs cairo surface to paint
 */
void debut_jeu(grille* g, grille* gc, Display* dpy, cairo_surface_t *cs);

#endif
