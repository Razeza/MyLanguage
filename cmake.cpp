#include <cstdlib>
#include "stdio.h"

int main ()
{
    system ("g++ frontend.cpp -o frontend.exe");
    system ("g++ backend.cpp -o backend.exe");
    system ("g++ Assembler.cpp -o assembler.exe");
    system ("g++ CPU.cpp -o cpu.exe");

    system ("frontend.exe");
    system ("backend.exe");
    system ("assembler.exe");
    system ("cpu.exe");
}

