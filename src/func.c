#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "func.h"

// le dados do input ate EOF, retorna numero de linhas
int read_user_input(int matrix[1000][4])
{
    int rows = 0, columns = 0;
    int input;

    while (scanf("%d", &input) != EOF) {
        matrix[rows][columns] = input;
        columns++;

        if (columns == 4) {
            columns = 0;
            rows++;
        }
    }

    return rows;
}

t_struct* input_to_struct(int matrix[][4], int rows)
{
    t_struct* data = (t_struct*)malloc(sizeof(t_struct));

    for (int i = 0; i < rows; i++) {
        data[i].tid = matrix[i][0];
        data[i].ttype = matrix[i][1];
        data[i].tsolo = matrix[i][2];
        data[i].ttrio = matrix[i][3];
    }

    return data;
}