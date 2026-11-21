#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
// Составить программу, реализующую функции указанного
// ниже меню.Выполнить функциональное разбиение программного кода.Меню программы : 1 – Сформировать с клавиатуры строку и записать в
// файл(строка может содержать пробелы);
// 2 – Считать строку из файла и распечатать;
// 3 – Зашифровать строку и записать в файл;
// 4 – Расшифроват
// 5 - выход
// Каждая пара букв
// "су", "лу" и "ту"
// заменяется соответственно на
// "уус", "уул" и"уут".

#define MAX_SIZE 512
#define FILE_NAME "data.txt"

void printSuccessMessage(const char *text);
void printErrorMessage(const char *text);
void writeInputToFile(const char *filename);
void readAndPrintFromFile(const char *filename);
void encryptFile(const char *filename);
void decryptFile(const char *filename);
char *encryptString(const char *string);
char *decryptString(const char *string);
void clearInputBuffer();

int main()
{
  // SetConsoleCP(1251);
  // SetConsoleOutputCP(1251);

  printf("Меню программы:\n");
  printf("1 - Сформировать с клавиатуры строку и записать в файл (строка может содержать пробелы)\n");
  printf("2 - Считать строку из файла и распечатать\n");
  printf("3 - Зашифровать строку и записать в файл\n");
  printf("4 - Расшифровать строку и записать в файл\n");
  printf("5 - Выход\n");

  while (1)
  {
    printf("Выберите пункт меню (смотреть выше, 1 - create, 2 - read, 3 - encr, 4 - decr, 5 - exit):");

    int taskId = 0;

    scanf("%d", &taskId);

    clearInputBuffer();

    switch (taskId)
    {
    case 1:
      writeInputToFile(FILE_NAME);
      break;
    case 2:
      readAndPrintFromFile(FILE_NAME);
      break;
    case 3:
      encryptFile(FILE_NAME);
      break;
    case 4:
      decryptFile(FILE_NAME);
      break;
    case 5:
      printf("Конец выполнения программы.\n");
      exit(0);
    default:
      printf("Такого пункта нет! Попробуйте другой номер.\n");
    }
  }
}

size_t utf8_strlen(const char *s)
{
  size_t count = 0;

  while (*s)
  {
    if ((*s & 0xC0) != 0x80)
    {
      count++;
    }
    s++;
  }

  return count;
}

void printSuccessMessage(const char *text)
{
  printf("\033[1;32m%s\033[0m", text);
}

void printErrorMessage(const char *text)
{
  printf("\033[31m%s\033[0m", text);
}

void clearInputBuffer()
{
  int character;
  // удаляем посимвольно из строки пока не достигнем конца из-за того что
  // метод fgets считает что последний введенный Enter и есть строка (после выбора задачи)
  while ((character = getchar()) != '\n' && character != EOF)
    ;
}

void writeInputToFile(const char *filename)
{
  char *string = (char *)malloc(MAX_SIZE * sizeof(char));

  if (string == NULL)
  {
    printErrorMessage("Ошибка выделения памяти!\n");
    return;
  }

  printf("Введите строку: ");

  if (fgets(string, MAX_SIZE, stdin) != NULL)
  {
    string[strcspn(string, "\n")] = '\0'; // Удаляем символ переноса строки из-за специфики работы fgets
  }

  FILE *file = fopen(filename, "w");

  if (file == NULL)
  {
    printErrorMessage("Ошибка открытия файла для записи!\n");
    free(string);
    return;
  }

  fprintf(file, "%s", string);
  fclose(file);
  free(string);

  printSuccessMessage("Строка успешно записана в файл: ");
  printSuccessMessage(filename);
  printf("\n");
}

void readAndPrintFromFile(const char *filename)
{
  FILE *file = fopen(filename, "r");

  if (file == NULL)
  {
    printErrorMessage("Ошибка: файл ");
    printErrorMessage(filename);
    printErrorMessage(" не найден или пуст. Сначала выполните пункт 1.\n");
    return;
  }

  char *string = (char *)malloc(MAX_SIZE * sizeof(char));

  if (string == NULL)
  {
    printErrorMessage("Ошибка выделения памяти!\n");
    fclose(file);
    return;
  }

  if (fgets(string, MAX_SIZE, file) != NULL)
  {
    printf("Содержимое файла: ");
    printSuccessMessage(string);
    printf("\n");
  }
  else
  {
    printf("Файл пуст.\n");
  }

  fclose(file);
  free(string);
}

