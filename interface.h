#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static GtkWidget *scale_SWS;
static GtkWidget *scale_preFiltCap;
static GtkWidget *scale_minDisp;
static GtkWidget *scale_numOfDisp;
static GtkWidget *scale_TxtrThrshld;
static GtkWidget *scale_unicRatio;
static GtkWidget *scale_SpcklRng;
static GtkWidget *scale_SpklWinSze;

int SWS = 7; 
int preFiltCap = 40;
int minDisp = 4;
int numOfDisp = 128;
int TxtrThrshld = 10;
int unicRatio = 10;
int SpcklRng = 16;
int SpklWinSze = 45;

void do_calculate(GtkWidget *calculate, gpointer data) {
    SWS = gtk_scale_get_digits((GtkScale*) scale_SWS);
    preFiltCap =  gtk_scale_get_digits((GtkScale*) scale_preFiltCap);
    minDisp =  gtk_scale_get_digits((GtkScale*) scale_minDisp);
    numOfDisp =  gtk_scale_get_digits((GtkScale*) scale_numOfDisp);
    TxtrThrshld =  gtk_scale_get_digits((GtkScale*) scale_TxtrThrshld);
    unicRatio =  gtk_scale_get_digits((GtkScale*) scale_unicRatio);
    SpcklRng =  gtk_scale_get_digits((GtkScale*) scale_SpcklRng);
    SpklWinSze =  gtk_scale_get_digits((GtkScale*) scale_SpklWinSze);
}

// gcc 007_gtk.c -o 007_gtk `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
    GtkWidget *window, *grid, *calculate;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid); // Configura a grid

    // Daqui pra baixo add os sliders
    scale_SWS = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 3, 21, 2);
    gtk_grid_attach(GTK_GRID(grid), scale_SWS, 1, 1, 10, 1);

    scale_preFiltCap = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_preFiltCap, 1, 3, 10, 1);

    scale_minDisp = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,-100, 100, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_minDisp, 1, 5, 10, 1);

    scale_numOfDisp = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 500, 16);
    gtk_grid_attach(GTK_GRID(grid), scale_numOfDisp, 1, 7, 7, 1);

    scale_TxtrThrshld = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 500, 5);
    gtk_grid_attach(GTK_GRID(grid), scale_TxtrThrshld, 1, 9, 5, 1);

    scale_unicRatio = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 10, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_unicRatio, 1, 11, 10, 1);

    scale_SpcklRng = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 20, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_SpcklRng, 1, 13, 10, 1);

    scale_SpklWinSze = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 10, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_SpklWinSze, 1, 15, 10, 1);

    calculate = gtk_button_new_with_label("Ogh Yah");
    g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate), NULL);
    gtk_grid_attach(GTK_GRID(grid), calculate, 1, 17, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}