#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkButton");
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    button = gtk_button_new_with_label("Quit");

    gtk_fixed_put(GTK_FIXED(fixed), button, 50, 50);
    gtk_widget_set_size_request(button, 80, 35);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
