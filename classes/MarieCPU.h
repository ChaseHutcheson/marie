//
// Created by Chase Hutcheson on 10/17/26.
//

#ifndef MARIE_MARIECPU_H
#define MARIE_MARIECPU_H
#include <cstdint>
#include <vector>
#include <array>

class MarieCPU {
    using Word = uint16_t;

    Word PC{0};     // program counter
    Word AC{0};     // accumulator
    Word MAR{0};    // memory address buffer
    Word MBR{0};    // memory buffer register
    Word IR{0};     // instruction register
    Word InREG{0};  // input register
    Word OutREG{0}; // output register

    std::array<Word, 4096> Memory{}; // 4K words of memory

public:
    void Step();
    void Run();
    void Load(const std::vector<Word>& program);
    bool Halted() const { return halted; }
private:
    void Fetch();
    void Execute();
    bool halted{false};
};


#endif //MARIE_MARIECPU_H
