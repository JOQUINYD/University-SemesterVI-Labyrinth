#include "../headers/MatrixInfo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getMatrixSize(MatrixInfo* self){
   FILE *file;
   
   /* Open a file for reading */
   file = fopen(self->path,"r");

   /* If it didn't open */
   if(file == NULL){
      perror("Error: Unable to open a file");
   } 
   
   else {
            int ch;
            char numTemp[2];
            char rowsTemp[10]="";
            char colsTemp[10]="";
            int equals;

            //Primer numero
            fgets(numTemp, 2, file);
            strcat(rowsTemp, numTemp);
            equals = strcmp(numTemp, " ");
            while(equals!=0){
                strcat(rowsTemp, fgets(numTemp, 2, file));
                equals = strcmp(numTemp, " ");
            }

            //Segundo numero
            fgets(numTemp, 2, file);
            strcat(colsTemp, numTemp);
            equals = strcmp(numTemp, "\n");
            while(equals!=0){
                strcat(colsTemp, fgets(numTemp, 2, file));
                equals = strcmp(numTemp, "\n");
            }

            /* printf("%s", rowsTemp);
            printf("%s", colsTemp); */

            self->rows = atoi(rowsTemp);
            self->columns = atoi(colsTemp);
        
            fclose(file);
        }
   
}

MatrixInfo* newMatrixInfo(char* path){
    //new
    MatrixInfo* self = (MatrixInfo*)malloc(sizeof(MatrixInfo));
    
    //atributes

    self->path = path; //Se deberia pedir por teclado

    self->getMatrixSize=getMatrixSize;

    self->getMatrixSize(self);
    
    return self;
}

Box** generateMatrix(MatrixInfo* self){
    
}

Box** crateMatrix(int rows, int cols){
    Box** matrix = malloc(rows * sizeof *matrix);
    for (int i=0; i<rows; i++)
    {
        matrix[i] = malloc(cols * sizeof *matrix[i]);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = *newBox(' ');
        }
        
    }
    
    return matrix;
}