char *encryptString(const char *string)
{
  int length = utf8_strlen(string);
  // памяти нужно больше
  char *res = (char *)malloc((length * 2 + 1) * sizeof(char));

  if (res == NULL)
  {
    return NULL;
  }

  // printf("Длинна строки '%s' составляет %zu символов.\n", string, length);

  int i = 0;
  int j = 0;

  while (i < length)
  {
    // printf("текущий символ, %c и сработал блок ", string[i]);
    // "су", "лу", "ту"
    // if (i + 1 < length && (string[i] == 's' || string[i] == 'l' || string[i] == 't') && string[i + 1] == 'y')
    if (i + 1 < length && (string[i] == 'с' || string[i] == 'л' || string[i] == 'т') && string[i + 1] == 'у')
    {
      res[j] = 'у';
      j++;
      res[j] = 'у';
      j++;
      res[j] = string[i];
      j++;
      i += 2; // скипаем сразу 2 символа
    }
    else
    {
      res[j] = string[i];
      i++;
      j++;
    }
  }

  res[j] = '\0';

  return res;
}

char *decryptString(const char *string)
{
  int length = utf8_strlen(string);

  char *res = (char *)malloc((length + 1) * sizeof(char));

  if (res == NULL)
  {
    return NULL;
  };

  int i = 0;
  int j = 0;

  while (i < length)
  {
    // "уус", "уул", "уут"
    if (i + 2 < length && string[i] == 'у' && string[i + 1] == 'у' &&
        (string[i + 2] == 'с' || string[i + 2] == 'л' || string[i + 2] == 'т'))
    {
      res[j] = string[i + 2];
      j++;
      res[j] = 'у';
      j++;
      i += 3; // скипаем сразу 3 символа
    }
    else
    {
      res[j] = string[i];
      j++;
      i++;
    }
  }

  res[j] = '\0';
  return res;
}

void encryptFile(const char *filename)
{
  FILE *file = fopen(filename, "r");

  if (file == NULL)
  {
    printErrorMessage("Ошибка: файл ");
    printErrorMessage(filename);
    printErrorMessage(" не найден. Сначала создайте его (пункт 1).\n");
    return;
  }

  char *string = (char *)malloc(MAX_SIZE * sizeof(char));

  if (string == NULL)
  {
    fclose(file);
    return;
  }

  if (fgets(string, MAX_SIZE, file) == NULL)
  {
    printf("Файл пуст или его нет\n");
    fclose(file);
    free(string);
    return;
  }

  fclose(file);

  char *encrypted = encryptString(string);
  free(string);

  if (encrypted == NULL)
  {
    printErrorMessage("Ошибка выделения памяти при шифровании!\n");
    return;
  }

  file = fopen(filename, "w");

  if (file != NULL)
  {
    fprintf(file, "%s", encrypted);
    fclose(file);
    printSuccessMessage("Строка зашифрована и записана в файл.\n");
  }
  else
  {
    printErrorMessage("Ошибка записи в файл!\n");
  }

  free(encrypted);
}

void decryptFile(const char *filename)
{
  FILE *file = fopen(filename, "r");

  if (file == NULL)
  {
    printErrorMessage("Ошибка: файл ");
    printErrorMessage(filename);
    printErrorMessage(" не найден или пуст. Сначала выполните пункт 1.\n");
    return;
  }

  char *string = (char *)malloc(MAX_SIZE * sizeof(char));

  if (string == NULL)
  {
    fclose(file);
    return;
  }

  if (fgets(string, MAX_SIZE, file) == NULL)
  {
    printErrorMessage("Файл пуст, нечего расшифровывать.\n");
    fclose(file);
    free(string);
    return;
  }

  fclose(file);

  char *decrypted = decryptString(string);
  free(string);

  if (decrypted == NULL)
  {
    printErrorMessage("Ошибка выделения памяти при расшифровке!\n");
    return;
  }

  file = fopen(filename, "w");

  if (file != NULL)
  {
    fprintf(file, "%s", decrypted);
    fclose(file);
    printSuccessMessage("Строка расшифрована и записана в файл.\n");
  }
  else
  {
    printErrorMessage("Ошибка записи в файл!\n");
  }

  free(decrypted);
}
