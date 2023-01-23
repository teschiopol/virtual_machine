[![CodeFactor](https://www.codefactor.io/repository/github/teschiopol/virtual_machine/badge)](https://www.codefactor.io/repository/github/teschiopol/virtual_machine)

# 💾 Virtual Machine

A simple virtual machine in c

Use Makefile to simple use the program

## 📂 Files

**main.c**
Avviene il controllo del numero di parametri passati da linea di comando, insieme alla corretta sintassi dei comandi “esegui” e “stampa”.

**function.h**
Header contenente le firme delle funzioni presenti nei file “esegui.c” e “stampa.c”.

**parser.c**
Tutto l’aspetto del parsing del file in input; eliminando tutti gli errori, le righe vuote e i commenti. Ho utilizzato diverse flag per determinare quando effettuare la free della memoria dinamica allocata, eliminando così eventuali errori.

**parser.h**
Header contenente la firma di “parser.c” e tutte le variabili globali usate nelle varie funzioni e file. In caso di modifica al codice memonico o all’istruzione, basta modificare questo file soltanto.

**esegui.c**
Tutto lo sviluppo del comando “esegui” con uno switch come corpo portante per gestire al meglio la chiamata delle varie istruzioni.

**stampa.c**
Tutto lo sviluppo del comando “stampa” con uno switch come corpo portante per gestire al meglio la stampa delle varie istruzioni.

## 📝 Test Case

- test: Fattoriale 5
- test1: Cambia numero negativo con positivo e poi stampa tutti i registri
- test2: Errore divisore 0
- test3: Errore file, righe non corrette
- test4: Comando non valido
- test5: Registro non valido
- test6: Stack underflow
- test7: Stack overflow
- test8: Overflow Aritmetico
- test9: Errore numero negativo quando serve positivo
- test10: Cubi primi 10 numeri interi
- test11: Somma primi 6 numeri interi
- test12: Somma dei quadrati dei primi 4 numeri interi
- test13: Jump compare register
- test14: Successione di Fibonacci
