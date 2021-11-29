/** \file io.c
 * \brief management of inputs / outputs with cairo (source code)
 */
#define KRED  "\x1B[31m" // for printf color red
#define KGRN  "\x1B[32m" //for print color green
#include "../include/io.h"

/** \brief defined in jeu.c*/
extern int (*compte_voisins_vivants) (int, int, grille); 
/** \brief defined in jeu.c*/
extern void (*set_continue_vie) (int, int, grille); 
/** \brief counting of the passing time: static global variable: only known in io.c*/
static int temps = 0;

void paint(cairo_surface_t *surface, grille g, int periode){
	// variables
	int i,j;
	float abs, ord, lgr=SIZEX/g.nbc, lrg=SIZEY/g.nbl, age;
	char tps[6];
	char prd[6];
	char tmx[6];
	sprintf(tps,"%d",temps);
	sprintf(prd,"%d",periode);
	sprintf(tmx,"%d",TMAX);
	
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);
	
	// grille
	cairo_set_line_width(cr, 1.0);
	for (i=0; i<g.nbl; ++i){
		for (j=0; j<g.nbc; ++j){
			abs = lgr*j;
			ord = lrg*i;
			cairo_rectangle(cr, abs, ord, lgr, lrg);
			if (est_viable(i,j,g)){
				if (est_vivante(i,j,g)){
					age = 0.1 * g.cellules[i][j];
					cairo_set_source_rgb(cr, age, 0.8 - age, 0.2);
					cairo_fill(cr);
				}
				else{
					cairo_set_source_rgb(cr, 0.0, 0.0, 0.2);
					cairo_fill(cr);
				}
			}
			else{
				cairo_set_source_rgb(cr, 0.2, 0.5, 1.0);
				cairo_fill(cr);
			}
		}
	}
	
	// messages (surface)
	cairo_set_source_rgb (cr, 0.1, 0.1, 0.1);
	cairo_rectangle(cr, 0.0, SIZEY, SIZEX, 70);
	cairo_fill(cr);
	cairo_set_source_rgb (cr, 0.7, 0.7, 0.0);
	cairo_set_line_width(cr,2.0);
	cairo_rectangle(cr, 0.0, SIZEY, SIZEX, 70);
	cairo_stroke(cr);
	
	// temps
	cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
	cairo_set_font_size(cr, 16.0);
	cairo_move_to(cr, 5.0, SIZEY+15.0);
	cairo_show_text(cr, "temps : ");
	cairo_show_text(cr, tps);
	
	// voisinnage
	cairo_move_to(cr, 5.0, SIZEY+30.0);
	if (compte_voisins_vivants == compte_voisins_cyclique)
		cairo_show_text(cr, "voisinnage cyclique");
	else cairo_show_text(cr, "voisinnage non-cyclique");
	
	// vielillissement
	cairo_move_to(cr, 5.0, SIZEY+45.0);
	if (set_continue_vie == set_ne_viellit_pas)
		cairo_show_text(cr, "vieillissement OFF");
	else cairo_show_text(cr, "vieillissement ON");
	
	// oscillation
	cairo_move_to(cr, 5.0, SIZEY+60.0);
	if (periode<0){
		cairo_show_text(cr, "pas d'oscillation en moins de ");
		cairo_show_text(cr, tmx);
		cairo_show_text(cr, " pas de temps");
	}
	else{
		cairo_show_text(cr, "oscillation : periode de ");
		cairo_show_text(cr, prd);
		cairo_show_text(cr, " pas de temps");
	}	
	
	// destroy cairo mask
	cairo_destroy(cr); 
	
	return;
}

