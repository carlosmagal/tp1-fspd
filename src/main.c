#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// #include "func.h"
// #include "spend_time.c"

typedef struct {
    int tid;
    int ttype;
    int tsolo;
    int ttrio;
} t_struct;

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

int trio[3] = { -1, -1, -1 };

pthread_mutex_t lock;
pthread_cond_t condition1, condition2, condition3;
// vai ficar a logica de adicionar no trio
// dar lock
// pegar o vetor trio e ver se tem alguem do tipo dele(criar funcao)
// se tiver, entra no vetor
// se nao tiver, espera
// tira o lock
void trio_enter(t_struct data, int ttype)
{
    int idx = data.ttype - 1;

    pthread_mutex_lock(&lock);

    while (trio[0] != -1) {
        pthread_cond_wait(&condition1, &lock);
    }

    while (trio[1] != -1) {
        pthread_cond_wait(&condition2, &lock);
    }

    while (trio[2] != -1) {
        pthread_cond_wait(&condition3, &lock);
    }

    trio[idx] = data.tid;

    pthread_mutex_unlock(&lock);
}

// vai retirar do trio
// dar lock
// retira do trio
// dar um lock
// ver se tem que avisar qnd sair
void trio_leave(t_struct data, int ttype)
{
    int idx = data.ttype - 1;

    pthread_mutex_lock(&lock);

    trio[idx] = -1;

    switch (idx) {
    case 1:
        /* code */
        pthread_cond_signal(&condition1);
        break;

    default:
        break;
    }

    pthread_mutex_unlock(&lock);
}

void* create_threads(void* data)
{
    t_struct t_data = *((t_struct*)data);

    printf("threadIDDDDD: %d\n", t_data.ttype);

    // spend_time(t_data.tid, t_data.ttype, "S", );
    Sleep(t_data.tsolo);
    trio_enter(t_data, t_data.ttype);
    Sleep(t_data.ttrio);
    // spend_time(data.tid, data.ttype, "T", data.ttrio);
    // trio_leave(&trio, data.ttype);
    // pthread_exit(NULL);
    pthread_exit(NULL);
}

int main()
{
    int matrix[1000][4];
    const int rows = read_user_input(matrix);
    pthread_t threads[rows];
    t_struct* data = (t_struct*)malloc(sizeof(t_struct));

    data = input_to_struct(matrix, rows);
    printf("carlos\n");

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&condition1, NULL);
    pthread_cond_init(&condition2, NULL);
    pthread_cond_init(&condition3, NULL);

    printf("carlos11111\n");


    for (int i = 0; i < rows; i++) {
        pthread_create(&threads[i], NULL, create_threads, (void*)&data[i]);
    }
    printf("carlos2222\n");

    for (int i = 0; i < rows; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("carlos333\n");

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&condition1);
    pthread_cond_destroy(&condition2);
    pthread_cond_destroy(&condition3);

    return 0;
}
