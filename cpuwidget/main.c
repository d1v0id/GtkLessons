#include "cpu.h"

static void set_value(GtkWidget *widget, gpointer data)
{
    GdkRegion *region;

    GtkRange *range = (GtkRange *)widget;
    GtkWidget *cpu = (GtkWidget *)data;
    GTK_CPU(cpu)->sel = gtk_range_get_value(range);

    region = gdk_drawable_get_clip_region(cpu->window);
    gdk_window_invalidate_region(cpu->window, region, TRUE);
    gdk_window_process_updates(cpu->window, TRUE);
}

int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkWidget *cpu;
    GtkWidget *fixed;
    GtkWidget *scale;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "CPU widget");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 180);

    g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    cpu = gtk_cpu_new();
    gtk_fixed_put(GTK_FIXED(fixed), cpu, 30, 40);

    scale = gtk_vscale_new_with_range(0.0, 100.0, 1.0);
    gtk_range_set_inverted(GTK_RANGE(scale), TRUE);
    gtk_scale_set_value_pos(GTK_SCALE(scale), GTK_POS_TOP);
    gtk_widget_set_size_request(scale, 50, 120);
    gtk_fixed_put(GTK_FIXED(fixed), scale, 130, 20);

    g_signal_connect(G_OBJECT(scale), "value_changed",
        G_CALLBACK(set_value), (gpointer) cpu);

    gtk_widget_show(cpu);
    gtk_widget_show(fixed);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
