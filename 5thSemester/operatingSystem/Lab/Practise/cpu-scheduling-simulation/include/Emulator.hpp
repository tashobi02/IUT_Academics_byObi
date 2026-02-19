#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "CPU.hpp"
#include "RAM.hpp"
#include "Scheduler.hpp"
#include <vector>
#include <utility>
#include <string>

class Emulator {
public:
    Emulator(Scheduler* scheduler);

    void loadProcess(const Process& process);
    
    // Runs the emulation until completion
    void run();

    // Prints the Gantt Chart
    void printGanttChart() const;

private:
    CPU cpu;
    RAM ram;
    Scheduler* scheduler;
    int curTick;

    // To store history: [StartTime, ProcessID]
    // Or [Tick, ProcessID]
    std::vector<std::pair<int, int>> history; // Tick -> Process ID. -1 for Idle.
};

#endif // EMULATOR_HPP
