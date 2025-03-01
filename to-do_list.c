
/*
 * To-do list
 * - A simple task manager
 * Made by: Nicolas
 * Date: 03/01/2025
 * Version: 1.0

 * Usage: 
 * Compile with gcc -o to-do_list to-do_list.c
 * and run with to-do_list
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDESC 256
#define MAXLIST 75

typedef unsigned uint;

typedef struct
{
  char desc[MAXDESC];
  int id;
  bool completed;
} Task;

Task tasks[MAXLIST];  // Tasks array
uint tasks_count = 0; // counting tasks

// func declarations
void tasks_add();  // adding tasks into tasks array;
void tasks_remove(); // removing;
void tasks_list(); // listing;
int tasks_find_task(int *id); // finding indexes
void menu(); // main menu;

int main(int argc, char *argv[]) 
{
  system("clear");  // i'm using sysclean to be more fancy
  menu();
  return EXIT_SUCCESS;
}

void tasks_add()
{
  if (tasks_count >= MAXLIST)
  {
    puts("Task list is full!");
    return;
  }

  char desc[MAXDESC];

  printf("\nEnter task description: ");
  system("clear");
  while (getchar() != '\n' && getchar() != EOF); // clearing buffer
  fgets(desc, MAXDESC, stdin);

  desc[strlen(desc)-1] = '\0'; // removing '\n'

  strcpy(tasks[tasks_count].desc, desc); // copying desc into desc from struct;

  tasks[tasks_count].id = tasks_count; // setting task id;

  tasks_count++;
  puts("Task has been added with success!");
}

void tasks_remove()
{
  int id;
  
  int found = tasks_find_task(&id);

  if (found)
  {
    for (int i = id; i < tasks_count; i++)
    {
      tasks[i] = tasks[i+1];
      tasks[i].id = i;
    }
    memset(&tasks[tasks_count - 1], 0, sizeof(Task));
    tasks_count--;
    puts("Your task was deleted.");
    return;
  }
  puts("Your task was not found.");
}

void tasks_list()
{
  if (!tasks_count)
  {
    system("clear");
    puts("There is no task on list. \n");
    return;
  }
  system("clear");
  puts("\n\t\t== Your tasks: ==");
  for (int i = 0; i < tasks_count; i++)
  {
    // trying to make output beautyful;
    printf("\t%d -: %s - %s\n", i, tasks[i].desc, tasks[i].completed ? " ✅ task concluded." : " ❌ task not concluded.");
  }
}

void tasks_conclude()
{
  int id;
  int found = tasks_find_task(&id);

  if (found)
  {
    if (tasks[id].completed == false)
    {
      tasks[id].completed = true;
      puts("You finished this task!");
    }
    else
    {
      puts("Your task is already finished.");
    }
  }
  else
  {
    puts("Your task was not found.");
    return;
  }
}

// Using int to be sure that it's not going to have any error;
int tasks_find_task(int *id)  // i don't know how to return id in other way
{
  tasks_list();
  printf("Enter task id: ");
  if (scanf("%d", id) == 0) exit(EXIT_FAILURE);;
  for (int i = *id; i < tasks_count && tasks_count != 0; i++)
  {
    if (tasks[i].id == *id)  // entered id is equal to struct id
    {
      *id = i;
      return 1;
    }
  }
  return 0;
}


void menu()
{
  int option;
  while (true)
  {
    puts("\n----- To-do List ------");
    puts("1. Add a task;");
    puts("2. Remove a task;");
    puts("3. List all tasks;");
    puts("4. Conclude a task;");
    puts("0. Exit");
    
    printf(" -> ");
    if (scanf("%d", &option) == 0)
    {
      puts("Enter a valid value!");
      while (getchar() != '\n');
      return;
    }

    switch (option)
    {
      case 1: 
        tasks_add();
        break;
      case 2: 
        tasks_remove();
        break;
      case 3: 
        tasks_list();
        break;
      case 4:
        tasks_conclude();
        break;
      case 0:
        puts("Exiting..");
        return;
      default:
        puts("Enter a valid value!");
    }
  }
}
