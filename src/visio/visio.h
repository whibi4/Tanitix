#ifndef VISIO_H
#define VISIO_H
#include <iostream>
#include <gtk/gtk.h>

#include "space.h"
using namespace std;

class Visio
{
public:
    Visio(SpaceManger* spaceManager);
    ~Visio();

    int run(int argc, char **argv);

private:
    GtkApplication*  _app;
    GtkWidget*       _drawing_area;
    SpaceManger*     _spaceManager;

    static void on_activate(GtkApplication *app, gpointer user_data);
    static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
    static gboolean on_timeout(gpointer user_data);
};
#endif //VISIO_H