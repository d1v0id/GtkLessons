#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *label;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Nymphetamine");
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 400);

    label = gtk_label_new("Cold was my soul\n\
        Untold was the pain\n\
        I faced when you left me\n\
        A rose in the rain....\n\
        So I swore to the razor\n\
        That never, enchained\n\
        Would your dark nails of faith\n\
        Be pushed through my veins again\n\
        \n\
        Bared on your tomb\n\
        I'm a prayer for your loneliness\n\
        And would you ever soon\n\
        Come above onto me?\n\
        For once upon a time\n\
        On the binds of your lowliness\n\
        I could always find the slot for your sacred key ");

    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_container_add(GTK_CONTAINER(window), label);

    g_signal_connect_swapped(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
