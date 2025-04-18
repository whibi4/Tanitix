#ifndef VISIO_H
#define VISIO_H
#include <iostream>
#include <gtk/gtk.h>

using namespace std;

class Visio
{
public:
    Visio();
    ~Visio();

    int run(int argc, char **argv);

private:
    GtkApplication *app;
    GtkWidget *drawing_area;

    //Circle state 
    double cx, cy;
    double dx;

    static void on_activate(GtkApplication *app, gpointer user_data);
    static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
    static gboolean on_timeout(gpointer user_data);
};
#endif //VISIO_H