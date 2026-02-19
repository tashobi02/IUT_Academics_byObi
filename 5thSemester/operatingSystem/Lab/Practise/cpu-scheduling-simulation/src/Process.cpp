#include "Process.hpp"
#include <stdexcept>

Process::Process(int id, int arrivalTime, int priority, const std::vector<Instruction>& instructions)
    : id(id), arrivalTime(arrivalTime), priority(priority), instructions(instructions), programCounter(0), state(ProcessState::CREATED) {}

int Process::getId() const {
    return id;
}

int Process::getArrivalTime() const {
    return arrivalTime;
}

int Process::getPriority() const {
    return priority;
}

ProcessState Process::getState() const {
    return state;
}

void Process::setState(ProcessState s) {
    state = s;
}

bool Process::hasNextInstruction() const {
    return programCounter < instructions.size();
}

const Instruction& Process::peekInstruction() const {
    if (!hasNextInstruction()) {
        throw std::out_of_range("No more instructions in process");
    }
    return instructions[programCounter];
}

void Process::advanceMock() {
    if (hasNextInstruction()) {
        programCounter++;
    }
}

size_t Process::getProgramCounter() const {
    return programCounter;
}

size_t Process::getTotalInstructions() const {
    return instructions.size();
}
