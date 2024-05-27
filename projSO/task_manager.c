#include "task_manager.h"

static Task tasks[MAX_TASKS];
static int task_count = 0;
static GtkWidget *window;

void add_task(const char *title, const char *description, Priority priority, time_t due_date) {
    if (task_count < MAX_TASKS) {
        strncpy(tasks[task_count].title, title, MAX_TITLE_LEN - 1);
        strncpy(tasks[task_count].description, description, MAX_DESC_LEN - 1);
        tasks[task_count].title[MAX_TITLE_LEN - 1] = '\0';
        tasks[task_count].description[MAX_DESC_LEN - 1] = '\0';
        tasks[task_count].priority = priority;
        tasks[task_count].due_date = due_date;
        tasks[task_count].status = 0;
        task_count++;
        save_tasks();
    } else {
        g_print("Task list is full!\n");
    }
}

void list_tasks() {
    gchar info[1024] = {0};
    for (int i = 0; i < task_count; i++) {
        g_snprintf(info + strlen(info), sizeof(info) - strlen(info),
            "Task ID: %d\nTitle: %s\nDescription: %s\nPriority: %s\nDue Date: %sStatus: %s\n\n",
            i, tasks[i].title, tasks[i].description,
            tasks[i].priority == HIGH ? "High" : (tasks[i].priority == MEDIUM ? "Medium" : "Low"),
            ctime(&tasks[i].due_date),
            tasks[i].status ? "Completed" : "Pending");
    }
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Tasks List:\n%s", info);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void load_tasks() {
    FILE *file = fopen(TASK_FILE, "rb");
    if (file) {
        fread(&task_count, sizeof(int), 1, file);
        fread(tasks, sizeof(Task), task_count, file);
        fclose(file);
    } else {
        printf("Unable to open the file or no existing task data found.\n");
        task_count = 0;
    }
}

void add_task_dialog() {
    GtkWidget *dialog, *title_entry, *description_entry, *priority_combo;
    dialog = gtk_dialog_new_with_buttons("Add Task", GTK_WINDOW(window), GTK_DIALOG_MODAL, 
                                         "Add", GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_REJECT, NULL);

    // Container for dialog contents
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(content_area), box);

    // Title entry
    title_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(title_entry), "Enter task title");
    gtk_box_pack_start(GTK_BOX(box), title_entry, TRUE, TRUE, 0);

    // Description entry
    description_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(description_entry), "Enter task description");
    gtk_box_pack_start(GTK_BOX(box), description_entry, TRUE, TRUE, 0);

    // Priority combobox
    priority_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(priority_combo), "High");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(priority_combo), "Medium");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(priority_combo), "Low");
    gtk_combo_box_set_active(GTK_COMBO_BOX(priority_combo), 0);
    gtk_box_pack_start(GTK_BOX(box), priority_combo, TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        const char *title = gtk_entry_get_text(GTK_ENTRY(title_entry));
        const char *description = gtk_entry_get_text(GTK_ENTRY(description_entry));
        Priority priority = gtk_combo_box_get_active(GTK_COMBO_BOX(priority_combo));
        add_task(title, description, priority, time(NULL)); // Assuming tasks are due now for simplicity
    }

    gtk_widget_destroy(dialog);
}

void edit_task_dialog() {
    if (task_count == 0) {
        g_print("No tasks available to edit.\n");
        return;
    }

    // Criar diálogo para selecionar a tarefa a editar
    GtkWidget *dialog, *combo, *label;
    dialog = gtk_dialog_new_with_buttons("Edit Task", GTK_WINDOW(window), GTK_DIALOG_MODAL, 
                                         "Cancel", GTK_RESPONSE_CANCEL,
                                         "Edit", GTK_RESPONSE_ACCEPT, 
                                         NULL);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(content_area), box);

    label = gtk_label_new("Select a task to edit:");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    combo = gtk_combo_box_text_new();
    for (int i = 0; i < task_count; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), tasks[i].title);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    gtk_box_pack_start(GTK_BOX(box), combo, FALSE, FALSE, 0);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        int selected_id = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
        if (selected_id != -1) {
            show_edit_task_form(selected_id);
        }
    }
    gtk_widget_destroy(dialog);
}

void show_edit_task_form(int task_id) {
    GtkWidget *dialog, *title_entry, *description_entry, *priority_combo;
    dialog = gtk_dialog_new_with_buttons("Edit Task Details", GTK_WINDOW(window), GTK_DIALOG_MODAL, 
                                         "Save", GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_CANCEL, NULL);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(content_area), box);

    title_entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(title_entry), tasks[task_id].title);
    gtk_box_pack_start(GTK_BOX(box), title_entry, TRUE, TRUE, 0);

    description_entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(description_entry), tasks[task_id].description);
    gtk_box_pack_start(GTK_BOX(box), description_entry, TRUE, TRUE, 0);

    priority_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(priority_combo), "High");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(priority_combo), "Medium");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(priority_combo), "Low");
    gtk_combo_box_set_active(GTK_COMBO_BOX(priority_combo), tasks[task_id].priority);
    gtk_box_pack_start(GTK_BOX(box), priority_combo, TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        strncpy(tasks[task_id].title, gtk_entry_get_text(GTK_ENTRY(title_entry)), MAX_TITLE_LEN - 1);
        strncpy(tasks[task_id].description, gtk_entry_get_text(GTK_ENTRY(description_entry)), MAX_DESC_LEN - 1);
        tasks[task_id].priority = gtk_combo_box_get_active(GTK_COMBO_BOX(priority_combo));
        save_tasks();
    }

    gtk_widget_destroy(dialog);
}

void save_tasks() {
    FILE *file = fopen(TASK_FILE, "wb");
    if (file) {
        fwrite(&task_count, sizeof(int), 1, file);  // Salva o número de tarefas
        for (int i = 0; i < task_count; i++) {
            fwrite(&tasks[i], sizeof(Task), 1, file);  // Salva cada tarefa
        }
        fclose(file);
    } else {
        fprintf(stderr, "Unable to open the file for writing.\n");
    }
}

void start_gui() {
    gtk_widget_show_all(window);
    gtk_main();
}


void init_gui(int *argc, char ***argv) {
    gtk_init(argc, argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Task Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Criação de um box para organizar os botões verticalmente
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *btnAdd = gtk_button_new_with_label("Add Task");
    GtkWidget *btnList = gtk_button_new_with_label("List Tasks");
    GtkWidget *btnEdit = gtk_button_new_with_label("Edit Task");

    // Adicionando botões ao box
    gtk_box_pack_start(GTK_BOX(vbox), btnAdd, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnList, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btnEdit, TRUE, TRUE, 0);

    // Conectando sinais aos botões
    g_signal_connect(btnAdd, "clicked", G_CALLBACK(add_task_dialog), NULL);
    g_signal_connect(btnList, "clicked", G_CALLBACK(list_tasks), NULL);
    g_signal_connect(btnEdit, "clicked", G_CALLBACK(edit_task_dialog), NULL);

    gtk_widget_show_all(window);
}




int main(int argc, char *argv[]) {
    load_tasks();
    init_gui(&argc, &argv);
    start_gui();
    return 0;
}
