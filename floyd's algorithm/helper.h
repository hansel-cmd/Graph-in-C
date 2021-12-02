#ifndef helper_H
#define helper_H


void displayMatrix(MATRIX M)
{
    printf("%3c", ' ');
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("%4d ", i);

    for (int i = 0; i < MAX_VERTEX; i++) {
        printf("\n%d: ", i);
        for (int j = 0; j < MAX_VERTEX; j++)
            printf("%4d ", M[i][j]);
    }
}




#endif