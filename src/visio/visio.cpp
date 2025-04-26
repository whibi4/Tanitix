#include "visio.h"
#include "drawableObject.h"
#include "physicalObject.h"
#include "space.h"
namespace VisoUtils {
    void drawFromDrawable(cairo_t* cr, DrawableObject* drawableObject) {
        auto [r, g, b] = drawableObject->getRGB();
        cairo_set_source_rgb(cr, r, g, b);
        cairo_arc(cr, drawableObject->getPosition()._x, drawableObject->getPosition()._y, drawableObject->getRadius(), 0, 2 * G_PI);
        cairo_fill(cr);
    }
}

Visio::Visio(SpaceManger* spaceManager) : _spaceManager(spaceManager) {
    _app = gtk_application_new("tanitix.gui.physics2d", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(_app, "activate", G_CALLBACK(Visio::on_activate), this);
}

Visio::~Visio() {
    g_object_unref(_app);
}

int Visio::run(int argc, char** argv) {
    return g_application_run(G_APPLICATION(_app), argc, argv);
}

void Visio::on_activate(GtkApplication* app, gpointer user_data) {
    Visio* self = static_cast<Visio*>(user_data);
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Tanitix");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    self->_drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(self->_drawing_area, TRUE);
    gtk_widget_set_vexpand(self->_drawing_area, TRUE);
    g_signal_connect(G_OBJECT(self->_drawing_area), "draw", G_CALLBACK(Visio::on_draw), self);
    gtk_container_add(GTK_CONTAINER(window), self->_drawing_area);
    gtk_widget_show_all(window);

    g_timeout_add(16, Visio::on_timeout, self);
}

gboolean Visio::on_draw(GtkWidget* widget, cairo_t* cr, gpointer user_data) {
    Visio* self = static_cast<Visio*>(user_data);
    SpaceManger* spaceManager = self->_spaceManager;

    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);

    // Draw background
    cairo_set_source_rgb(cr, 1, 1, 1);  // White
    cairo_paint(cr);

     // Draw each circle
     for (auto& drawableObject : spaceManager->getSpaceScene()) {
        VisoUtils::drawFromDrawable(cr, drawableObject);
    }
    return FALSE;
}

gboolean Visio::on_timeout(gpointer user_data) {
    Visio* self = static_cast<Visio*>(user_data);

    GtkAllocation alloc;
    gtk_widget_get_allocation(self->_drawing_area, &alloc);

    self->_spaceManager->update(Time<double>(16.0, false));    

    // Redraw
    gtk_widget_queue_draw(self->_drawing_area);

    return TRUE; // keep the timeout
}