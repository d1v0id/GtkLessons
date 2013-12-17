#include <gtk/gtk.h>

void frame_callback(GtkWindow *window, GdkEvent *event, gpointer data)
{
    int x, y;
    char buf[10];
    x = event->configure.x;
    y = event->configure.y;
    sprintf(buf, "%d, %d", x, y);
    gtk_window_set_title(window, buf);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_title(GTK_WINDOW(window), "Moving Simple");
    gtk_widget_add_events(GTK_WIDGET(window), GDK_CONFIGURE);

    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    g_signal_connect(G_OBJECT(window), "configure-event", G_CALLBACK(frame_callback), NULL);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}
