#include <iostream>
#include <vector>

class ProcessorCesar {
private:
    std::vector<int> memory; // Memória com 256 posições
    int acc;                 // Acumulador
    int pc;                  // Contador de Programa (Program Counter)
    bool running;            // Indicador de execução

public:
    // Inicializa o processador com memória zerada
    ProcessorCesar() : memory(256, 0), acc(0), pc(0), running(true) {}

    // Carrega um programa na memória
    void load_program(const std::vector<int>& program) {
        for (size_t i = 0; i < program.size() && i < memory.size(); ++i) {
            memory[i] = program[i];
        }
    }

    // Executa o programa carregado na memória
    void run() {
        running = true;
        while (running) {
            if (pc < 0 || pc >= static_cast<int>(memory.size())) {
                std::cerr << "Erro: PC fora dos limites da memória (PC = " << pc << ").\n";
                running = false;
                break;
            }

            int instruction = fetch();
            execute(instruction);
        }
    }

    // Busca a próxima instrução na memória
    int fetch() {
        int instruction = memory[pc];
        pc = (pc + 1) % 256; // Incrementa PC com wrap-around (256 posições)
        return instruction;
    }

    // Decodifica e executa a instrução
    void execute(int instruction) {
        int opcode = (instruction >> 4) & 0xF; // 4 bits mais significativos
        int operand = instruction & 0xF;       // 4 bits menos significativos

        switch (opcode) {
        case 0x0: // NOP: Não faz nada
            break;
        case 0x1: // LDA: Carrega valor da memória no acumulador
            acc = memory[operand];
            break;
        case 0x2: // STA: Armazena o acumulador na memória
            memory[operand] = acc;
            break;
        case 0x3: // ADD: Soma valor da memória ao acumulador
            acc += memory[operand];
            break;
        case 0x4: // SUB: Subtrai valor da memória do acumulador
            acc -= memory[operand];
            break;
        case 0x5: // JMP: Salta para um endereço da memória
            pc = operand;
            break;
        case 0x6: // JZ: Salta se o acumulador for zero
            if (acc == 0) pc = operand;
            break;
        case 0x7: // JN: Salta se o acumulador for negativo
            if (acc < 0) pc = operand;
            break;
        case 0x8: // HLT: Para a execução do programa
            running = false;
            break;
        default: // Instrução desconhecida
            std::cerr << "Instrução desconhecida: 0x" << std::hex << instruction << std::endl;
            running = false;
        }
    }

    // Lê o valor de uma posição da memória
    int get_memory(int address) const {
        if (address >= 0 && address < static_cast<int>(memory.size())) {
            return memory[address];
        } else {
            std::cerr << "Erro: Endereço de memória inválido (" << address << ").\n";
            return 0;
        }
    }
};

int main() {
    // Exemplo de programa: Soma dois números na memória e armazena o resultado
    // Memória inicial:
    //   0x00: LDA 0x04 (Carrega o valor de 0x04 no acumulador)
    //   0x01: ADD 0x05 (Soma o valor de 0x05 ao acumulador)
    //   0x02: STA 0x06 (Armazena o acumulador em 0x06)
    //   0x03: HLT      (Termina a execução)
    // Dados na memória:
    //   0x04: 5        (Número 1)
    //   0x05: 7        (Número 2)
    std::vector<int> program = {
        0x14, // LDA 0x04
        0x35, // ADD 0x05
        0x26, // STA 0x06
        0x80, // HLT
        5,    // Dados: 0x04
        7     // Dados: 0x05
    };

    ProcessorCesar processor;
    processor.load_program(program);
    processor.run();

    // Exibe o resultado da soma (armazenado em 0x06)
    std::cout << "Resultado da soma: " << processor.get_memory(0x06) << std::endl;

    return 0;
}
