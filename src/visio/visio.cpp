#include "visio.h"
Visio::Visio() : cx(100), cy(150), dx(2.0) {
    app = gtk_application_new("com.example.Visio", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(Visio::on_activate), this);
}

Visio::~Visio() {
    g_object_unref(app);
}

int Visio::run(int argc, char** argv) {
    return g_application_run(G_APPLICATION(app), argc, argv);
}

void Visio::on_activate(GtkApplication* app, gpointer user_data) {
    Visio* self = static_cast<Visio*>(user_data);

    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Visio Animation");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    self->drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(self->drawing_area, TRUE);
    gtk_widget_set_vexpand(self->drawing_area, TRUE);
    g_signal_connect(G_OBJECT(self->drawing_area), "draw", G_CALLBACK(Visio::on_draw), self);

    gtk_container_add(GTK_CONTAINER(window), self->drawing_area);
    gtk_widget_show_all(window);

    // Start animation timer (16ms ≈ 60 FPS)
    g_timeout_add(16, Visio::on_timeout, self);
}

gboolean Visio::on_draw(GtkWidget* widget, cairo_t* cr, gpointer user_data) {
    Visio* self = static_cast<Visio*>(user_data);

    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);

    // Draw background
    cairo_set_source_rgb(cr, 1, 1, 1);  // White
    cairo_paint(cr);

    // Draw circle
    cairo_set_source_rgb(cr, 0.2, 0.6, 0.9);  // Blue
    cairo_arc(cr, self->cx, self->cy, 30.0, 0, 2 * G_PI);
    cairo_fill(cr);

    return FALSE;
}

gboolean Visio::on_timeout(gpointer user_data) {
    Visio* self = static_cast<Visio*>(user_data);

    GtkAllocation alloc;
    gtk_widget_get_allocation(self->drawing_area, &alloc);

    // Move circle
    self->cx += self->dx;

    // Bounce if hitting edges
    if (self->cx <= 30 || self->cx >= alloc.width - 30) {
        self->dx *= -1;
    }

    // Redraw
    gtk_widget_queue_draw(self->drawing_area);

    return TRUE; // keep the timeout
}