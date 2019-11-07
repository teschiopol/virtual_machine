/* 876700 Paolo Concolato */

void leggi(char *input);

/* Codice memonico e istruzioni */
typedef enum{
  HALT,
  DISPLAY,
  PRINT_STACK,
  PUSH = 10,
  POP,
  MOV,
  CALL = 20,
  RET,
  JMP,
  JCR = 71,
  JCN = 72,
  JZ,
  JPOS,
  JNEG,
  ADD = 80,
  SUB,
  MUL,
  DIV
} Instruction;

/* Registri */
typedef enum{
  R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15,R16,R17,R18,R19,R20,R21,R22,R23,R24,R25,R26,R27,R28,R29,R30,R31, /* tutti i registri */
  REG_SIZE
}Registers;

int registers[REG_SIZE];

int *run; /* Flag per terminare il programma */
int *program; /* Array con codice macchina */
int *dim; /* Righe "valide" del file */

/* Parametri */
int p1;
int p2;
int p3;

#define STACK_SIZE 16384 /* [(64*1024)byte]/4 byte per un int */
int stack[STACK_SIZE]; /* Stack */
