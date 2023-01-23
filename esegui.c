/* 876700  Paolo Concolato */

#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "parser.h"

/* Instruction pointer */
static unsigned int ip_e = 0;

/* Flag per la gestione delle free in caso di errore. */
static int ok_e=0;

/*
* Indica la posizione in cui scrivere, non quella attuale.
* Quindi se 0 vuo dire che siamo alla posizione -1.
*/
unsigned int sp_e = 0;

/*
* Utilizzato per castare le operazioni aritmetiche, valutando
* l'overflow prima che dia errore.
*/
long cast_overflow;

/*
* Valori massimi dentro il quale non è overflow.
* Estremi di un int.
*/
long max = 2147483647;
long min = -2147483648;


/* Indice per la stampa dei singoli registri con DISPLAY (-1). */
int i=0;

/*
* Corpo centrale del programma, ogni case contiene le relative
* operazioni corrispondenti al codice memonico.
* L'instruction pointer viene aumentato nella funzione esegui
* per una miglior gestione delle operazioni.
* L'incremento nei singoli casi è per accedere ai parametri
* legati alle relative istruzioni.
*/

/*
* Funzioni refactoring
*/

void push(){
  if (sp_e>=16384){
    printf("\nErrore Stack Overflow\n");
    valuta_esegui(0);
  }else{
    ip_e++;
    if (program[ip_e]<0 || program[ip_e]>31){
      printf("\nErrore registro\n");
      valuta_esegui(0);
    }else{
      stack[sp_e] = registers[program[ip_e]];
      sp_e++;
    }
  }
}

void pop(){
  if (sp_e==0){
    printf("\nErrore Stack Underflow\n");
    valuta_esegui(0);
  }else if(sp_e>16384){
    printf("\nErrore Stack Overflow\n");
    valuta_esegui(0);
  }
  ip_e++;
  if (program[ip_e]<0 || program[ip_e]>31){
    printf("\nErrore registro\n");
    valuta_esegui(0);
  }else{
    sp_e--;
    registers[program[ip_e]] = stack[sp_e];  
  }
}

void add(){
  ip_e++;
  p1=program[ip_e];
  ip_e++;
  p2=program[ip_e];
  ip_e++;
  p3=program[ip_e];
  if (p1<0 || p1>31 || p2<0 || p2>31 || p3<0 || p3>31){
    printf("\nErrore registro\n");
    valuta_esegui(0);
  }else{
    cast_overflow=(long)registers[p1]+(long)registers[p2];
    if(cast_overflow>max || cast_overflow<min){
      printf("\nOverflow Aritmetico\n");
      valuta_esegui(0);
    }else{
      registers[p3]=registers[p1]+registers[p2];
    }
  }
}

void sub(){
  ip_e++;
  p1=program[ip_e];
  ip_e++;
  p2=program[ip_e];
  ip_e++;
  p3=program[ip_e];
  if (p1<0 || p1>31 || p2<0 || p2>31 || p3<0 || p3>31){
    printf("\nErrore registro\n");
    valuta_esegui(0);
  }else{
    cast_overflow=(long)registers[p1]-(long)registers[p2];
    if(cast_overflow>max || cast_overflow<min){
      printf("\nOverflow Aritmetico\n");
      valuta_esegui(0);
     }else{
        registers[p3]=registers[p1]-registers[p2];
      }
  }
}

void mul(){
  ip_e++;
  p1=program[ip_e];
  ip_e++;
  p2=program[ip_e];
  ip_e++;
  p3=program[ip_e];
  if (p1<0 || p1>31 || p2<0 || p2>31 || p3<0 || p3>31){
    printf("\nErrore registro\n");
    valuta_esegui(0);
  }else{
    cast_overflow=(long)registers[p1]*(long)registers[p2];
    if(cast_overflow>max || cast_overflow<min){
      printf("\nOverflow Aritmetico\n");
      valuta_esegui(0);
    }else{
      registers[p3]=registers[p1]*registers[p2];
    }
  }
}

void div(){
  ip_e++;
  p1=program[ip_e];
  ip_e++;
  p2=program[ip_e];
  ip_e++;
  p3=program[ip_e];
  if (p1<0 || p1>31 || p2<0 || p2>31 || p3<0 || p3>31){
    printf("\nErrore registro\n");
    valuta_esegui(0);
  }else if(registers[p2]==0){
    printf("\nDivisore è 0\n");
    valuta_esegui(0);
  }else{
    cast_overflow=(long)registers[p1]/(long)registers[p2];
    if(cast_overflow>max || cast_overflow<min){
      printf("\nOverflow Aritmetico\n");
      valuta_esegui(0);
    }else{
      registers[p3]=registers[p1]/registers[p2];
    }
  }
}

