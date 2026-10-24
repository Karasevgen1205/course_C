#include <stdio.h>
#include <math.h>
#include <windows.h>

// #define  EPS 10e-4;
double EPS = 10e-4;

int task1(void);
int task2(void);

int main()
{
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  task1();
  // task2();
}

int task1()
{
  double a, b, h, x, res, y, s, delta;
  int n, i, k;

  // system("cls");
  // fflush(stdin);

  // printf("Введите значение а:");
  // scanf_s(" %lf", &a);
  // printf("Введите значение b:");
  // scanf_s(" %lf", &b);
  // printf("Введите значение h:");
  // scanf_s(" %lf", &h);
  // printf("Введите значение n:");
  // scanf_s(" %d", &n);
  a = 0.1;
  b = 1.0;
  h = 0.1;
  n = 20;

  printf("\n");
  printf("-------------------------------------------------------------\n");
  printf("|    x    |    Y(x)    |    S(x)    |  Y(x) - S(x)  |\n");
  printf("-------------------------------------------------------------\n");

  x = a;

  while (x <= b)
  {
    s = 0;

    for (k = 0; k <= n; k++)
    {
      res = 1;

      for (i = 1; i <= k; i++)
      {
        res *= i;
      }

      s += ((2 * k + 1) / res) * pow(x, 2 * k);
    }

    y = (1 + 2 * pow(x, 2)) * exp(pow(x, 2));
    delta = fabs(y - s);

    printf("\n |  %.2lf  |  %.5lf   |  %.5lf   |    %.5lf    | \n", x, y, s, delta);

    x += h;
  }

  system("pause");

  return 1;
}

double getValue(double x)
{
  return log(x) - 5 * pow(sin(x), 2);
};

void divByTwo(double x1, double x2)
{
  double x0;
  double y0;
  double y1;
  double y2;

  double tempX1 = x1;
  double tempX2 = x2;

  int count = 0;

  do
  {
    x0 = (x2 + x1) / 2;
    y0 = getValue(x0);
    count++;

    if (fabs(y0) < EPS)
    {
      printf("На отрезке [%.2lf ; %.2lf] при x = %.3lf y = %.4lf количесвто итераций = %d\n", tempX1, tempX2, x0, y0, count);
      break;
    }
    else
    {
      y1 = getValue(x1);
      y2 = getValue(x2);

      if (y1 * y0 < 0)
      {
        x2 = x0;
      }
      else
      {
        x1 = x0;
      }
    }
  } while (1);
}

void iter(double x1, double x2)
{
  double result;
  int count = 0;

  for (double i = x1; i <= x2; i += EPS)
  {
    result = getValue(i);
    count++;

    if (fabs(result) < EPS)
    {
      printf("На отрезке [%.2lf ; %.2lf] при x = %.3lf y = %.4lf количесвто итераций = %d\n", x1, x2, i, result, count);
      break;
    }
  }
}

int task2()
{
  double left = 2;
  double right = 6;
  double numb = 20;
  double step = (right - left) / numb;
  double x;
  double y1;
  double y2;

  x = left;

  while (x <= right)
  {
    y1 = getValue(x);
    y2 = getValue(x + step);

    if (y1 * y2 < 0)
    {
      // 1 часть задания
      // printf("На [%.2lf ; %.2lf] y1 = %.3lf y2 = %.3lf\n", x, x + step, y1, y2);
      // 2 часть задания
      // iter(x, x + step);
      // 3 часть задания
      // divByTwo(x, x + step);
      // 4 часть задания
    }

    x += step;
  }

  return 0;
}
