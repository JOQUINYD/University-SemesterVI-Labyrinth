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

char** generateMatrixChars(MatrixInfo* self){
    FILE *fp = fopen(self->path, "r");
    if(fp == NULL) {
         perror("Unable to open file!");
        exit(1);
    }
 
    char chunk[128];

    fgets(chunk, sizeof(chunk), fp); //ignoramos la primera
    
    char** matrix = malloc(self->rows * sizeof *matrix);
    for (int i=0; i<self->rows; i++)
    {
        matrix[i] = malloc(self->columns * sizeof *matrix[i]);
    }

    int i = 0;
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
        for (int j = 0; j < self->columns; j++)
        {
            matrix[i][j] = chunk[j];
        } 
        i++;
    }

    for (int i = 0; i < self->rows; i++)
        {
            
            for (int j = 0; j < self->columns; j++)
            {
                //printf("%c\n", lineTmp[j]);
                printf("%c", matrix[i][j]);
                
                //printf("%c",matrix[i][j]);
            }
            printf("\n");
        }

    fclose(fp);

  /*  FILE *file;
   
    /* Open a file for reading 
    file = fopen(self->path,"r");

    /* If it didn't open 
    if(file == NULL){
        perror("Error: Unable to open a file");
    } 
    
    else {
        
         char line[128];
        fgets(line, 128, file);
        

        char** matrix = malloc(self->rows * sizeof *matrix);
        for (int i=0; i<self->rows; i++)
        {
            matrix[i] = malloc(self->columns * sizeof *matrix[i]);
        }

        for (int i = 0; i < self->rows; i++)
        {
            char lineTmp[128];
            fgets(lineTmp, self->columns+1, file);
            printf("%s",lineTmp);
            printf("%d", self->rows);
            
            for (int j = 0; j < self->columns; j++)
            {
                //printf("%c\n", lineTmp[j]);
                matrix[i][j] = lineTmp[j];
                //printf("%c",matrix[i][j]);
            } */
        //}
        
        //return matrix;
    //}
}

/* Box** crateMatrix(int rows, int cols){
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
} */

MatrixInfo* newMatrixInfo(char* path){
    //new
    MatrixInfo* self = (MatrixInfo*)malloc(sizeof(MatrixInfo));
    
    //atributes

    self->path = path; //Se deberia pedir por teclado

    self->getMatrixSize=getMatrixSize;

    self->getMatrixSize(self);

    self->generateMatrixChars=generateMatrixChars;

    self->generateMatrixChars(self);
    
    return self;
}

