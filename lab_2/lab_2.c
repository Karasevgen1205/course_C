#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <process.h>
#include <locale.h>

#define PI 3.1415926

void task1(void);
void task2(void);
int task3(void);
int task4(void);
int task5(void);
void selectTask(void);

void main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    selectTask();
}

void selectTask()
{
    system("cls"); // очистка консоли

    int taskId;

    printf("Введите номер задания для проверки:\n");

    scanf_s(" %d", &taskId);

    switch (taskId)
    {
    case 1:
        task1();
        break;
    case 2:
        task2();
        break;
    case 3:
        task3();
        break;
    case 4:
        task4();
        break;
    case 5:
        task5();
        break;
    default:
        printf("Такого задания нет\n");
        _getch();
    }
}

void task1()
{
    system("cls"); // очистка консоли

    printf("Задание 1\n");

    double a, a1, a2, z1, z2;

    printf("Введите значение угла а: ");

    scanf_s(" %lf", &a);

    z1 = cos(a) + cos(2 * a) + cos(6 * a) + cos(7 * a);

    z2 = 4 * cos(a / 2.) * cos(5 / 2. * a) * cos(4 * a);

    printf("\nРезультаты работы: z1=%.4lf z2=%.4lf\n", z1, z2);

    _getch();

    selectTask();
}

void task2()
{
    system("cls"); // очистка консоли

    printf("Задание 2\n");

    double x, y, z, r1, r2, r3;

    // x = 16.55 * pow(10, -3);
    // y = -2.75;
    // z = 0.15;

    printf("Введите значение x: ");
    scanf_s(" %lf", &x);

    printf("Введите значение y: ");
    scanf_s(" %lf", &y);

    printf("Введите значение z: ");
    scanf_s(" %lf", &z);

    r1 = sqrt(10 * (cbrt(x) + pow(x, y + 2))); // sqrt - квадратный корень, cbrt - кубический корень

    r2 = pow(asin(z), 2) - fabs(x - y); // fabs - модуль

    r3 = r1 * r2;

    printf("\nРезультаты работы: %.4lf\n", r3);

    _getch();

    selectTask();
}

int task3()
{
    system("cls"); // очистка консоли

    printf("Задание 3\n");

    double z, x, r1, r2, r3;

    printf("Введите значение z: ");
    scanf_s(" %lf", &z);

    if (z == 0)
    {
        printf("Выполнить операцию с z == 0 невозможно!");

        _getch();

        selectTask();

        return 0;
    }

    const short isPositive = z > 0;

    x = isPositive ? sin(z) : z;
    printf(isPositive ? "Значение z > 0" : "Значение z < 0");

    r1 = 2 / 3. * pow(sin(x), 2);

    r2 = 3 / 4. * pow(cos(x), 2);

    r3 = r1 * r2;

    printf("\nРезультаты работы: %.4lf\n", r3);

    _getch();

    selectTask();

    return 0;
}

int task4()
{
    system("cls"); // очистка консоли

    printf("Задание 4\n");

    double x, y, z, max1, max2, min, result;

    void setData()
    {
        printf("Введите значение x: ");
        scanf_s(" %lf", &x);

        printf("Введите значение y: ");
        scanf_s(" %lf", &y);

        printf("Введите значение z: ");
        scanf_s(" %lf", &z);
    };

    boolean getIsEquals(double x, double y, double z)
    {

        return (x == y || x == z || y == z);
    };

    boolean getIsSomeValueIsZero(double x, double y, double z)
    {
        return (x == 0 || x == 0 || y == 0);
    };

    setData();

    const short isEquals = getIsEquals(x, y, z);
    const short isSomeValueIsZero = getIsSomeValueIsZero(x, y, z);

    if (isEquals || isSomeValueIsZero)
    {
        printf(isEquals ? "Одинаковые значения вводить нельзя, введите заново\n" : "Вводить ноль вводить нельзя, введите заново\n");

        setData();

        const short isEquals = getIsEquals(x, y, z);
        const short isSomeValueIsZero = getIsSomeValueIsZero(x, y, z);

        if (isEquals || isSomeValueIsZero)
        {
            printf("Хорошая попытка но попыток больше нет\n");

            _getch();

            selectTask();

            return 0;
        }
    }

    max1 = x > y ? x : y;

    max2 = y > z ? y : z;

    min = max1 > max2 ? max2 : max1;

    result = min / max2;

    printf("\nРезультаты работы: %.4lf\n", result);

    _getch();

    selectTask();

    return 0;
}

int task5()
{
    system("cls"); // очистка консоли

    printf("Задание 5\n");

    double n1, n2, sum, result;

    printf("Введите значение n1: ");
    scanf_s(" %lf", &n1);

    printf("Введите значение n2: ");
    scanf_s(" %lf", &n2);

    sum = n1 + n2;

    if (sum >= PI && sum < 5)
    {
        printf("Сумма n1 и n2 больше или равно числа П и меньше 5\n");
        result = pow(sin(PI * n1 + exp(n2)), 2);
    }
    else if (sum >= 5)
    {
        printf("Сумма n1 и n2 больше или равно 5\n");
        result = pow(sin(PI * n2 + n1), 2);
    }
    else
    {
        printf("Сумма n1 и n2 меньше числа П.\nПрограмма завершена.\n");

        _getch();

        selectTask();

        return 0;
    }

    printf("\nРезультаты работы: t2=%.4lf\n", result);

    _getch();

    selectTask();

    return 0;
}