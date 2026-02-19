#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>
#include <string>

// Simulates a single instruction
struct Instruction {
    int duration; // Duration in ticks 
    // In a real CPU, this would be an opcode, operands, etc.
    // For this simplified version, duration is the main property.
    
    Instruction(int d = 1) : duration(d) {}
};

enum class ProcessState {
    CREATED,
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED
};

class Process {
public:
    Process(int id, int arrivalTime, int priority, const std::vector<Instruction>& instructions);

    int getId() const;
    int getArrivalTime() const;
    int getPriority() const;
    
    ProcessState getState() const;
    void setState(ProcessState state);

    // Returns true if there are more instructions to execute
    bool hasNextInstruction() const;

    // Returns the current instruction without advancing
    const Instruction& peekInstruction() const;

    // Advances the program counter (simulates instruction completion)
    void advanceMock();

    // Returns the Program Counter
    size_t getProgramCounter() const;

    // Returns the total number of instructions
    size_t getTotalInstructions() const;

private:
    int id;
    int arrivalTime;
    int priority;
    std::vector<Instruction> instructions;
    size_t programCounter;
    ProcessState state;
};

#endif // PROCESS_HPP
