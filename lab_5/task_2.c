#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "task_2.h"
#include "utils.h"

void getNegativeRowSum(int *n, int *m, int ***matrix);
// Во всех заданиях предусмотреть захват и освобождение динамической памяти(calloc или malloc)
// На печать в виде таблиц вывести исходный двухмерный массив.Размеры массива N и M.
// Предусмотреть реакцию программы в случае, если исходные данные не позволяют выполнить поставленную задачу.
// Дан целочисленный прямоугольный массив.
// Определить сумму элементовв тех строках, которые содержат хотя бы один отрицательный элемент

int task2()
{
  int n, m;
  int **matrix;

  int isError = getMatrix(&n, &m, &matrix);

  if (isError)
  {
    printf("Произошла ошибка формирования матрицы");
    return 1;
  }

  setMatrixData(&n, &m, &matrix);

  printMatrix(&n, &m, &matrix);

  getNegativeRowSum(&n, &m, &matrix);

  freeMatrix(&n, &matrix);

  return 0;
}

void getNegativeRowSum(int *n, int *m, int ***matrix)
{
  int sum = 0;
  bool hasValidRows = false;

  for (int i = 0; i < *n; i++)
  {
    for (int j = 0; j < *m; j++)
    {
      if ((*matrix)[i][j] < 0)
      {
        for (int j = 0; j < *m; j++)
        {
          hasValidRows = true;
          sum += (*matrix)[i][j];
        }

        break;
      }
    }
  }

  if (!hasValidRows)
  {
    printf("Предупреждение: В матрице нет рядов, в которых содержатся отрицательные элементы.\n");
  }
  else
  {
    printf("Результаты анализа рядов: %d\n", sum);
  }
}