void valuta_esegui(int istr){
  switch(istr){
    case HALT:{
      run = 0;
      break;
    }
    case PUSH:{
      push();
      break;
    }
    case POP:{
      pop();
      break;
    }
    case ADD:{
      add();
      break;
    }
    case SUB:{
      sub()
      break;
    }
    case MUL:{
      mul();
      break;
    }
    case DIV:{
      div();
      break;
    }
    case DISPLAY:{
      ip_e++;
      if (program[ip_e]==-1){
        for(i=0; i<32; i++){
          printf("\nRegistro R%d = %d\n", i, registers[i]);
        }
        break;
      }
      if (program[ip_e]<0 || program[ip_e]>31){
        printf("\nErrore registro\n");
        valuta_esegui(0);
        break;
      }else{
        printf("\nRegistro R%d = %d\n", program[ip_e], registers[program[ip_e]]);
        break;
      }
    }
    case PRINT_STACK:{
      if (sp_e==0 || sp_e>16384){
        printf("\nErrore Stack Non Valido\n");
        valuta_esegui(0);
        break;
      }
      ip_e++;
      p1=sp_e;
      p2=program[ip_e];
      if (p2<=0){
        printf("\nValore N Non Valido\n");
        valuta_esegui(0);
        break;
      }
      while(p2!=0 && sp_e>0){
        sp_e--;
        printf("\nIndice: %d\nContenuto: %d\n", sp_e, stack[sp_e]);
        p2--;
      }
      sp_e=p1;
      break;
    }
    case MOV:{
      p1=program[ip_e+1];
      ip_e+=2;
      if (p1<0 || p1>31){
        printf("\nErrore registro\n");
        valuta_esegui(0);
        break;
      }else{
        registers[p1]=program[ip_e];
        break;
      }
    }
    case JMP:{
      p1=program[ip_e+1];
      if ((p1>=dim[0])||p1<0){
        printf("\nErrore indice\n");
        valuta_esegui(0);
        break;
      }else{
        ip_e=p1-1;
        break;
      }
    }
    case JZ:{
      p2=program[ip_e+2];
      if (p2<0 || p2>31){
        printf("\nErrore registro\n");
        valuta_esegui(0);
        break;
      }else{
        p3=registers[p2];
      }
      if(p3==0){
        p1=program[ip_e+1];
        if ((p1>=dim[0])||p1<0){
          printf("\nErrore indice\n");
          valuta_esegui(0);
          break;
        }else{
          ip_e=p1-1;
          break;
        }
      }else{
        ip_e+=2;
        break;
      }
    }
    case JPOS:{
      p2=program[ip_e+2];
      if (p2<0 || p2>31){
        printf("\nErrore registro\n");
        valuta_esegui(0);
        break;
      }else{
        p3=registers[p2];
      }
      if(p3>0){
        p1=program[ip_e+1];
        if ((p1>=dim[0])||p1<0){
          printf("\nErrore indice\n");
          valuta_esegui(0);
          break;
        }else{
          ip_e=p1-1;
          break;
        }
      }else{
        ip_e+=2;
        break;
      }
    }
    case JNEG:{
      p2=program[ip_e+2];
      if (p2<0 || p2>31){
        printf("\nErrore registro\n");
        valuta_esegui(0);
        break;
      }else{
        p3=registers[p2];
      }
      if(p3<0){
        p1=program[ip_e+1];
        if ((p1>=dim[0])||p1<0){
          printf("\nErrore indice\n");
          valuta_esegui(0);
          break;
        }else{
          ip_e=p1-1;
          break;
        }
      }else{
        ip_e+=2;
        break;
      }
    }
    case CALL:{
      if (sp_e>=16384){
        printf("\nErrore Stack Overflow\n");
        valuta_esegui(0);
        break;
      }
      stack[sp_e] = ip_e+2;
      sp_e++;
      p1=program[ip_e+1];
      if ((p1>=dim[0])||p1<0){
        printf("\nErrore indice\n");
        valuta_esegui(0);
        break;
      }else{
        ip_e=p1-1;
        break;
      }
    }
    case RET:{
      if (sp_e==0){
        printf("\nErrore Stack Underflow\n");
        valuta_esegui(0);
        break;
      }
      if (sp_e>16384){
        printf("\nErrore Stack Overflow\n");
        valuta_esegui(0);
        break;
      }
      sp_e--;
      p1=stack[sp_e];
      ip_e=p1-1;
      break;
    }
    case JCR:{
      p2=program[ip_e+2];
      p3=program[ip_e+3];
      if (p2<0 || p2>31 || p3<0 || p3>31){
        printf("\nErrore registro\n");
        valuta_esegui(0);
        break;
      }else{
        p2=registers[program[ip_e+2]];
        p3=registers[program[ip_e+3]];
      }
      if(p2==p3){
        p1=program[ip_e+1];
        if ((p1>=dim[0])||p1<0){
          printf("\nErrore indice\n");
          valuta_esegui(0);
          break;
        }else{
          ip_e=p1-1;
          break;
        }
      }else{
        ip_e+=3;
        break;
      }
    }
    case JCN:{
      p2=program[ip_e+2];
      p3=program[ip_e+3];
      if (p2<0 || p2>31){
        printf("\nErrore registro\n");
        valuta_esegui(0);
        break;
      }else{
        p2=registers[program[ip_e+2]];
      }
      if(p2==p3){
        p1=program[ip_e+1];
        if ((p1>=dim[0])||p1<0){
          printf("\nErrore indice\n");
          valuta_esegui(0);
          break;
        }else{
          ip_e=p1-1;
          break;
        }
      }else{
        ip_e+=3;
        break;
      }
    }
    default:{
      printf("\nIstruzione non riconosciuta: [%d] -> %d\n", ip_e, program[ip_e]);
      valuta_esegui(0);
      break;
    }
    break;
  }
}

/*
* Prende in input il file da leggere e, dopo averlo parsato
* (vedi Parser), finchè la flag run è attiva viene eseguito il
* comando presente nello switch che corrisponde ai valori salvati
* nell'array dinamico program.
*/
void esegui(char *argv){
  char *input;
  input=argv;
  leggi(input);
  while(run){
    ok_e=1;
    valuta_esegui(program[ip_e]);
    ip_e++;
  }
  if (ok_e==1){
    free(program);
  }
  free(run);
  free(dim);
  printf("\nFine Programma\n");
}
