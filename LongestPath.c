#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

struct node {
    int lp_len; // lp - самый длинный путь
    int lp_count;
};

void node_init(struct node* new_node, int is_s);
int** adj_matrix_init(int N);
void adj_matrix_free(int N, int** adj_matrix);
// void node_compare(int i, int j);

int main(int argc, char const* argv[])
{
    setlocale(0, "");
    int N;
    int M;

    printf("Укажите количество вершин графа: ");
    scanf("%d", &N);

    // printf("%d\n", N);
    printf("Укажите количество рёбер в графе: ");
    scanf("%d", &M);
    // printf("%d\n", M);

    // заполнение матрицы смежности
    int** adj_matrix = adj_matrix_init(N);
    int a;
    int b;

    for (int i = 0; i < M; i++) {
        printf("Введите начальную вершину, конечную и длину пути (например: 1 "
               "4 10): ");
        int l;
        scanf("%d %d %d", &a, &b, &l);
        adj_matrix[a - 1][b - 1] = l;
    }

    // формирование массива вершин
    struct node* node_array = malloc(sizeof(struct node) * N);
    node_init(&node_array[0], 1);

    for (int i = 1; i < N; i++) {
        node_init(&node_array[i], 0);
    }

    // цикл по матрице и обновление характеристик вершин
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (adj_matrix[i][j] != 0) {
                if (node_array[j].lp_len
                    < node_array[i].lp_len + adj_matrix[i][j]) {
                    node_array[j].lp_len
                            = node_array[i].lp_len + adj_matrix[i][j];
                    node_array[j].lp_count = node_array[i].lp_count;
                } else if (
                        node_array[j].lp_len
                        == node_array[i].lp_len + adj_matrix[i][j]) {
                    node_array[j].lp_count += node_array[i].lp_count;
                }
            }
        }
    }
    printf("Самый длинный путь: %d\n", node_array[N - 1].lp_len);
    printf("Количество самых длинных путей: %d\n", node_array[N - 1].lp_count);

    free(node_array);
    adj_matrix_free(N, adj_matrix);

    return 0;
}

void node_init(struct node* new_node, int is_s)
{ // создание нового узла, если ошибка, то возвращается NULL
    if (new_node != NULL) {
        if (is_s) {
            new_node->lp_len = 0;
            new_node->lp_count = 1;
        } else {
            new_node->lp_len = INT_MIN; // максимальная длина равна самому
                                        // минимальному int
            new_node->lp_count = 0;
        }
    };
}

int** adj_matrix_init(int N)
{
    int** adj_matrix = malloc(sizeof(int*) * N);
    if (adj_matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < N; i++) {
        adj_matrix[i] = malloc(sizeof(int) * N);
        if (adj_matrix[i] == NULL) {
            free(adj_matrix);
            for (int j = 0; j < i; j++) {
                free(adj_matrix[j]);
            }
            return NULL;
        }
        for (int j = 0; j < N; j++) {
            adj_matrix[i][j] = 0;
        }
    }
    return adj_matrix;
}

void adj_matrix_free(int N, int** adj_matrix)
{
    for (int i = 0; i < N; i++) {
        free(adj_matrix[i]);
    }
    free(adj_matrix);
}