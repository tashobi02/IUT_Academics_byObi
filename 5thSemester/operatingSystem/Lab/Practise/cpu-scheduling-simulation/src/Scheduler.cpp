#include "Scheduler.hpp"
#include <algorithm>

// FCFS Implementation
void FCFSScheduler::addProcess(Process* process) {
    // Ideally check if process is state READY before adding
    process->setState(ProcessState::READY);
    readyQueue.push(process);
}

Process* FCFSScheduler::nextProcess() {
    if (readyQueue.empty()) {
        return nullptr;
    }
    
    while (!readyQueue.empty() && readyQueue.front()->getState() == ProcessState::TERMINATED) {
        readyQueue.pop();
    }
    
    if (readyQueue.empty()) {
        return nullptr;
    }

    Process* p = readyQueue.front();
    
    return p;
}

void SJFScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyList.push_back(process);
}

Process* SJFScheduler::nextProcess() {
    if (currentProcess &&
        currentProcess->getState() != ProcessState::TERMINATED) {
        return currentProcess;
    }

    Process* shortest = nullptr;

    for (auto* p : readyList) {
        if (p->getState() == ProcessState::TERMINATED)
            continue;

        if (!shortest ||
            (p->getTotalInstructions() - p->getProgramCounter()) <
            (shortest->getTotalInstructions() - shortest->getProgramCounter())) {
            shortest = p;
        }
    }

    currentProcess = shortest;
    return currentProcess;
}

void PreemptiveSJFScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyList.push_back(process);
}

Process* PreemptiveSJFScheduler::nextProcess() {
    Process* shortest = nullptr;

    for (auto* p : readyList) {
        if (p->getState() == ProcessState::TERMINATED)
            continue;

        if (!shortest ||
            (p->getTotalInstructions() - p->getProgramCounter()) <
            (shortest->getTotalInstructions() - shortest->getProgramCounter())) {
            shortest = p;
        }
    }

    return shortest;
}

void PriorityScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyList.push_back(process);
}

Process* PriorityScheduler::nextProcess() {
    if (currentProcess &&
        currentProcess->getState() != ProcessState::TERMINATED) {
        return currentProcess;
    }

    Process* highestPriority = nullptr;

    for (auto* p : readyList) {
        if (p->getState() == ProcessState::TERMINATED)
            continue;

        if (!highestPriority ||
            p->getPriority() < highestPriority->getPriority()) {
            highestPriority = p;
        }
    }

    currentProcess = highestPriority;
    return currentProcess;
}

void RRScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyQueue.push(process);
}

Process* RRScheduler::nextProcess() {
    if (currentProcess &&
        currentProcess->getState() != ProcessState::TERMINATED &&
        currentQuantumUsed < quanta) {
        currentQuantumUsed++;
        return currentProcess;
    }

    if (currentProcess &&
        currentProcess->getState() != ProcessState::TERMINATED) {
        readyQueue.push(currentProcess);
    }

    currentQuantumUsed = 0;

    while (!readyQueue.empty() &&
           readyQueue.front()->getState() == ProcessState::TERMINATED) {
        readyQueue.pop();
    }

    if (readyQueue.empty()) {
        currentProcess = nullptr;
        return nullptr;
    }

    currentProcess = readyQueue.front();
    readyQueue.pop();
    currentQuantumUsed = 1;

    return currentProcess;
}