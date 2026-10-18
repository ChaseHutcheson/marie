#include <iostream>
#include "classes/MarieCPU.h"

int main() {
    MarieCPU CPU;

    CPU.Load({
        0x5000, // Take input
        0x200A, // Store at address 10
        0x5000, // Take new input
        0x400A, // Subtract new input from old input
        0x6000, // Print result
        0x7000, // Halt
    });

    bool stopped = false;

    while (!stopped) {
        char input;

        CPU.Step();
        std::cout << "(y/n) Step again? ";
        std::cin >> input;
    }

    return 0;
}