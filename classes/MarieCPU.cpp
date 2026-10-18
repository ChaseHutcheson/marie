//
// Created by Chase Hutcheson on 10/17/26.
//

#include "MarieCPU.h"
#include <iostream>
#include <vector>

void MarieCPU::Step() {
    Fetch();
    Execute();
}

void MarieCPU::Run() {
    while (!halted) {
        Step();
    }
}

void MarieCPU::Load(const std::vector<Word>& program) {
    std::ranges::copy(program, Memory.begin());
    PC = 0;
    halted = false;
}

void MarieCPU::Fetch() {
    MAR = PC;
    IR = Memory[MAR];
    PC = ++PC;
    MAR = IR & 0x0FFF;
}

void MarieCPU::Execute() {
    switch (IR >> 12) {
        case 0: {
            std::cout << "Reached NULL word, ending...\n";
            halted = true;
            break;
        }

        // LOAD X
        case 1: {
            std::cout << "Executing Load instruction\n";
            MBR = Memory[MAR];
            AC = MBR;
            break;
        }

        // STORE X
        case 2: {
            std::cout << "Executing Store instruction\n";
            MBR = AC;
            Memory[MAR] = MBR;
            break;
        }

        case 3: {
            std::cout << "Executing Add instruction\n";
            MBR = Memory[MAR];
            AC = AC + MBR;
            break;
        }

        // SUBT X
        case 4: {
            std::cout << "Executing Subt instruction\n";
            MBR = Memory[MAR];
            AC = AC - MBR;
            break;
        }

        // INPUT
        case 5: {
            std::cout << "INPUT: ";
            std::cin >> InREG;
            AC = InREG;
            break;
        }

        // OUTPUT
        case 6: {
            OutREG = AC;
            std::cout << "OUTPUT: " << OutREG << "\n";
            break;
        }

        // HALT
        case 7: {
            std::cout << "HALT\n";
            halted = true;
            break;
        }

        // SKIPCOND
        case 8: {
            if (IR & 0x0C00 == 0x0000) {
                if (AC < 0)
                    PC = ++PC;
            } else if (IR & 0x0C00 == 0x0400) {
                if (AC == 0)
                    PC = ++PC;
            } else if (IR & 0x0C00 == 0x0800) {
                if (AC > 0)
                    PC = ++PC;
            }
            break;
        }

        // JUMP X
        case 9: {
            PC = IR & 0x0FFF;
            break;
        }
    }
}
