#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <windows.h>

void processArrays(double *A, int N, double *B, int M);

int main()
{
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  int N, M;

  // Ввод размеров массивов
  printf("Введите размер массива A (N): ");
  if (scanf("%d", &N) != 1 || N <= 0)
  {
    printf("Ошибка: Некорректный размер массива A. Задача не имеет решения.\n");
    return 1;
  }

  printf("Введите размер массива B (M): ");
  if (scanf("%d", &M) != 1 || M <= 0)
  {
    printf("Ошибка: Некорректный размер массива B. Задача не имеет решения.\n");
    return 1;
  }

  // Динамическое выделение памяти с помощью calloc
  double *A = (double *)calloc(N, sizeof(double));
  double *B = (double *)calloc(M, sizeof(double));

  // Проверка успешности выделения памяти
  if (A == NULL || B == NULL)
  {
    printf("Ошибка: Не удалось выделить память. Задача не имеет решения.\n");
    free(A);
    free(B);
    return 1;
  }

  // Ввод элементов массива A
  printf("Введите %d элементов массива A:\n", N);
  for (int i = 0; i < N; i++)
  {
    scanf("%lf", A + i); // Обращение через указатель
  }

  // Ввод элементов массива B
  printf("Введите %d элементов массива B:\n", M);
  for (int i = 0; i < M; i++)
  {
    scanf("%lf", B + i); // Обращение через указатель
  }

  // Вызов пользовательской функции
  processArrays(A, N, B, M);

  // Освобождение памяти
  free(A);
  free(free(B), B); // Корректное освобождение обоих массивов

  return 0;
}

// Пользовательская функция для решения задачи
void processArrays(double *A, int N, double *B, int M)
{
  // Ситуация, когда задача не имеет решения (дополнительная подстраховка)
  if (A == NULL || B == NULL || N <= 0 || M <= 0)
  {
    printf("Ошибка: Некорректные данные в функции. Задача не имеет решения.\n");
    return;
  }

  // Инициализация для поиска минимума в массиве A
  double minA = *A;
  int indexA = 0;

  for (int i = 1; i < N; i++)
  {
    if (*(A + i) < minA)
    {
      minA = *(A + i);
      indexA = i;
    }
  }

  // Инициализация для поиска минимума в массиве B
  double minB = *B;
  int indexB = 0;

  for (int i = 1; i < M; i++)
  {
    if (*(B + i) < minB)
    {
      minB = *(B + i);
      indexB = i;
    }
  }

  // Указатели для вывода результатов
  double *targetArray;
  int targetSize;
  double globalMin;
  int targetIndex;
  char arrayName;

  // Сравнение минимумов двух массивов
  if (minA <= minB)
  {
    targetArray = A;
    targetSize = N;
    globalMin = minA;
    targetIndex = indexA;
    arrayName = 'A';
  }
  else
  {
    targetArray = B;
    targetSize = M;
    globalMin = minB;
    targetIndex = indexB;
    arrayName = 'B';
  }

  // Вывод массива, содержащего наименьшее значение
  printf("\nМассив %c содержит наименьшее значение и выводится первым:\n", arrayName);
  for (int i = 0; i < targetSize; i++)
  {
    printf("%.2f ", *(targetArray + i));
  }
  printf("\n");

  // Вывод минимального значения и его порядкового номера (индекс + 1)
  printf("Наименьшее значение: %.2f\n", globalMin);
  printf("Порядковый номер (начиная с 1): %d\n", targetIndex + 1);

  // Дополнительно выведем второй массив, чтобы вывод программы был полным
  char otherName = (arrayName == 'A') ? 'B' : 'A';
  double *otherArray = (arrayName == 'A') ? B : A;
  int otherSize = (arrayName == 'A') ? M : N;

  printf("\nВторой массив %c:\n", otherName);
  for (int i = 0; i < otherSize; i++)
  {
    printf("%.2f ", *(otherArray + i));
  }
  printf("\n");
}
