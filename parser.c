/* 876700 Paolo Concolato */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

/*
* La funzione leggi costituisce l'intero parsing del file.
* Controlla la presenza di caratteri non "idonei", eliminandoli, e salva invece
* tutti i numeri del codice macchina in un array allocato dinamicamente.
*/

int check(char *buffer, int rif, int *flag, int count){
  if (buffer[rif]==' '){
      rif++;
  }
  if (buffer[rif] == ';'){
      buffer[rif] = '\0';
      while(rif!=count){
          rif++;
          buffer[rif]=' ';
      }
  }
  if (buffer[rif]==45 && (buffer[rif+1]>47 || buffer[rif+1]<58)){
      rif++;
  }else{
      if (buffer[rif]<48 || buffer[rif]>57){
          buffer[rif]=' ';
          rif++;
      }else{
          flag=1;
          rif++;
      }
  }
  return rif;
}

void leggi(char *input){
  FILE* stream;
  char *buffer=NULL;
  size_t size = 1;
  int count; /* Buffer */
  int rif=0; /* Scorrere il buffer */
  int riga=0; /* Distinguere la prima riga */
  int g=0; /* Scorrere l'array */
  int command; /* Salva la riga "pulita" */
  int flag; /* Flag per copia riga */
  int r=0;
  int stop; /* Flag per la free */
  dim=(int*)malloc(sizeof(int));
  run=(int*)malloc(sizeof(int));
  run[r]=1;
  dim[r]=0;

  /* Controllo esistenza File */
  stream = fopen(input, "r");
  if (stream==NULL){
      printf("Errore apertura file\n");
      run=0;
      stop=0;
  }else{
  /* Controllo righe del file */
    buffer = (char *)malloc(size * sizeof(char));
    stop=1;
    while((count=getline(&buffer,&size,stream))!=-1 && run){
      flag=0;
      rif=0;
      while (rif<count){
        rif = check(buffer, rif, &flag, count);
      }
      /* Salva i valori del codice macchina nell'array */
      if (flag){
        command = atoi(buffer);
        if (riga == 0 ){
          dim[0]=command;
          program = (int * )malloc(sizeof(int )* command);
          riga=1;
        }else{
          if (g==dim[0]){
            printf("File non valido.\n");
            run=0;
          }else{
            program[g]=command;
            g++;
          }
        }
      }
    }
  }
  if (stop!=0){
    fclose(stream);
    free(buffer);
  }
}
