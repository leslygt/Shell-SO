#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TASK_FILE "task_manager/tasks.dat"
#define MAX_TASKS 100
#define MAX_TITLE_LEN 100
#define MAX_DESC_LEN 255

typedef enum { HIGH, MEDIUM, LOW } Priority;

typedef struct {
    char title[MAX_TITLE_LEN];
    char description[MAX_DESC_LEN];
    Priority priority;
    time_t due_date;
    int status; // 0 for pending, 1 for completed
} Task;

void add_task(const char *title, const char *description, Priority priority, time_t due_date);
void list_tasks();
void update_task(int task_id, const char *title, const char *description, Priority priority, time_t due_date, int status);
void load_tasks();
void save_tasks();
void show_notification(Task task);  // If you plan to implement notifications

// GUI functions
void init_gui(int *argc, char ***argv);
void start_gui();
void add_task_dialog();
void show_edit_task_form(int task_id);  // Declaration for the edit task form function

#endif // TASK_MANAGER_H
