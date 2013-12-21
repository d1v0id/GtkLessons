#include <gtk/gtk.h>

void toggle_title(GtkWidget *widget, gpointer window)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        gtk_window_set_title(window, "GtkCheckButton");
    }
    else {
        gtk_window_set_title(window, "");
    }
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *frame;
    GtkWidget *check;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_title(GTK_WINDOW(window), "GtkCheckButton");

    frame = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), frame);

    check = gtk_check_button_new_with_label("Show title");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
    GTK_WIDGET_UNSET_FLAGS(check, GTK_CAN_FOCUS);
    gtk_fixed_put(GTK_FIXED(frame), check, 50, 50);

    g_signal_connect_swapped(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(check, "clicked",
        G_CALLBACK(toggle_title), (gpointer)window);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
