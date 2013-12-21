#include <gtk/gtk.h>

void button_pressed(GtkWidget *widget, gpointer window)
{
    gchar *str;
    str = g_strdup_printf("Button %s clicked",
        gtk_button_get_label(GTK_BUTTON(widget)));

    gtk_statusbar_push(GTK_STATUSBAR(window),
        gtk_statusbar_get_context_id(GTK_STATUSBAR(window), str), str);
    g_free(str);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *statusbar;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 280, 150);
    gtk_window_set_title(GTK_WINDOW(window), "GtkStatusbar");

    vbox = gtk_vbox_new(FALSE, 2);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_box_pack_start(GTK_BOX(vbox), fixed, TRUE, TRUE, 1);

    button1 = gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(button1, 80, 30);
    button2 = gtk_button_new_with_label("Apply");
    gtk_widget_set_size_request(button2, 80, 30);

    gtk_fixed_put(GTK_FIXED(fixed), button1, 50, 50);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 150, 50);

    statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);

    g_signal_connect(G_OBJECT(button1), "clicked",
        G_CALLBACK(button_pressed), G_OBJECT(statusbar));

    g_signal_connect(G_OBJECT(button2), "clicked",
        G_CALLBACK(button_pressed), G_OBJECT(statusbar));

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
