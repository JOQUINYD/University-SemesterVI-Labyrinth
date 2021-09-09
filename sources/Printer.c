#include "../headers/Box.h"

void fontBlack(){
    printf("\033[0;30m");
}

void fontRed() {
  printf("\033[1;31m");
}

void fontWhite(){
    printf("\033[1;37m");
}

void fontBlue() {
    printf("\033[1;34m");
}

void fontPurple(){
    printf("\033[1;35m");
}

void fontReset(){
    printf("\033[0m");
}

void* printMatrix(Box** matrix, int numOfRows, int numOfCols, bool* done){
    while (!done)
    {
        for (int row = 0; row < numOfRows; row++)
        {
            for (int col = 0; col < numOfCols; col++)
            {
                switch (matrix[row][col].type)
                {
                case '*':
                    fontBlue();
                    printf("▓");
                    break;
                case ' ':
                    if(matrix[row][col].marked == true){
                        fontRed();
                        printf("█");
                    }
                    else{
                        fontWhite();
                        printf("▓");
                    }
                    break;
                case '/':
                        fontPurple();
                        printf("▒");
                    break;
                default:
                    break;
                }
                if(col == numOfCols-1){
                    printf("\n");
                }
            }   
        }
        printf("\n");

        usleep(300000);
    }
    fontReset();
}