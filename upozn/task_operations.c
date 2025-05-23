//
// Created by jegorix on 26.04.25.
//

#include "task_operations.h"


int calculate_deadline(Task* task)
{
    return task->day + task->month + task->year;
}

void addTask(TaskList* list)
{
    if(list->size >= list->capacity)
    {
        list->capacity += 3;
        list->tasks = realloc(list->tasks, list->capacity * sizeof(Task));
    }

    Task* new_task = &list->tasks[list->size];
    new_task->id = list->size + 1;

    char buffer[256];
    char* striped_buffer;


    do{
        printf("\n╭───────────────────────────────────╮\n");
        printf("│     Введите название задачи:      │\n");
        printf("╰───────────────────────────────────╯\n");
    printf("╰─> ");
    fgets(buffer, 256, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    striped_buffer = strip(buffer);

    if(strlen(striped_buffer) == 0)
    {
      printf("\n╭────────────────────────────────────────╮\n");
        printf("│  Название задачи не может быть пустым  │\n");
        printf("╰────────────────────────────────────────╯\n");
        printf("\n");
    }


    }
    while(strlen(striped_buffer) == 0);
    new_task->title = strdup(striped_buffer);
    printf("\n");



  printf("\n╭───────────────────────────────────╮\n");
    printf("│     Введите описание задачи:      │\n");
    printf("╰───────────────────────────────────╯\n");
    printf("╰─> ");

    fgets(buffer, 256, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_task->description = strdup(buffer);
    printf("\n");

    printf("\n╭────────────────────────────────────────╮\n");
    printf("│ Введите день выполнения задачи (1-31): │\n");
    printf("╰────────────────────────────────────────╯\n");
    printf("╰─> ");

    int day = execute_verification(1,31);
    new_task->day = day;
    printf("\n");

  printf("\n╭─────────────────────────────────────────╮\n");
    printf("│ Введите месяц выполнения задачи (1-12): │\n");
    printf("╰─────────────────────────────────────────╯\n");
    printf("╰─> ");

    int month = execute_verification(1,12);
    new_task->month = month;
    printf("\n");

  printf("\n╭────────────────────────────────────────╮\n");
    printf("│     Введите год выполнения задачи:     │\n");
    printf("╰────────────────────────────────────────╯\n");
    printf("╰─> ");

    int year = execute_verification(2025, max_limit);
    new_task->year = year;
    printf("\n");


    new_task->deadline = calculate_deadline(new_task);

  printf("\n╭────────────────────────────────────────╮\n");
    printf("│ Введите приоритет задачи:              │\n");
    printf("│ (1 - высокий, 2 - средний, 3 - низкий) │\n");
    printf("╰────────────────────────────────────────╯\n");
    printf("╰─> ");

    int priority = execute_verification(1, 3);
    new_task->priority = priority;
    printf("\n");

    new_task->status = 0;
    list->size++;

  printf("\n╔════════════════════════════════════════════╗\n");
    printf("║        Задача успешно добавлена!           ║\n");
    printf("╚════════════════════════════════════════════╝\n");


}


void show_micro_task(Task* task)
{
    printf("\n╭────────────────────────╮\n");
    printf("│     Задача № %-4d      │\n", task->id);
    printf("╰────────────────────────╯\n");


  printf("\n╭──────────────────────────────╮\n");
    printf("│           Название:          │\n");
    printf("│                              │\n");
    printf("  %s \n", task->title);
    printf("╰──────────────────────────────╯\n");


  printf("\n╭────────────────────────────────────────────────────────╮\n");
    printf("│                       Описание:                        │\n");
    printf("│                                                        │\n");
    printf("  %s                                                  \n", task->description);
    printf("╰────────────────────────────────────────────────────────╯\n");


    printf("\n╭────────────────────────────────────────────────────────╮\n");
    printf("│                   Срок выполнения до:                  │\n");
    printf("                        %02d.%02d.%04d \n", task->day, task->month, task->year);
    printf("╰────────────────────────────────────────────────────────╯\n");

    switch(task->priority)
    {
        case 1:
            printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                      Приоритет:                        │\n");
            printf("│                Задача высокой важности                 │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
            break;

        case 2:
            printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                      Приоритет:                        │\n");
            printf("│                Задача средней важности                 │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
            break;

        case 3:
            printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                      Приоритет:                        │\n");
            printf("│                Задача низкой важности                  │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
            break;
    }

    if(task->status)
    {
        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│                      Статус:                           │\n");
        printf("│                  Задача выполнена!                     │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
    }
    else
    {
        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│                      Статус:                           │\n");
        printf("│                Задача не выполнена!                    │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
    }
    printf("────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    printf("\n");
}





void showTasks(TaskList* list)
{
    if(list->size == 0)
    {
      printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│                Нет задач для отображения.              │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        return;
    }

    for(int i = 0; i < list->size; i++)
    {
        Task* task = &list->tasks[i];
        show_micro_task(task);
    }

}



void TasksShortList(TaskList* list)
{
    printf("\n╭─────────────────────────────────────────────────────────╮\n");
    printf("│                 Актуальные задачи (%d)                   │\n", list->size);

    for(int i = 0; i < list->size; i++)
    {
        char active_status[25];;
        if(list->tasks[i].status == 1)
        {
            strcpy(active_status, "Выполнена\0");
        }

        else
        {
            strcpy(active_status, "Невыполнена\0");
        }

        printf("\n╭─────────────────────────────────────────────────────────╮\n");
        printf("       %d - Задача № %d (%s) - %s\n", i+1, list->tasks[i].id, list->tasks[i].title, active_status);
        printf("╰─────────────────────────────────────────────────────────╯\n");
    }
    printf("\n│                                                         │\n", list->size);
    printf("╰─────────────────────────────────────────────────────────╯\n");


    printf("\n");

}








void editTask(TaskList* list)
{
    if(list->size == 0)
    {
        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│           Нет задач для редактирования.                │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        return;
    }


    TasksShortList(list);



    printf("\n╭────────────────────────────────────────────────────────╮\n");
    printf("│      Введите номер задачи, которую хотите изменить:    │\n");
    printf("╰────────────────────────────────────────────────────────╯\n");
    printf("╰─> ");

    int id = execute_verification(1, list->size);

    if(id < 1 || id > list->size)
    {
        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│          Неверный номер задачи! Попробуйте снова.      │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        return;
    }

    Task* task = &list->tasks[id-1];
    int running = 1;

while(running) {

  printf("\n╭─────────────────────────────────────────────────────────╮\n");
    printf("│                 Что вы хотите изменить?                 │\n");
    printf("╠═════════════════════════════════════════════════════════╣\n");
    printf("│ 1 - Название задачи                                     │\n");
    printf("│ 2 - Описание задачи                                     │\n");
    printf("│ 3 - Срок выполнения задачи                              │\n");
    printf("│ 4 - Приоритет задачи                                    │\n");
    printf("│ 5 - Статус задачи                                       │\n");
    printf("│ 6 - Завершить редактирование                            │\n");
    printf("╰─────────────────────────────────────────────────────────╯\n");
    printf("╰─> ");

    int choice = execute_verification(1,6);
    char buffer[256];


        switch (choice) {
            case 1:
                printf("\n╭───────────────────────────────────╮\n");
                printf("│     Введите новое название:       │\n");
                printf("╰───────────────────────────────────╯\n");
                printf("╰─> ");
                fgets(buffer, 256, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                free(task->title);
                task->title = strdup(buffer);
                break;

            case 2:
                printf("\n╭───────────────────────────────────╮\n");
                printf("│     Введите новое описание:       │\n");
                printf("╰───────────────────────────────────╯\n");
                printf("╰─> ");
                fgets(buffer, 256, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                free(task->description);
                task->description = strdup(buffer);
                break;

            case 3:
              printf("\n╭───────────────────────────────────╮\n");
                printf("│     Введите новый день (1-31):    │\n");
                printf("╰───────────────────────────────────╯\n");
                printf("╰─> ");
                int day = execute_verification(1, 31);
                task->day = day;

                printf("\n╭───────────────────────────────────╮\n");
                printf("│    Введите новый месяц (1-12):    │\n");
                printf("╰───────────────────────────────────╯\n");
                printf("╰─> ");
                int month = execute_verification(1, 12);
                task->month = month;

                printf("\n╭───────────────────────────────────╮\n");
                printf("│         Введите новый год:        │\n");
                printf("╰───────────────────────────────────╯\n");
                printf("╰─> ");
                int year = execute_verification(2025, max_limit);
                task->year = year;
                break;

            case 4:
              printf("\n╭──────────────────────────────────────────╮\n");
                printf("│      Введите новый приоритет задачи:     │\n");
                printf("│  (1 - высокий, 2 - средний, 3 - низкий)  │\n");
                printf("╰──────────────────────────────────────────╯\n");
                printf("╰─> ");
                int priority = execute_verification(1,3);
                task->priority = priority;
                break;

            case 5:
              printf("\n╭────────────────────────────────────────────────╮\n");
                printf("│          Введите новый статус задачи:          │\n");
                printf("│         (0 - в процессе, 1 - выполнено)        │\n");
                printf("╰────────────────────────────────────────────────╯\n");
                printf("╰─> ");
                int status = execute_verification(0,1);
                task->status = status;
                break;

            case 6:
              printf("\n╭────────────────────────────────────────────────────────╮\n");
                printf("│           Завершение редактирования задачи.            │\n");
                printf("╰────────────────────────────────────────────────────────╯\n");
                printf("\n");
                printf("     Сохранение изменений");
                loadingAnimation(3, 250);
                running = 0;
                break;

            default:
              printf("\n╭────────────────────────────────────────────────────────╮\n");
                printf("│         Неверный выбор! Попробуйте ещё раз.            │\n");
                printf("╰────────────────────────────────────────────────────────╯\n");
                break;

        }

      printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│             Изменения сохранены успешно!               │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
    }



}


void markCompleteTask(TaskList* list) {
    int running = 1;

    if (list->size == 0) {
        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│           Нет задач для изменения статуса.             │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        return;
    }


    while (running) {
        int count = 0;
        printf("\n╭─────────────────────────────────────────────────────────╮\n");
        printf("│                  Невыполненные задачи                   │\n");

        for (int i = 0; i < list->size; i++) {
            if (!list->tasks[i].status) {
                count++;

                printf("\n╭─────────────────────────────────────────────────────────╮\n");
                printf("                  %d - Задача № %d (%s)\n", i + 1, list->tasks[i].id, list->tasks[i].title);
                printf("╰─────────────────────────────────────────────────────────╯\n");
            }
        }
      printf("\n│                  невыполненных задач: %d                 │\n", count);
        printf("╰─────────────────────────────────────────────────────────╯\n");

        printf("\n");


        if (!count) {
            printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                 Все задачи выполнены!                  │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
            return;
        }


        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│      Введите номер задачи, которую хотите изменить:    │\n");
        printf("│        Для выхода из редактирования, нажмите %d         │\n", list->size + 1);
        printf("╰────────────────────────────────────────────────────────╯\n");
        printf("╰─> ");

        int id = execute_verification(1, list->size + 1);

        if(id == list->size + 1)
        {
          printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                Выход из редактирования                 │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
            printf("     Сохранение изменений");
            loadingAnimation(3, 250);
            running = 0;
            return;
        }

        list->tasks[id - 1].status = 1;
        count--;

      printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("   Задача № %d (%s) отмечена как выполненная!       \n", list->tasks[id - 1].id,
               list->tasks[id - 1].title);
        printf("╰────────────────────────────────────────────────────────╯\n");


    }
}


void deleteTask(TaskList* list)
{
    int running = 1;

    if(list->size == 0)
    {
      printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│                 Нет задач для удаления.                │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        return;
    }

    while(running)
    {


        if (list->size == 0) {
            printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                  Все задачи удалены!                   │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
            return;
        }

        TasksShortList(list);
      printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│      Введите номер задачи, которую хотите удалить:     │\n");
        printf("│        Для выхода из режима удаления, нажмите %d        │\n", list->size + 1);
        printf("╰────────────────────────────────────────────────────────╯\n");
        printf("╰─> ");


        int id = execute_verification(1, list->size + 1);

        if(id == list->size + 1)
        {
          printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                   Выход из удаления                    │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
            printf("     Сохранение изменений");
            loadingAnimation(3, 250);
            running = 0;
            return;
        }

        char* title = strdup(list->tasks[id-1].title);
        free(list->tasks[id-1].title);
        free(list->tasks[id-1].description);

        for(int i = id - 1; i < list->size; i++)
        {
            list->tasks[i] = list->tasks[i+1];
        }
        list->size--;


        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("   Задача № %d (%s) успешно удалена!       \n", id, title);
          printf("╰────────────────────────────────────────────────────────╯\n");

        free(title);

    }

}

void searchTask(TaskList* list)
{
    if(list->size == 0)
    {
        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│                 Нет задач для поиска.                  │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        return;
    }

  printf("\n╭───────────────────────────────────╮\n");
    printf("│     Введите название задачи:      │\n");
    printf("╰───────────────────────────────────╯\n");
    printf("╰─> ");

    char buffer[256];
    fgets(buffer, 256, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    for(int i = 0; i < list->size; i++)
    {
        Task* task = &list->tasks[i];
        if( !strcmp(buffer, task->title) )
        {
          printf("\n╭────────────────────────────────────────────────────────╮\n");
            printf("│                Задача успешно найденa!                 │\n");
            printf("╰────────────────────────────────────────────────────────╯\n");
printf("────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
            show_micro_task(task);
            return;
        }
    }

        printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│                   Задача не найденa!                   │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        printf("────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");

}




void freeTasks(TaskList* list, int criteria)
{
    for(int i = 0; i < list->size; i++)
    {
        if(list->tasks[i].status == criteria)
        {
            free(list->tasks[i].title);
            free(list->tasks[i].description);

            for(int j = i; j < list->size; j++)
            {
                list->tasks[i] = list->tasks[i+1];
            }

            list->size--;
        }

        else
        {
            i++;
        }
    }

}



void clean(TaskList* list)
{
    for (int i = 0; i < list->size; i++) {
        free(list->tasks[i].title);
        free(list->tasks[i].description);
    }
    list->size = 0;
}





void clearTasks(TaskList* list)
{
    if(list->size == 0)
    {
      printf("\n╭────────────────────────────────────────────────────────╮\n");
        printf("│                  Список задач пуст.                    │\n");
        printf("╰────────────────────────────────────────────────────────╯\n");
        return;
    }


    TasksShortList(list);
    int running = 1;

  while(running) {
      printf("\n╭─────────────────────────────────────────────────────────╮\n");
      printf("│                 Что вы хотите очистить?                 │\n");
      printf("╠═════════════════════════════════════════════════════════╣\n");
      printf("│ 1 - Выполненные задачи                                  │\n");
      printf("│ 2 - Невыполненные задачи                                │\n");
      printf("│ 3 - Все задачи                                          │\n");
      printf("│ 4 - Просмотреть список задач                            │\n");
      printf("│ 5 - Выход                                               │\n");
      printf("╰─────────────────────────────────────────────────────────╯\n");
      printf("╰─> ");

      char choice = fgetch();
      int criteria;

      switch (choice) {
          case '1':
              criteria = 1;
              freeTasks(list, criteria);

              printf("\n╭────────────────────────────────────────────╮\n");
              printf("│     Выполненные задачи успешно удалены!    │\n");
              printf("╰────────────────────────────────────────────╯\n");
              break;

          case '2':
              criteria = 0;
              freeTasks(list, criteria);
              freeTasks(list, criteria);

              printf("\n╭────────────────────────────────────────────╮\n");
              printf("│    Невыполненные задачи успешно удалены!   │\n");
              printf("╰────────────────────────────────────────────╯\n");
              break;

          case '3':

              if(list->size == 0)
              {
                  printf("\n╭────────────────────────────────────────────────────────╮\n");
                  printf("│                  Список задач пуст.                    │\n");
                  printf("╰────────────────────────────────────────────────────────╯\n");
                  break;
              }

              clean(list);

              printf("\n╭────────────────────────────────────────────────────────╮\n");
              printf("│                Все задачи были удалены.                │\n");
              printf("╰────────────────────────────────────────────────────────╯\n");
              break;

          case '4':
              TasksShortList(list);
              break;

          case '5':
              printf("\n╭────────────────────────────────────────────────────────╮\n");
              printf("│                Выход из режима очистки                 │\n");
              printf("╰────────────────────────────────────────────────────────╯\n");
              printf("     Сохранение изменений");
              loadingAnimation(3, 250);
              running = 0;
              break;

          default:
              printf("\n╭────────────────────────────────────────────────────────╮\n");
              printf("│         Неверный выбор! Попробуйте ещё раз.            │\n");
              printf("╰────────────────────────────────────────────────────────╯\n");
              break;

      }

  }

}








    //printf("\n╭───────────────────────╮        ╭───────────────────────╮\n");
      //printf("│        1 - Да         │        │        2 - Нет        │\n");
      //printf("╰───────────────────────╯        ╰───────────────────────╯\n");