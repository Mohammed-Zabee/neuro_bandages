#pragma once
#include <math.h>

#include <string.h>
void add_vectors(double *v1, double *v2, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] + v2[i];
}
void mul_vector_number(double *v1, double num, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] * num;
}
void score(double * input, double * output) {
    double var0[2];
    double var1[2];
    double var2[2];
    double var3[2];
    double var4[2];
    double var5[2];
    if (input[0] <= 6.849379301071167) {
        memcpy(var5, (double[]){1.0, 0.0}, 2 * sizeof(double));
    } else {
        memcpy(var5, (double[]){0.0, 1.0}, 2 * sizeof(double));
    }
    double var6[2];
    if (input[2] <= 35.405168533325195) {
        memcpy(var6, (double[]){1.0, 0.0}, 2 * sizeof(double));
    } else {
        memcpy(var6, (double[]){0.0, 1.0}, 2 * sizeof(double));
    }
    add_vectors(var5, var6, 2, var4);
    double var7[2];
    if (input[1] <= 5.254596829414368) {
        memcpy(var7, (double[]){0.0, 1.0}, 2 * sizeof(double));
    } else {
        memcpy(var7, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var4, var7, 2, var3);
    double var8[2];
    if (input[2] <= 35.406166076660156) {
        memcpy(var8, (double[]){1.0, 0.0}, 2 * sizeof(double));
    } else {
        memcpy(var8, (double[]){0.0, 1.0}, 2 * sizeof(double));
    }
    add_vectors(var3, var8, 2, var2);
    double var9[2];
    if (input[2] <= 35.40657424926758) {
        memcpy(var9, (double[]){1.0, 0.0}, 2 * sizeof(double));
    } else {
        memcpy(var9, (double[]){0.0, 1.0}, 2 * sizeof(double));
    }
    add_vectors(var2, var9, 2, var1);
    mul_vector_number(var1, 0.2, 2, var0);
    memcpy(output, var0, 2 * sizeof(double));
}
