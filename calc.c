#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

static void button_clicked(GtkWidget *widget, gpointer data)
{
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *text = gtk_entry_get_text(entry);

    if (strcmp(text, "0") == 0)
        gtk_entry_set_text(entry, "");

    gchar *new_text = g_strconcat(text, label, NULL);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}

static void clear_clicked(GtkWidget *widget, gpointer data)
{
    GtkEntry *entry = GTK_ENTRY(data);
    gtk_entry_set_text(entry, "0");
}

static void equals_clicked(GtkWidget *widget, gpointer data)
{
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *expression = gtk_entry_get_text(entry);

    double result = 0;
    // Simple evaluation - replace with proper parser
    if (sscanf(expression, "%lf", &result) == 1)
    {
        gchar buf[32];
        g_snprintf(buf, sizeof(buf), "%.2f", result);
        gtk_entry_set_text(entry, buf);
    }
    else
    {
        gtk_entry_set_text(entry, "Error");
    }
}

int main(int argc, char *argv[])
{
    GtkWidget *window, *grid, *entry, *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1.0);
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_widget_set_vexpand(entry, TRUE);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    // Number and operator buttons
    const char *button_labels[] = {
        "7", "8", "9", "+",
        "4", "5", "6", "-",
        "1", "2", "3", "*",
        "0", "C", "=", "/"};

    for (int i = 0; i < 16; i++)
    {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_widget_set_hexpand(button, TRUE);
        gtk_widget_set_vexpand(button, TRUE);

        int col = i % 4;
        int row = 1 + i / 4;

        if (strcmp(button_labels[i], "=") == 0)
        {
            g_signal_connect(button, "clicked", G_CALLBACK(equals_clicked), entry);
        }
        else if (strcmp(button_labels[i], "C") == 0)
        {
            g_signal_connect(button, "clicked", G_CALLBACK(clear_clicked), entry);
        }
        else
        {
            g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), entry);
        }

        gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
    }

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
