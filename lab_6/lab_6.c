#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

const int MAX_SIZE = 256;

// Во всех заданиях предусмотреть захват и освобождение динамической
// памяти(операции new, delete), решение оформить в виде отдельной
// функции, которой передается исходная строка.На печать вывести исходную и преобразованную строки.
// Ввести строку символов, если ее длина кратна 3, удалить все цифры, делящиеся на 3.

char *getPreparedString(const char *initialString, char *resultString)
{
  int len = strlen(initialString);

  if (len % 3 == 0)
  {
    int j = 0;

    for (int i = 0; i < len; i++)
    {
      if (isdigit(initialString[i]) && initialString[i] % 3 == 0)
      {
        continue;
      }
      resultString[j] = initialString[i];
      j++;
    }
    resultString[j] = '\0';
  }
  else
  {
    strcpy(resultString, initialString);
  }

  return resultString;
}

int main()
{
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  char *inputString = (char *)malloc(MAX_SIZE * sizeof(char));
  char *resultString = (char *)malloc(MAX_SIZE * sizeof(char));

  if (inputString == NULL || resultString == NULL)
  {
    return 1;
  }

  printf("Введите строку (максимальная длинна %d символов): ", MAX_SIZE);
  gets_s(inputString, MAX_SIZE);

  if (!strlen(inputString))
  {
    printf("Вы ничего не ввели");
    return 1;
  }

  getPreparedString(inputString, resultString);

  printf("Исходная строка:        %s\n", inputString);
  printf("Преобразованная строка: %s\n", resultString);

  free(inputString);
  free(resultString);

  return 0;
}