#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int **getEmptyMatrix(int *n)
{
  return (int **)malloc((*n) * sizeof(int *));
}

int getMatrix(int *n, int *m, int ***matrix)
{
  printf("Введите количество строк N: ");
  scanf("%d", n);

  if (*n <= 1)
  {
    printf("Ошибка: Неверное количество строк. Задачу выполнить невозможно.\n");
    return 1;
  }

  printf("Введите количество столбцов M: ");
  scanf("%d", m);

  if (*m <= 1)
  {
    printf("Ошибка: Неверное количество столбцов. Задачу выполнить невозможно.\n");
    return 1;
  }

  // создаем матрицу
  *matrix = getEmptyMatrix(n);

  if (*matrix == NULL)
  {
    printf("Ошибка выделения памяти.\n");
    return 1;
  }

  // Выделение памяти под элементы каждой строки
  for (int i = 0; i < *n; i++)
  {
    (*matrix)[i] = (int *)malloc((*m) * sizeof(int));
    if ((*matrix)[i] == NULL)
    {
      printf("Ошибка выделения памяти.\n");
      return 1;
    }
  }

  return 0;
}

int setMatrixData(int *n, int *m, int ***matrix)
{
  printf("Введите элементы массива (%d x %d):\n", *n, *m);

  for (int i = 0; i < *n; i++)
  {
    for (int j = 0; j < *m; j++)
    {
      printf("M[%d][%d] = ", i, j);
      scanf("%d", &(*matrix)[i][j]);
    }
  }
}

void printMatrix(int *n, int *m, int ***matrix)
{
  printf("\nИсходный массив:\n");

  for (int i = 0; i < *n; i++)
  {
    for (int j = 0; j < *m; j++)
    {
      printf("%d   ", (*matrix)[i][j]);
    }
    printf("\n");
  }
}

void freeMatrix(int *n, int ***matrix)
{
  for (int i = 0; i < *n; i++)
  {
    free((*matrix)[i]);
  }
  free(*matrix);
}
