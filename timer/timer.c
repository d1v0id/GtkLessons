#include <cairo.h>
#include <gtk/gtk.h>
#include <time.h>

static char buffer[256];

static gboolean on_expose_event(GtkWidget *widget, 
    GdkEventExpose *event, gpointer data)
{
    cairo_t *cr;

    cr = gdk_cairo_create(widget->window);

    cairo_move_to(cr, 30, 30);
    cairo_show_text(cr, buffer);

    cairo_destroy(cr);

    return FALSE;
}

static gboolean time_handler(GtkWidget *widget)
{
    if (widget->window == NULL) {
        return FALSE;
    }

    time_t curtime;
    struct tm *loctime;

    curtime = time(NULL);
    loctime = localtime(&curtime);
    strftime(buffer, 256, "%T", loctime);

    gtk_widget_queue_draw(widget);
    return TRUE;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *darea;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(darea, "expose-event",
        G_CALLBACK(on_expose_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 170, 100);

    gtk_window_set_title(GTK_WINDOW(window), "timer");
    g_timeout_add(1000, (GSourceFunc) time_handler, (gpointer)window);
    gtk_widget_show_all(window);
    time_handler(window);

    gtk_main();

    return 0;
}
