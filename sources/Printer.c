#include "../headers/Box.h"
#include "../headers/PrinterInfo.h"

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

void* printMatrix(void* printInfo_i){

    PrinterInfo *printerInfo = (PrinterInfo*)(printInfo_i);

    Box** matrix = printerInfo->matrix;
    int numOfRows = printerInfo->numOfRows;
    int numOfCols = printerInfo->numOfCols;
    bool* done = printerInfo->done;

    while (!(*done))
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
                        switch (matrix[row][col].first)
                        {
                        case 'u':
                            printf("⇧");
                            break;
                        case 'd':
                            printf("⇩");
                            break;
                        case 'r':
                            printf("⇨");
                            break;
                        case 'l':
                            printf("⇦");
                            break;
                        default:
                            printf("▓");
                            break;
                        }
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