#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "task_1.h"
#include "task_2.h"

void main()
{
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  system("cls");

  do
  {
    int taskId;

    printf("Введите номер задания для проверки (для завершения программы введите 0):\n");

    scanf_s(" %d", &taskId);

    switch (taskId)
    {
    case 0:
      exit(0);
      break;
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    default:
      printf("Такого задания нет. Попробуйте еще раз\n");
      _getch();
    }
  } while (1);
}