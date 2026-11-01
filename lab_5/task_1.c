#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "task_1.h"
#include "utils.h"

void getFirstRowSum(int *m, int ***matrix);

// Программа печатает массив в виде таблицы,
// Размеры массива N и M, значения элементов массива вводятся с клавиатуры.
// Обращение к элементам массива выполняется только через косвенную адресацию,
// Предусмотреть реакцию программы в случае, если исходные данные не позволяют выполнить поставленную задачу.
// Задан двумерный массив М(N, M).
// В массиве вычислить сумму значений элементов первой строки и вывести ее на экран.

int task1()
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

  getFirstRowSum(&m, &matrix);

  freeMatrix(&n, &matrix);

  return 0;
}

void getFirstRowSum(int *m, int ***matrix)
{
  int sum = 0;

  for (int j = 0; j < *m; j++)
  {
    sum += (*matrix)[0][j];
  }

  printf("Сумма элементов первой строки: %d\n", sum);
}
