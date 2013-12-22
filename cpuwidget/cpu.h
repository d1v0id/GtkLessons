#ifndef __CPU_H
#define __CPU_H

#include <gtk/gtk.h>
#include <cairo.h>

G_BEGIN_DECLS

#define GTK_CPU(obj) GTK_CHECK_CAST(obj, gtk_cpu_get_type (), GtkCpu)
#define GTK_CPU_CLASS(klass) GTK_CHECK_CLASS_CAST(klass, gtk_cpu_get_type(), GtkCpuClass)
#define GTK_IS_CPU(obj) GTK_CHECK_TYPE(obj, gtk_cpu_get_type())

typedef struct _GtkCpu GtkCpu;
typedef struct _GtkCpuClass GtkCpuClass;

struct _GtkCpu {
    GtkWidget widget;
    gint sel;
};

struct _GtkCpuClass {
    GtkWidgetClass parent_class;
};

GtkType gtk_cpu_get_type(void);
void gtk_cpu_set_sel(GtkCpu *cpu, gint sel);
GtkWidget *gtk_cpu_new();

G_END_DECLS

#endif
