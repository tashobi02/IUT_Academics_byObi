#include "CPU.hpp"
#include <iostream>

CPU::CPU() : currentProcess(nullptr) {}

bool CPU::execute() {
    if (currentProcess == nullptr) {
        return false;
    }

    if (currentProcess->getState() != ProcessState::TERMINATED) {
        // In a real CPU, we would decrement the instruction duration or similar
        // Here, we just assume 1 instruction = 1 tick as requested
        // "I just want a cpu which processes 1 instruction in 1 tick"
        
        if (currentProcess->hasNextInstruction()) {
            currentProcess->advanceMock();
            
            // Check if process is finished after this instruction
            if (!currentProcess->hasNextInstruction()) {
                currentProcess->setState(ProcessState::TERMINATED);
            }
            return true;
        } else {
             currentProcess->setState(ProcessState::TERMINATED);
        }
    }
    
    return false;
}

void CPU::setProcess(Process* process) {
    currentProcess = process;
    if (currentProcess && currentProcess->getState() == ProcessState::READY) {
        currentProcess->setState(ProcessState::RUNNING);
    }
}

Process* CPU::getCurrentProcess() const {
    return currentProcess;
}

bool CPU::isIdle() const {
    return currentProcess == nullptr || currentProcess->getState() == ProcessState::TERMINATED;
}
