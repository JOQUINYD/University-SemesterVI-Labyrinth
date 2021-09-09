#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void readMatrix(){
   FILE *file;
   int ch;
   char size[2][11];
    
   /* Open a file for reading */
   file = fopen("/home/mela227/Downloads/lab1.txt","r");

   /* If it didn't open */
   if(file == NULL){
      perror("Error: Unable to open a file");
   } 
   
   else {
         getMatrixSize(file);
         //char sizeRes[2][11] = getMatrixSize(file);
         //strcpy(size[0], sizeRes[0]);
         //strcpy(size[1], sizeRes[1]);
       /* while(!feof(file)){
          ch = fgetc(file);
          if (ch)
          int rows = getw(file);
          int columns = getw(file);
          
          printf("%c", ch);
       } */
       fclose(file);
   }
}

void getMatrixSize(FILE *file){
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

   //printf("%s", rowsTemp);

   fgets(numTemp, 2, file);
   strcat(colsTemp, numTemp);
   equals = strcmp(numTemp, "\n");
   while(equals!=0){
      strcat(colsTemp, fgets(numTemp, 2, file));
      equals = strcmp(numTemp, "\n");
   }

   //printf("\n%s", colsTemp);

   char strs[2][11];
   strcpy(strs[0], rowsTemp);
   strcpy(strs[1], colsTemp);
   
   printf("\n%s", strs[0]);
   printf("\n%s", strs[1]);

   //return strs;
}


/*
void readMatrix(){
   FILE *file;
   int ch;
    
   Open a file for reading
   file = fopen("/home/mela227/Downloads/lab2.txt","r");

    If it didn't open
   if(file == NULL){
      perror("Error: Unable to open a file");
   } 
   
   else {
       while(!feof(file)){
          ch = fgetc(file);
          printf("%c", ch);
       }
       fclose(file);
   }
}
*/