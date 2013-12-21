#include <gtk/gtk.h>

void combo_selected(GtkWidget *widget, gpointer window)
{
    gchar *text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
    gtk_label_set_text(GTK_LABEL(window), text);
    g_free(text);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *combo;
    GtkWidget *label;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkCombo");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);

    fixed = gtk_fixed_new();

    combo = gtk_combo_box_new_text();
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Debian");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Ubuntu");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Mandriva");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Fedora");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Mint");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Gentoo");

    gtk_fixed_put(GTK_FIXED(fixed), combo, 50, 50);
    gtk_container_add(GTK_CONTAINER(window), fixed);

    label = gtk_label_new(".");
    gtk_fixed_put(GTK_FIXED(fixed), label, 50, 110);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    g_signal_connect(G_OBJECT(combo), "changed",
        G_CALLBACK(combo_selected), (gpointer)label);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
