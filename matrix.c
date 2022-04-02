#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **create_matrix(int row, int col);
int fill_data(int **matrix, int row, int col);
void print_matrix(int **matrix, int row, int col);
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col);
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col);
int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col);
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col);
int free_matrix(int **matrix, int row, int col);

int main() {
    char command;
    srand(time(NULL));
    printf("[----- [Won Jong Min] [2019038014] -----]\n");
    int row, col;

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);

    int **matrix_a = create_matrix(row, col);       //행렬 A, B, T를 생성
    int **matrix_b = create_matrix(row, col);
    int **matrix_t = create_matrix(col, row);

    if (matrix_a == NULL || matrix_b == NULL || matrix_t == NULL) {
        return -1;      //하나라도 만들어지지 않았을 때 오류출력
    }

    printf("Matrix Created.\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);     //커맨드 입력받음

        switch (command) {
            case 'z':   //z일때 랜덤배열 생성
            case 'Z':
                printf("Initialize Matrix\n");
                fill_data(matrix_a, row, col);
                fill_data(matrix_b, row, col);
                break;
            case 'p':
            case 'P':   //p일때 배열 출력
                printf("Print Matrix\n");
                printf("Matrix A\n");
                print_matrix(matrix_a, row, col);
                printf("Matrix B\n");
                print_matrix(matrix_b, row, col);
                break;
            case 'a':   //a일때 A, B행렬 더하기
            case 'A':
                printf("Addition Matrix\n");
                addition_matrix(matrix_a, matrix_b, row, col);
                break;
            case 's':   //s일때 A행렬에서 B행렬 빼기
            case 'S':
                printf("Subtraction Matrix\n");
                subtraction_matrix(matrix_a, matrix_b, row, col);
                break;
            case 't':   //t일때 A의 전치행렬 생성
            case 'T':
                printf("Transpose Matrix_A\n");
                transpose_matrix(matrix_a, matrix_t, col, row);
                print_matrix(matrix_t,col,row);
                break;
            case 'm':   //m일때 A와 A의 전치행렬 T를 곱함
            case 'M':   //바로 m을 입력하면 전치행렬T은 빈 배열이기 때문에 전치행렬 생성
                printf("Multiply Matrix\n");
                transpose_matrix(matrix_a, matrix_t, col, row);
                multiply_matrix(matrix_a, matrix_t, row, col);
                break;
            case 'q':   //q를 눌렀을때 모든 행렬 메모리 해제
            case 'Q':
                printf("Quit Matrix\n");
                free_matrix(matrix_a,row,col);
                free_matrix(matrix_b,row,col);
                free_matrix(matrix_t,row,col);
                break;
            default:
                printf("\n----------------------    Re-Enter!    -----------------------\n");
                break;
        }
    }while(command != 'Q' && command != 'q');   //q를 눌렀을때 

    return 0;
}

int **create_matrix(int row, int col) {
    if (row <= 0 || col <= 0) { //행과 열이 0보다 작으면 오류 출력
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **matrix = (int**)malloc(sizeof(int*) * row); // 2차원 배열을 주소*행 크기로 선언

    for (int i = 0; i < row; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * col); //각 행의 첫번째 열의 주소를 각행에 입력
    }

    if (matrix == NULL) { //행이 비어있다면 오류출력
        printf("Check the sizes of row and col!\n");
        return NULL;
    }
    return matrix;
}

int fill_data(int **matrix, int row, int col) {
    if (row <= 0 || col <= 0) { //행과 열이 0보다 작으면 오류 출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 20;
        }       //랜덤 배열 생성
    }

    if (matrix == NULL) { //행이 비어있다면 오류출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    return 1;
}

void print_matrix(int **matrix, int row, int col) {
    if (row <= 0 || col <= 0) { //행과 열이 0보다 작으면 오류 출력
        printf("Check the sizes of row and col!\n");
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%5d", matrix[i][j]);
        }       //행렬을 5칸 간격으로 출력
        printf("\n");
    }

    if (matrix == NULL) { //행이 비어있다면 오류출력
        printf("Check the sizes of row and col!\n");
    }
}

int addition_matrix(int **matrix_a, int **matrix_b, int row, int col) {
    if (row <= 0 || col <= 0) { //행과 열이 0보다 작으면 오류 출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    int **matrix_sum = (int **)malloc(sizeof(int *) * row);     //더한 값을 넣을 배열 생성
    for (int i = 0; i < row; i++) {
        matrix_sum[i] = (int *)malloc(sizeof(int) * col);
        for (int j = 0; j < col; j++) {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }       //생성한 배열의 각각의 값에 두 배열의 합을 넣음
    }
    print_matrix(matrix_sum, row, col);     //더한 값을 넣은 배열 출력
    free_matrix(matrix_sum,row,col);        //사용하고 필요없는 배열 메모리 해제

    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { //행이 비어있다면 오류출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    return 1;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col) {
    if (row <= 0 || col <= 0) { //행과 열이 0보다 작으면 오류 출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    int **matrix_sub = (int **)malloc(sizeof(int *) * row);     //뺀 값을 넣을 배열 생성
    for (int i = 0; i < row; i++) {
        matrix_sub[i] = (int *)malloc(sizeof(int) * col);
        for (int j = 0; j < col; j++) {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }       //생성한 배열의 각각의 값에 두 배열의 차를 넣음
    }
    print_matrix(matrix_sub, row, col);     //뺀 값을 넣은 배열을 출력
    free_matrix(matrix_sub,row,col);        //사용하고 필요없는 배열 메모리 해제

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { //행이 비어있다면 오류출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    return 1;
}

int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col) {
    if (row <= 0 || col <= 0) { //행과 열이 0보다 작으면 오류 출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_t[i][j] = matrix_a[j][i];
        }   //행과 열을 교환하여 대입
    }

    if (matrix_a == NULL || matrix_t == NULL) { //행이 비어있다면 오류출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    return 1;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col) {
    if (row <= 0 || col <= 0) { //행과 열이 0보다 작으면 오류 출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    int **mul_matrix = create_matrix(row,row);       //곱한 값을 넣을 2차원 배열 생성

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            mul_matrix[i][j] = 0;               //0으로 초기화를 해야 쓰레기 값으로 인한 오류가 생기지 않음
            for(int k = 0; k < col; k++) {      //mul행렬의 ij행에 a행렬의 ik값과 A전치행렬의 kj값을 곱한 후 더함
                mul_matrix[i][j] += matrix_a[i][k] * matrix_t[k][j];
            }
        }
    }

    print_matrix(mul_matrix, row, row);
    free_matrix(mul_matrix,row,col);

    if (matrix_a == NULL || matrix_t == NULL) { //행이 비어있다면 오류출력
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    return 1;
}

int free_matrix(int **matrix, int row, int col){
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
        return -1;
	}

	for (int i= 0; i < row; i++) {
		free(matrix[i]);    //우선 각 열에 선언된 동적배열 메모리 해제
	}

	free(matrix);   //그 후 그 열을 선언 했던 동적배열 메모리 해제
    return 1;
}