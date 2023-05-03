#ifndef FUNC_H
#define FUNC_H

typedef struct {
    int tid;
    int ttype;
    int tsolo;
    int ttrio;
} t_struct;

int read_user_input(int matrix[][4]);
t_struct* input_to_struct(int matrix[][4], int rows);

#endif