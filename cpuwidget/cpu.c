#include "cpu.h"

static void gtk_cpu_class_init(GtkCpuClass *klass);
static void gtk_cpu_init(GtkCpu *cpu);
static void gtk_cpu_size_request(GtkWidget *widget,
    GtkRequisition *requisition);
static void gtk_cpu_size_allocate(GtkWidget *widget,
    GtkAllocation *allocation);
static void gtk_cpu_realize(GtkWidget *widget);
static gboolean gtk_cpu_expose(GtkWidget *widget,
    GdkEventExpose *event);
static void gtk_cpu_paint(GtkWidget *widget);
static void gtk_cpu_destroy(GtkObject *object);

GtkType gtk_cpu_get_type(void)
{
    static GtkType gtk_cpu_type = 0;

    if (!gtk_cpu_type) {
        static const GtkTypeInfo gtk_cpu_info = {
            "GtkCpu",
            sizeof(GtkCpu),
            sizeof(GtkCpuClass),
            (GtkClassInitFunc) gtk_cpu_class_init,
            (GtkObjectInitFunc) gtk_cpu_init,
            NULL,
            NULL,
            (GtkClassInitFunc) NULL
        };
        gtk_cpu_type = gtk_type_unique(GTK_TYPE_WIDGET, &gtk_cpu_info);
    }

    return gtk_cpu_type;
}

void gtk_cpu_set_state(GtkCpu *cpu, gint num)
{
    cpu->sel = num;
    gtk_cpu_paint(GTK_WIDGET(cpu));
}

GtkWidget *gtk_cpu_new()
{
    return GTK_WIDGET(gtk_type_new(gtk_cpu_get_type()));
}

static void gtk_cpu_class_init(GtkCpuClass *klass)
{
    GtkWidgetClass *widget_class;
    GtkObjectClass *object_class;

    widget_class = (GtkWidgetClass *)klass;
    object_class = (GtkObjectClass *)klass;

    widget_class->realize = gtk_cpu_realize;
    widget_class->size_request = gtk_cpu_size_request;
    widget_class->size_allocate = gtk_cpu_size_allocate;
    widget_class->expose_event = gtk_cpu_expose;

    object_class->destroy = gtk_cpu_destroy;
}

static void gtk_cpu_init(GtkCpu *cpu)
{
    cpu->sel = 0;
}

static void gtk_cpu_size_request(GtkWidget *widget,
    GtkRequisition *requisition)
{
    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CPU(widget));
    g_return_if_fail(requisition != NULL);

    requisition->width = 80;
    requisition->height = 100;
}

static void gtk_cpu_size_allocate(GtkWidget *widget,
    GtkAllocation *allocation)
{
    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CPU(widget));
    g_return_if_fail(allocation != NULL);

    widget->allocation = *allocation;

    if (GTK_WIDGET_REALIZED(widget)) {
        gdk_window_move_resize(
            widget->window,
            allocation->x, allocation->y,
            allocation->width, allocation->height
        );
    }
}

static void gtk_cpu_realize(GtkWidget *widget)
{
    GdkWindowAttr attributes;
    guint attributes_mask;

    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CPU(widget));

    GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);

    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.x = widget->allocation.x;
    attributes.y = widget->allocation.y;
    attributes.width = 80;
    attributes.height = 100;

    attributes.wclass = GDK_INPUT_OUTPUT;
    attributes.event_mask = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;

    attributes_mask = GDK_WA_X | GDK_WA_Y;

    widget->window = gdk_window_new(
        gtk_widget_get_parent_window(widget),
        &attributes, attributes_mask
    );

    gdk_window_set_user_data(widget->window, widget);

    widget->style = gtk_style_attach(widget->style, widget->window);
    gtk_style_set_background(widget->style, widget->window, GTK_STATE_NORMAL);
}

static gboolean gtk_cpu_expose(GtkWidget *widget,
    GdkEventExpose *event)
{
    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(GTK_IS_CPU(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    gtk_cpu_paint(widget);

    return FALSE;
}

static void gtk_cpu_paint(GtkWidget *widget)
{
    cairo_t *cr;

    cr = gdk_cairo_create(widget->window);

    cairo_translate(cr, 0, 7);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);

    gint pos = GTK_CPU(widget)->sel;
    gint rect = pos / 5;

    cairo_set_source_rgb(cr, 0.2, 0.4, 0);

    gint i;
    for (i = 1; i <= 20; i++) {
        if (i > 20 - rect) {
            cairo_set_source_rgb(cr, 0.6, 1.0, 0);
        }
        else {
            cairo_set_source_rgb(cr, 0.2, 0.4, 0);
        }
        cairo_rectangle(cr, 8, i*4, 30, 3);
        cairo_rectangle(cr, 42, i*4, 30, 3);
        cairo_fill(cr);
    }

    cairo_destroy(cr);
}

static void gtk_cpu_destroy(GtkObject *object)
{
    GtkCpu *cpu;
    GtkCpuClass *klass;

    g_return_if_fail(object != NULL);
    g_return_if_fail(GTK_IS_CPU(object));

    cpu = GTK_CPU(object);

    klass = gtk_type_class(gtk_widget_get_type());

    if (GTK_OBJECT_CLASS(klass)->destroy) {
        (*GTK_OBJECT_CLASS(klass)->destroy) (object);
    }
}