void debut_jeu(grille* g, grille* gc, Display* dpy, cairo_surface_t *cs){
	grille greset;
	alloue_grille(g->nbl, g->nbc, &greset);
	copie_grille(*g,greset);
	XEvent e;
	FILE * pfile = NULL;
	float lgrCase = (SIZEX/g->nbc);
	float lrgCase = (SIZEY/g->nbl);
	int i,j;
	int k,l;
	int count_life;
	int count_nonviable;
	char* touche;
	int periode=-1;
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1){
			paint(cs, *g, periode);
		}
		else if(e.type==ButtonPress){
			if(e.xbutton.button==3) break;
			else if (e.xbutton.button==1){
				j=e.xbutton.x/lrgCase;
				i=e.xbutton.y/lgrCase;
				if (i>=0 && i<g->nbl && j>=0 && j<g->nbc){
					if (est_vivante(i,j,*g)) set_nonviable(i,j,*g);
					else if (!est_viable(i,j,*g)) set_morte(i,j,*g);
					else set_vivante(i,j,*g);
					paint(cs,*g, periode);
				}
			}
		}
		else if (e.type==KeyPress){
			touche = XKeysymToString(XkbKeycodeToKeysym(dpy, e.xkey.keycode, 0, 0));
			switch(touche[0]){
				case 'v' : // vieillissement ON/OFF
					if (set_continue_vie == set_ne_viellit_pas)
						set_continue_vie = set_viellit;
					else set_continue_vie = set_ne_viellit_pas;
					
					
					paint(cs,*g, periode);
					break;
					
				case 'c' : // voisinnage cyclique/non-cyclique
					if (compte_voisins_vivants == compte_voisins_cyclique)
						compte_voisins_vivants = compte_voisins_non_cyclique;
					else compte_voisins_vivants = compte_voisins_cyclique;
					paint(cs,*g, periode);
					break;
					
				case 'o' : // oscillation test
					periode = cherche_oscillation(g,TMAX);
					paint(cs,*g, periode);
					break;
					
				case 'e' : // evolution
					evolue(g, gc);
					temps++; 
					paint(cs,*g, periode);
					break;
					
				case 'k' : // kill living cells
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (!(!est_vivante(i,j,*g))) set_morte(i,j,*g);
						}
					}
					paint(cs,*g, periode);
					break;
					
				case 'd' : // destroy non-viable cells
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (!est_viable(i,j,*g)) set_morte(i,j,*g);
						}
					}
					paint(cs,*g, periode);
					break;
					
				case 'l' : // give life to dead cells
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (!est_vivante(i,j,*g) && est_viable(i,j,*g)) set_vivante(i,j,*g);
						}
					}
					paint(cs,*g, periode);
					break;
					
				case 't' : // give life to non-viable cells
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (!est_viable(i,j,*g)) set_vivante(i,j,*g);
						}
					}
					paint(cs,*g, periode);
					break;
					
				case 'r' : // reset curently grille
					copie_grille(greset, *g);
					temps=0;
					paint(cs,*g, periode);
					break;
					
				case 'i' : // inversion of dead / living cells
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (est_vivante(i,j,*g)) set_morte(i,j,*g);
							else if (!est_vivante(i,j,*g) && est_viable(i,j,*g)) set_vivante(i,j,*g);
						}
					}
					paint(cs,*g, periode);
					break;
					
				case 'y' : // inversion of non-viable / living cells
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (est_vivante(i,j,*g)) set_nonviable(i,j,*g);
							else if (!est_viable(i,j,*g)) set_vivante(i,j,*g);
						}
					}
					paint(cs,*g, periode);
					break;
					
				case 'a' : // save grille configuration file
					count_life=0;
					count_nonviable=0;
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (est_vivante(i,j,*g)) count_life++;
							else if (!est_viable(i,j,*g)) count_nonviable++;
						}
					}
					pfile = fopen("../../grilles/saved.txt", "w");
					assert (pfile != NULL);
					
					fprintf(pfile, "%d %d\n\n", g->nbl, g->nbc);
					fprintf(pfile, "%d\n", count_life);
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (est_vivante(i,j,*g)) fprintf(pfile, "%d %d\n", i, j);
						}
					}
					fprintf(pfile, "\n%d\n", count_nonviable);
					for (i=0; i<g->nbl; i++){
						for (j=0; j<g->nbc; j++){
							if (!est_viable(i,j,*g)) fprintf(pfile, "%d %d\n", i, j);
						}
					}
					
					fclose (pfile);
					break;
					
				case 'w' : // draw a line of living cells
					XNextEvent(dpy, &e);
					if(e.type==ButtonPress){
						//~ j=e.xbutton.x/lrgCase;
						i=e.xbutton.y/lgrCase;
						if (i>=0 && i<g->nbl){ // && j>=0 && j<g->nbc
							if(e.xbutton.button==3){ // draw and invert the cells
								for (j=0; j<g->nbc; j++){
									if (est_vivante(i,j,*g)) set_morte(i,j,*g);
									else if (!est_vivante(i,j,*g) && est_viable(i,j,*g)) set_vivante(i,j,*g);
								}
							}
							else if (e.xbutton.button==1){ // draw without inverting
								for (j=0; j<g->nbc; j++){
									if (est_viable(i,j,*g)) set_vivante(i,j,*g);
								}
							}
							paint(cs,*g, periode);
						}
					}
					break;
					
				case 'x' : // draw a column of living cells
					XNextEvent(dpy, &e);
					if(e.type==ButtonPress){
						j=e.xbutton.x/lrgCase;
						//~ i=e.xbutton.y/lgrCase;
						if (j>=0 && j<g->nbc){ // && i>=0 && i<g->nbl
							if(e.xbutton.button==3){ // draw and invert the cells
								for (i=0; i<g->nbl; i++){
									if (est_vivante(i,j,*g)) set_morte(i,j,*g);
									else if (!est_vivante(i,j,*g) && est_viable(i,j,*g)) set_vivante(i,j,*g);
								}
							}
							else if (e.xbutton.button==1){ // draw without inverting
								for (i=0; i<g->nbl; i++){
									if (est_viable(i,j,*g)) set_vivante(i,j,*g);
								}
							}
							paint(cs,*g, periode);
						}
					}
					break;
					
				case 'q' : //quit
					printf("%s******************************\n",KRED);
					printf("%s*************     ************\n",KRED);
					printf("%s------------ Ended -----------\n",KRED);
					printf("%s************       ***********\n",KRED);
					return;
					
				case 's' : // draw a right diagonal of living cells
					XNextEvent(dpy, &e);
					if(e.type==ButtonPress){
						l=e.xbutton.x/lrgCase;
						k=e.xbutton.y/lgrCase;
						if (l>=0 && l<g->nbc && k>=0 && k<g->nbl){
							if(e.xbutton.button==3){ // draw and invert the cells
								j=l;
								for (i=k; i<g->nbl; i++){
									if (est_vivante(i,j,*g)) set_morte(i,j,*g);
									else if (!est_vivante(i,j,*g) && est_viable(i,j,*g)) set_vivante(i,j,*g);
									j++;
									if (j>=g->nbc) break;
								}
								j=l-1;
								for (i=k-1; i>=0; i--){
									if (est_vivante(i,j,*g)) set_morte(i,j,*g);
									else if (!est_vivante(i,j,*g) && est_viable(i,j,*g)) set_vivante(i,j,*g);
									j--;
									if (j<0) break;
								}
							}
							else if (e.xbutton.button==1){ // draw without inverting
								j=l;
								for (i=k; i<g->nbl; i++){
									if (est_viable(i,j,*g)) set_vivante(i,j,*g);
									j++;
									if (j>=g->nbc) break;
								}
								j=l-1;
								for (i=k-1; i>=0; i--){
									if (est_viable(i,j,*g)) set_vivante(i,j,*g);
									j--;
									if (j<0) break;
								}
							}
							paint(cs,*g, periode);
						}
					}
					break;
					
				case 'm' : // draw the center box
					i=g->nbl/2;
					j=g->nbc/2;
					if (est_vivante(i,j,*g)) set_nonviable(i,j,*g);
					else if (!est_viable(i,j,*g)) set_morte(i,j,*g);
					else set_vivante(i,j,*g);
					if (g->nbl%2==0 && g->nbc%2==0){
						if (est_vivante(i-1,j-1,*g)) set_nonviable(i-1,j-1,*g);
						else if (!est_viable(i-1,j-1,*g)) set_morte(i-1,j-1,*g);
						else set_vivante(i-1,j-1,*g);
						if (est_vivante(i-1,j,*g)) set_nonviable(i-1,j,*g);
						else if (!est_viable(i-1,j,*g)) set_morte(i-1,j,*g);
						else set_vivante(i-1,j,*g);
						if (est_vivante(i,j-1,*g)) set_nonviable(i,j-1,*g);
						else if (!est_viable(i,j-1,*g)) set_morte(i,j-1,*g);
						else set_vivante(i,j-1,*g);
					}
					else if (g->nbl%2==0){
						if (est_vivante(i-1,j,*g)) set_nonviable(i-1,j,*g);
						else if (!est_viable(i-1,j,*g)) set_morte(i-1,j,*g);
						else set_vivante(i-1,j,*g);
					}
					else if (g->nbc%2==0){
						if (est_vivante(i,j-1,*g)) set_nonviable(i,j-1,*g);
						else if (!est_viable(i,j-1,*g)) set_morte(i,j-1,*g);
						else set_vivante(i,j-1,*g);
					}
					paint(cs,*g, periode);
					break;
					
				case 'n' : // reset the grille to the starting situation
					printf("%s******************************\n",KGRN);
					printf("%s*************     ************\n",KGRN);
					printf("%s--    Enter a new grille  ----\n",KGRN);
					printf("%s************       ***********\n",KGRN);
					return;
					
				default :
					break;
			}
		}
	}
	return;
}
