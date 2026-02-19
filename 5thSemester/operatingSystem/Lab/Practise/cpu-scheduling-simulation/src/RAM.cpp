#include "RAM.hpp"

void RAM::addProcess(const Process& process) {
    processes.push_back(process);
}

Process* RAM::getProcess(int id) {
    for (auto& p : processes) {
        if (p.getId() == id) {
            return &p;
        }
    }
    return nullptr;
}

std::vector<Process*> RAM::getAllProcesses() {
    std::vector<Process*> ptrs;
    for (auto& p : processes) {
        ptrs.push_back(&p);
    }
    return ptrs;
}
