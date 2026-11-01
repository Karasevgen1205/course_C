#ifndef UTILS_H
#define UTILS_H

int getMatrix(int *n, int *m, int ***matrix);
int setMatrixData(int *n, int *m, int ***matrix);
void printMatrix(int *n, int *m, int ***matrix);
void freeMatrix(int *n, int ***matrix);

#endif
