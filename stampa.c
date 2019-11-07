/* 876700  Paolo Concolato */

#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "parser.h"

/* Instruction pointer */
static unsigned int ip_s = 0;

/* Flag per la gestione delle free in caso di errore. */
static int ok_s=0;

/*
* Corpo centrale del programma, ogni case contiene le specifiche da stampare
* equivalenti ai parametri delle varie istruzioni.
* L'instruction pointer viene aumentato nella funzione esegui
* per una miglior gestione delle operazioni.
* L'incremento nei singoli casi è per accedere ai parametri
* legati alle relative istruzioni.
*/
void valuta_stampa(int istr){
  switch(istr){
    case HALT:{
      printf("[%d] HALT\n", ip_s);
      break;
    }
    case PUSH:{
      p1=program[ip_s+1];
      printf("[%d] PUSH R%d\n", ip_s, p1);
      ip_s+=1;
      break;
    }
    case POP:{
      p1=program[ip_s+1];
      printf("[%d] POP R%d\n", ip_s, p1);
      ip_s+=1;
      break;
    }
    case ADD:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      p3=program[ip_s+3];
      printf("[%d] ADD R%d R%d R%d\n", ip_s, p1, p2, p3);
      ip_s+=3;
      break;
    }
    case SUB:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      p3=program[ip_s+3];
      printf("[%d] SUB R%d R%d R%d\n", ip_s, p1, p2, p3);
      ip_s+=3;
      break;
    }
    case MUL:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      p3=program[ip_s+3];
      printf("[%d] MUL R%d R%d R%d\n", ip_s, p1, p2, p3);
      ip_s+=3;
      break;
    }
    case DIV:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      p3=program[ip_s+3];
      printf("[%d] DIV R%d R%d R%d\n", ip_s, p1, p2, p3);
      ip_s+=3;
      break;
    }
    case DISPLAY:{
      p1=program[ip_s+1];
      if (p1==-1){
        printf("[%d] DISPLAY %d\n", ip_s, p1);
      }else{
        printf("[%d] DISPLAY R%d\n", ip_s, p1);
      }
      ip_s+=1;
      break;
    }
    case PRINT_STACK:{
      p1=program[ip_s+1];
      printf("[%d] PRINT_STACK %d\n", ip_s, p1);
      ip_s+=1;
      break;
    }
    case MOV:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      printf("[%d] MOV R%d %d\n", ip_s, p1, p2);
      ip_s+=2;
      break;
    }
    case JMP:{
      p1=program[ip_s+1];
      printf("[%d] JMP %d\n", ip_s, p1);
      ip_s+=1;
      break;
    }
    case JZ:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      printf("[%d] JZ %d R%d\n", ip_s, p1, p2);
      ip_s+=2;
      break;
    }
    case JPOS:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      printf("[%d] JPOS %d R%d\n", ip_s, p1, p2);
      ip_s+=2;
      break;
    }
    case JNEG:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      printf("[%d] JNEG %d R%d\n", ip_s, p1, p2);
      ip_s+=2;
      break;
    }
    case CALL:{
      p1=program[ip_s+1];
      printf("[%d] CALL %d\n", ip_s, p1);
      ip_s+=1;
      break;
    }
    case RET:{
      printf("[%d] RET\n", ip_s);
      break;
    }
    case JCR:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      p3=program[ip_s+3];
      printf("[%d] JCR %d R%d R%d\n", ip_s, p1, p2, p3);
      ip_s+=3;
      break;
    }
    case JCN:{
      p1=program[ip_s+1];
      p2=program[ip_s+2];
      p3=program[ip_s+3];
      printf("[%d] JCN %d R%d %d\n", ip_s, p1, p2, p3);
      ip_s+=3;
      break;
    }
    default:{
      printf("\nIstruzione non riconosciuta: [%d] -> %d\n", ip_s, program[ip_s]);
      run=0;
      break;
    }
    break;
  }
}

/*
* Prende in input il file da leggere e, dopo averlo parsato
* (vedi Parser), finchè la flag run è attiva viene stampato il
* comando presente nello switch che corrisponde ai valori salvati
* nell'array dinamico program.
*/
void stampa(char *argv){
  unsigned int doppio=0;
  char *input;
  input=argv;
  leggi(input);
  doppio=dim[0];
  while(ip_s < doppio && run){
    ok_s=1;
    valuta_stampa(program[ip_s]);
    ip_s++;
  }
  if (ok_s==1){
    free(program);
  }
  free(run);
  free(dim);
  printf("\nFine Programma\n");
}
