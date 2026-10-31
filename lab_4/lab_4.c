#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE 10000

void task1(void);
void task2(void);
void task3(void);
void setArray(int *, int);
void selectTask(void);

int main()
{
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  srand(time(NULL));

  selectTask();
}

void selectTask()
{
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
    case 3:
      task3();
      break;
    default:
      printf("Такого задания нет\n");
      _getch();
    }
  } while (1);
}

void setArray(int *array, int n)
{
  printf("Введите %d элементов массива A:\n", n);

  for (int i = 0; i < n; i++)
  {
    scanf("%d", array + i);
  }
}

int *getEmptyArray(int length)
{
  return (int *)malloc(length * sizeof(int));
}

void getRandomArray(int *array, int length)
{
  for (int i = 0; i < length; i++)
  {
    array[i] = rand() % length;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////

void processArrays(int *arrayA, int n, int *arrayB, int m)
{
  // Заданы два массива А(N) и В(M).Первым на печать вывести массив,
  // содержащий наименьшее значение.Напечатать также это значение и его
  // порядковый номер.

  int minNumberInArrayA = *arrayA;
  int indexArrayA = 0;

  for (int i = 1; i < n; i++)
  {
    if (*(arrayA + i) < minNumberInArrayA)
    {
      minNumberInArrayA = *(arrayA + i);
      indexArrayA = i;
    }
  }

  int minNumberInArrayB = *arrayB;
  int indexArrayB = 0;

  for (int i = 1; i < m; i++)
  {
    if (*(arrayB + i) < minNumberInArrayB)
    {
      minNumberInArrayB = *(arrayB + i);
      indexArrayB = i;
    }
  }

  int *currentArray;
  int currentSize;
  int globalMin;
  int currentIndex;
  char arrayName;

  if (minNumberInArrayA <= minNumberInArrayB)
  {
    currentArray = arrayA;
    currentSize = n;
    globalMin = minNumberInArrayA;
    currentIndex = indexArrayA;
    arrayName = 'A';
  }
  else
  {
    currentArray = arrayB;
    currentSize = m;
    globalMin = minNumberInArrayB;
    currentIndex = indexArrayB;
    arrayName = 'B';
  }

  printf("\nМассив %c содержит наименьшее значение и выводится первым:\n", arrayName);
  for (int i = 0; i < currentSize; i++)
  {
    printf("%d ", *(currentArray + i));
  }
  printf("\n");

  printf("Наименьшее значение: %d\n", globalMin);
  printf("Порядковый номер (начиная с 1): %d\n", currentIndex + 1);

  char otherName = arrayName == 'A' ? 'B' : 'A';
  int *otherArray = arrayName == 'A' ? arrayB : arrayA;
  int otherSize = arrayName == 'A' ? m : n;

  printf("\nВторой массив %c:\n", otherName);
  for (int i = 0; i < otherSize; i++)
  {
    printf("%d ", *(otherArray + i));
  }
  printf("\n");
}

void task1()
{
  int n, m;

  printf("Введите размер массива A (n): ");
  scanf("%d", &n);

  if (n <= 1)
  {
    printf("Ошибка: Некорректный размер массива A. Задача не имеет решения.\n");
    return;
  }

  printf("Введите размер массива B (m): ");
  scanf("%d", &m);

  if (m <= 1)
  {
    printf("Ошибка: Некорректный размер массива B. Задача не имеет решения.\n");
    return;
  }

  int *arrayA = (int *)calloc(n, sizeof(int));
  int *arrayB = (int *)calloc(m, sizeof(int));

  if (arrayA == NULL || arrayB == NULL)
  {
    printf("Ошибка: Не удалось выделить память. Задача не имеет решения.\n");
    free(arrayA);
    free(arrayB);
    return;
  }

  setArray(arrayA, n);
  setArray(arrayB, m);

  processArrays(arrayA, n, arrayB, m);

  free(arrayA);
  free(arrayB);

  system("pause");
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////

void calculateSumBetweenNegativeNumbers(int *arr, int n)
{
  int firstNegIdx = -1;
  int secondNegIdx = -1;

  for (int i = 0; i < n; ++i)
  {
    if (*(arr + i) < 0)
    {
      if (firstNegIdx == -1)
      {
        firstNegIdx = i;
      }
      else
      {
        secondNegIdx = i;
        break;
      }
    }
  }

  if (firstNegIdx == -1)
  {
    printf("Результат: В массиве нет ни одного отрицательного числа. Задача не имеет решения.\n");
    return;
  }

  if (secondNegIdx == -1)
  {
    printf("Результат: В массиве есть только одно отрицательное число. Задача не имеет решения.\n");
    return;
  }

  if (secondNegIdx - firstNegIdx == 1)
  {
    printf("Результат: Первый и второй отрицательные числа расположены рядом. Между ними нет элементов, сумма равна 0.\n");
    return;
  }

  int sum = 0;

  for (int i = firstNegIdx + 1; i < secondNegIdx; ++i)
  {
    sum += *(arr + i);
  }

  printf("Результаты\n");
  printf("Первый отрицательный элемент: %d (индекс %d)\n", *(arr + firstNegIdx), firstNegIdx);
  printf("Второй отрицательный элемент: %d (индекс %d)\n", *(arr + secondNegIdx), secondNegIdx);
  printf("Сумма элементов между ними: %d\n", sum);

  system("pause");
}

void task2()
{
  // Массив создается в динамической области памяти функцией new.
  // При обращении к элементам массива воспользоваться взаимосвязью массивов с указателями.
  // Предусмотреть реакцию программы на ситуации, при которых задача не имеет решения.
  // В одномерном массиве, состоящем из n вводимых с клавиатуры элементов, вычислить :
  // Сумму элементов массива, расположенных между первым и вторым отрицательными элементами;
  int n;

  printf("Введите размер массива (n): ");
  scanf("%d", &n);

  if (n <= 1)
  {
    printf("Ошибка: Некорректный размер массива. Задача не имеет решения.\n");
    return;
  }

  int *array = getEmptyArray(n);

  if (array == NULL)
  {
    printf("Ошибка: Не удалось выделить память. Задача не имеет решения.\n");
    return;
  }

  setArray(array, n);

  calculateSumBetweenNegativeNumbers(array, n);

  free(array);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////

// Функция для обмена элементов
void changeNumbers(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(int *array, int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        changeNumbers(&array[j], &array[j + 1]);
      }
    }
  }
}

void quickSortHoare(int *array, int left, int right)
{
  if (left < right)
  {
    int middle = array[left + (right - left) / 2];
    int leftIndex = left;
    int rightIndex = right;

    while (leftIndex <= rightIndex)
    {
      while (array[leftIndex] < middle)
        leftIndex++;
      while (array[rightIndex] > middle)
        rightIndex--;
      if (leftIndex <= rightIndex)
      {
        changeNumbers(&array[leftIndex], &array[rightIndex]);
        leftIndex++;
        rightIndex--;
      }
    }

    if (left < rightIndex)
      quickSortHoare(array, left, rightIndex);
    if (leftIndex < right)
      quickSortHoare(array, leftIndex, right);
  }
}

typedef struct
{
  int index;
  int count;
} SearchResult;

SearchResult binarySearch(int *array, int target, int length)
{
  int left = 0;
  int right = length - 1;
  SearchResult result = {-1, 0};

  while (left <= right)
  {
    int middle = left + (right - left) / 2;
    result.count++;

    if (array[middle] == target)
    {
      result.index = middle;
      return result;
    }
    else if (array[middle] < target)
    {
      left = middle + 1;
    }
    else
    {
      right = middle - 1;
    }
  }

  return result;
}

void task3()
{
  int *initialArray = getEmptyArray(ARRAY_SIZE);
  int *bubbleArray = getEmptyArray(ARRAY_SIZE);
  int *hoareArray = getEmptyArray(ARRAY_SIZE);

  getRandomArray(initialArray, ARRAY_SIZE);

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    bubbleArray[i] = *(initialArray + i);
    hoareArray[i] = *(initialArray + i);
  }

  clock_t start, end;
  double time_bubble, time_hoare;

  // Замер времени для пузырьковой сортировки
  start = clock();
  bubbleSort(bubbleArray, ARRAY_SIZE);
  end = clock();
  time_bubble = ((double)(end - start)) / CLOCKS_PER_SEC;

  // Замер времени для сортировки Хоара
  start = clock();
  quickSortHoare(hoareArray, 0, ARRAY_SIZE - 1);
  end = clock();
  time_hoare = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("=== Результаты сравнения (массив на %d элементов) ===\n", ARRAY_SIZE);
  printf("Метод пузырька: %.4f сек.\n", time_bubble);
  printf("Метод Хоара:    %.4f сек.\n\n", time_hoare);
  printf("Метод Хоара быстрее пузырька примерно в %.1f раз(а).\n", time_bubble / time_hoare);

  // binarySearch

  int target;

  printf("Введите искомое число: ");
  scanf("%d", &target);

  SearchResult searchResult = binarySearch(hoareArray, target, ARRAY_SIZE);

  if (searchResult.index == -1)
  {
    printf("Бинарный поиск: число %d из массива длинно %d НЕ НАЙДЕНО, всего итераций %d\n", target, ARRAY_SIZE, searchResult.count);
  }
  else
  {
    printf("Бинарный поиск: нашли число %d из массива длинно %d на индексе %d за %d итераций\n", target, ARRAY_SIZE, searchResult.index, searchResult.count);
  }

  free(initialArray);
  free(bubbleArray);
  free(hoareArray);
}