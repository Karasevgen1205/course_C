#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#define MAX_SIZE 512
#define FILE_NAME "data.txt"

// Прототипы функций (функциональное разбиение)
void writeInputToFile(const char *filename);
void readAndPrintFromFile(const char *filename);
void encryptFile(const char *filename);
void decryptFile(const char *filename);
char *encryptString(const char *src);
char *decryptString(const char *src);
void clearInputBuffer();

int main()
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  int choice = 0;

  while (1)
  {
    printf("\n=== МЕНЮ ПРОГРАММЫ ===\n");
    printf("1 - Сформировать строку с клавиатуры и записать в файл\n");
    printf("2 - Считать строку из файла и распечатать\n");
    printf("3 - Зашифровать строку и записать в файл\n");
    printf("4 - Расшифровать строку и записать в файл\n");
    printf("5 - Выход\n");
    printf("Выберите пункт меню: ");

    if (scanf("%d", &choice) != 1)
    {
      printf("Ошибка ввода! Введите число от 1 до 5.\n");
      clearInputBuffer();
      continue;
    }
    clearInputBuffer(); // Очищаем буфер от символа '\n' после ввода числа

    switch (choice)
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
      printf("Выход из программы.\n");
      return 0;
    default:
      printf("Неверный пункт меню! Попробуйте снова.\n");
    }
  }

  return 0;
}

// Очистка буфера стандартного ввода
void clearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Пункт 1: Ввод строки с клавиатуры и запись в файл
void writeInputToFile(const char *filename)
{
  char *buffer = (char *)malloc(MAX_SIZE * sizeof(char));
  if (buffer == NULL)
  {
    printf("Ошибка выделения памяти!\n");
    return;
  }

  printf("Введите строку: ");
  if (fgets(buffer, MAX_SIZE, stdin) != NULL)
  {
    buffer[strcspn(buffer, "\n")] = '\0'; // Удаляем символ переноса строки
  }

  FILE *file = fopen(filename, "w");
  if (file == NULL)
  {
    printf("Ошибка открытия файла для записи!\n");
    free(buffer);
    return;
  }

  fprintf(file, "%s", buffer);
  fclose(file);
  free(buffer);

  printf("Строка успешно записана в файл '%s'.\n", filename);
}

// Пункт 2: Чтение строки из файла и вывод на экран
void readAndPrintFromFile(const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Ошибка: файл '%s' не найден или пуст. Сначала выполните пункт 1.\n", filename);
    return;
  }

  char *buffer = (char *)malloc(MAX_SIZE * sizeof(char));
  if (buffer == NULL)
  {
    printf("Ошибка выделения памяти!\n");
    fclose(file);
    return;
  }

  if (fgets(buffer, MAX_SIZE, file) != NULL)
  {
    printf("Содержимое файла: %s\n", buffer);
  }
  else
  {
    printf("Файл пуст.\n");
  }

  fclose(file);
  free(buffer);
}

// Функция шифрования: "су" -> "уус", "лу" -> "уул", "ту" -> "уут"
char *encryptString(const char *src)
{
  int len = strlen(src);
  // При шифровании 2 символа превращаются в 3, выделяем память с запасом (len * 1.5 + 1)
  char *res = (char *)malloc((len * 2 + 1) * sizeof(char));
  if (res == NULL)
    return NULL;

  int i = 0, j = 0;
  while (i < len)
  {
    // Проверяем пары символов: "су", "лу", "ту"
    if (i + 1 < len && (src[i] == 'с' || src[i] == 'л' || src[i] == 'т') && src[i + 1] == 'у')
    {
      res[j++] = 'у';
      res[j++] = 'у';
      res[j++] = src[i]; // Подставляем 'с', 'л' или 'т'
      i += 2;            // Перешагиваем через 2 обработанных символа
    }
    else
    {
      res[j++] = src[i++];
    }
  }
  res[j] = '\0';
  return res;
}

// Функция дешифрования: "уус" -> "су", "уул" -> "лу", "уут" -> "ту"
char *decryptString(const char *src)
{
  int len = strlen(src);
  // При расшифровке строка только уменьшается, достаточно len + 1
  char *res = (char *)malloc((len + 1) * sizeof(char));
  if (res == NULL)
    return NULL;

  int i = 0, j = 0;
  while (i < len)
  {
    // Проверяем тройки символов: "уус", "уул", "уут"
    if (i + 2 < len && src[i] == 'у' && src[i + 1] == 'у' &&
        (src[i + 2] == 'с' || src[i + 2] == 'л' || src[i + 2] == 'т'))
    {
      res[j++] = src[i + 2]; // Возвращаем 'с', 'л' или 'т' на первое место
      res[j++] = 'у';
      i += 3; // Перешагиваем через 3 обработанных символа
    }
    else
    {
      res[j++] = src[i++];
    }
  }
  res[j] = '\0';
  return res;
}

// Пункт 3: Чтение из файла, шифрование и перезапись файла
void encryptFile(const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Ошибка: файл '%s' не найден. Сначала создайте его (пункт 1).\n", filename);
    return;
  }

  char *buffer = (char *)malloc(MAX_SIZE * sizeof(char));
  if (buffer == NULL)
  {
    fclose(file);
    return;
  }

  if (fgets(buffer, MAX_SIZE, file) == NULL)
  {
    printf("Файл пуст, нечего шифровать.\n");
    fclose(file);
    free(buffer);
    return;
  }
  fclose(file);

  char *encrypted = encryptString(buffer);
  free(buffer);

  if (encrypted == NULL)
  {
    printf("Ошибка выделения памяти при шифровании!\n");
    return;
  }

  file = fopen(filename, "w");
  if (file != NULL)
  {
    fprintf(file, "%s", encrypted);
    fclose(file);
    printf("Строка зашифрована и записана в файл.\n");
  }
  else
  {
    printf("Ошибка записи в файл!\n");
  }

  free(encrypted);
}

// Пункт 4: Чтение из файла, дешифрование и перезапись файла
void decryptFile(const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Ошибка: файл '%s' не найден.\n", filename);
    return;
  }

  char *buffer = (char *)malloc(MAX_SIZE * sizeof(char));
  if (buffer == NULL)
  {
    fclose(file);
    return;
  }

  if (fgets(buffer, MAX_SIZE, file) == NULL)
  {
    printf("Файл пуст, нечего расшифровывать.\n");
    fclose(file);
    free(buffer);
    return;
  }
  fclose(file);

  char *decrypted = decryptString(buffer);
  free(buffer);

  if (decrypted == NULL)
  {
    printf("Ошибка выделения памяти при расшифровке!\n");
    return;
  }

  file = fopen(filename, "w");
  if (file != NULL)
  {
    fprintf(file, "%s", decrypted);
    fclose(file);
    printf("Строка расшифрована и записана в файл.\n");
  }
  else
  {
    printf("Ошибка записи в файл!\n");
  }

  free(decrypted);
}
