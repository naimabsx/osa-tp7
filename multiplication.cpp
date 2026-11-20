#include <Arduino.h>

/* -------------------------------------------------------------------
 * B3. Multiplication (MUL et MLA interdites)
 * Responsable : ...
 * R0, R1 (entrée) : opérandes ; R0 (sortie) : R0 × R1
 * ------------------------------------------------------------------- */
extern "C" __attribute__((naked)) int multiplication(int a, int b) {
  asm volatile(
  
    "MOVS R2, #0         \n"
    "MOVS R3, #0         \n"

    "CMP R0, #0          \n"
    "BGE signe2          \n"
    "RSBS R0, R0, #0     \n"
    "MOVS R3, #1         \n"

    "signe2:             \n"
    "CMP R1, #0          \n"
    "BGE boucle          \n"
    "RSBS R1, R1, #0     \n"
    "EOR R3, R3, #1      \n"

    "boucle:             \n"
    "CMP R1, #0          \n"
    "BEQ fin_boucle      \n"
    "TST R1, #1          \n"
    "BEQ decalage        \n"
    "ADD R2, R2, R0      \n"

    "decalage:           \n"
    "LSL R0, R0, #1      \n"
    "LSR R1, R1, #1      \n"
    "B boucle           \n"

    "fin_boucle:         \n"
    "CMP R3, #0          \n"
    "BEQ fin             \n"
    "RSBS R2, R2, #0     \n"

    "fin:                \n"
    "MOV R0, R2          \n"
    "BX    LR              \n"   // à compléter
    ".ltorg                \n"
  );
}
