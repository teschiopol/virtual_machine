/* Concolato Paolo 876700 */

#include <stdio.h>
#include <string.h>
#include "function.h"

/*
* Uso della string compare per valutare i comandi passati da linea di comando.
*/

int main(int argc, char  *argv[]) {
  if (argc!=3){
    printf("\nNumero di argomenti errato.\n");
  }else{
    if (!strcmp(argv[1],"esegui")){
      esegui(argv[2]);
    }else if (!strcmp(argv[1],"stampa")){
      stampa(argv[2]);
    }else{
      printf("\nComando non valido\n");
    }
  }
  return 0;
}
