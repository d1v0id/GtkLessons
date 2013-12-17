#include <gtk/gtk.h>

int handler_id;

void button_clicked(GtkWidget *widget, gpointer data)
{
    g_print("clicked\n");
}

void toogle_signal(GtkWidget *widget, gpointer window)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        handler_id = g_signal_connect(G_OBJECT(window), "clicked", G_CALLBACK(button_clicked), NULL);
    }
    else {
        g_signal_handler_disconnect(window, handler_id);
    }
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *button;
    GtkWidget *check;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 150);
    gtk_window_set_title(GTK_WINDOW(window), "Disconnect");

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    button = gtk_button_new_with_label("Click");
    gtk_widget_set_size_request(button, 80, 30);
    gtk_fixed_put(GTK_FIXED(fixed), button, 30, 50);

    check = gtk_check_button_new_with_label("Connect");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
    gtk_fixed_put(GTK_FIXED(fixed), check, 130, 50);

    handler_id = g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), NULL);

    g_signal_connect(G_OBJECT(check), "clicked", G_CALLBACK(toogle_signal), (gpointer)button);

    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
