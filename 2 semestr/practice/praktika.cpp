#include <iostream>

#define NO_MEMORY_ERROR -3;
#define NO_FILE -2;
#define WORK_FINIESHED 0
#define MAXLEN 255

FILE *fl;

void FloydMarshallAlghoritm(int **arr, int size);
int userInterface();

int main() {

    while (1) {
        int vertexCount;
        int **matrix;

        switch (userInterface()) {
            default:
                printf("Такой опции не существует, попробуйте еще раз.\n\n");
                break;
            case 0:
                return WORK_FINIESHED;
                break;
            case 1:
                char inputFilename[MAXLEN];
                printf("\n\nВведите имя файла с матрицей весов рёбер: ");
                scanf("%s", inputFilename);

                if (!(fl = fopen(inputFilename, "r"))) {
                    printf("Не удалось открыть файл под заданым именем.");
                    return NO_FILE;
                }
                vertexCount = 0;
                fflush(stdin);
                fscanf(fl, "%d", &vertexCount);
                matrix = (int **) malloc (vertexCount * sizeof(int *));
                for (int i = 0; i < vertexCount; i++)
                    matrix[i] = (int *) malloc(vertexCount * sizeof(int));

                if (!matrix) {
                    printf("\nНедостаточно свободной памяти.");
                    return NO_MEMORY_ERROR;
                }

                for (int i = 0; i < vertexCount; i++) {
                    for (int j = 0; j < vertexCount; j++) {
                        fscanf(fl, "%d", &matrix[i][j]);
                    }
                }
                fclose(fl);

                printf("Матрица кратчайших путей после алгоритма Флойда-Уоршелла\n");
                FloydMarshallAlghoritm(matrix, vertexCount);

                printf("\nВведите название файла для сохранения результата\n > ");
                fflush(stdin);
                char outputFilename[MAXLEN];
                scanf("%s", outputFilename);
                fl = fopen(outputFilename, "w");
                for (int i = 0; i < vertexCount; i++) {
                    for (int j = 0; j < vertexCount; j++) {
                        fprintf(fl, "%3d", matrix[i][j]);
                    }
                    fprintf(fl, "\n");
                }
                fclose(fl);

                for (int i = 0; i < vertexCount; i++)
                    free(matrix[i]);
                free(matrix);
                break;
            case 2:
                bool flag = false;
                vertexCount = 0;
                while (flag == false) {
                    printf("Введите количество вершин ориентированного графа: ");
                    fflush(stdin);
                    scanf("%d", &vertexCount);
                    if (vertexCount > 2)
                        flag = true;
                }

                matrix = (int **) malloc (vertexCount * sizeof(int *));
                for (int i = 0; i < vertexCount; i++)
                    matrix[i] = (int *) malloc(vertexCount * sizeof(int));

                if (!matrix) {
                    printf("\nНедостаточно свободной памяти.");
                    return NO_MEMORY_ERROR;
                }

                printf("Введите матрицу веса рёбер в ориентированном графе.");
                for (int i = 0; i < vertexCount; i++) {
                    for (int j = i + 1; j < vertexCount; j++) {
                        int temp;
                        std::cin >> temp;
                        matrix[i][j] = temp;
                        matrix[j][i] = temp;
                    }
                }

              printf("Матрица кратчайших путей после алгоритма Флойда-Уоршелла\n");
                FloydMarshallAlghoritm(matrix, vertexCount);

                for (int i = 0; i < vertexCount; i++)
                    free(matrix[i]);
                free(matrix);
                break;
        }
    }
}



void FloydMarshallAlghoritm(int **arr, int size) {
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr[i][k] && arr[k][j] && i != j)
                    if (arr[i][k] + arr[k][j] < arr[i][j] || arr[i][j] == 0)
                        arr[i][j] = arr[i][k] + arr[k][j];
            }
        }
    }

    // Вывод конечной матрицы кратчайших путей
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%4d", arr[i][j]);
        }
        std::cout << std::endl;
    }
    return;
}


int userInterface() {
    int userOption = 0;
    printf("Выберите метод для ввода информации о матрице весов ребер.\n");
    printf("1 - Ввод информации через файл.\n");
    printf("2 - Ввод информации через консоль.\n");
    printf("0 - Выход из программы.\n > ");
    fflush(stdin);
    scanf("%d", &userOption);

    return userOption;
}