#include <stdio.h>

// Declaração e definição das variáveis globais
int a = 2, b = 3, c = 5, x = 4, y;

int main() {
    asm(
        "movl %1, %%eax;"    // eax = a
        "imull %2, %%eax;"   // eax = a * x
        "imull %2, %%eax;"   // eax = a * x^2

        "movl %3, %%ebx;"    // ebx = b
        "imull %2, %%ebx;"   // ebx = b * x

        "addl %%ebx, %%eax;" // eax = (a * x^2) + (b * x)
        "addl %4, %%eax;"    // eax = (a * x^2) + (b * x) + c

        "movl %%eax, %0;"    // y = resultado final
        : "=r" (y)           // Saída
        : "m" (a), "m" (x), "m" (b), "m" (c) // Entradas
        : "%eax", "%ebx"     // Registradores modificados
    );

    printf("Resultado de y = %d\n", y);
    return 0;
}