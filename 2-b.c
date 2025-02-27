#include <stdio.h>

short int a = -10;
short int b = -4;
int c;

int main() {
    asm(

        "movw %1, %%ax;"       // Carrega 'a' em AX (16 bits)
        "movw %2, %%dx;"       // Carrega 'b' em DX (16 bits)

        "shll $1, %%ax;"       // Desloca 'a' para a esquerda até o primeiro bit 1

        "shll $1, %%dx;"       // Desloca 'b' para a esquerda até o primeiro bit 1
        "orw $0xFFFF, %%dx;"   // Preenche a parte à esquerda de 'b' com 1s

        "shll $16, %%eax;"     // Desloca 'a' para os 16 bits superiores de EAX
        "orw %%dx, %%ax;"      // Combina 'b' nos 16 bits inferiores de EAX
        "movl %%eax, %0;"      // Armazena o resultado final em 'c'

        : "=m" (c)             // Saída (variável 'c')
        : "m" (a), "m" (b)     // Entradas (variáveis 'a' e 'b')
        : "%ax", "%dx"         // Registradores modificados
    );

    printf("Resultado final: %d (0x%X)\n", c, c);
    return 0;
}