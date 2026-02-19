#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Process.hpp"
#include "Scheduler.hpp"
#include "Emulator.hpp"

struct ProcessInput {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
};

void runSimulation(Scheduler* sched, const std::string& name, const std::vector<ProcessInput>& inputs) {
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Scheduler: " << name << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    Emulator emulator(sched);

    for (const auto& input : inputs) {
        std::vector<Instruction> instructions;
        for (int j = 0; j < input.burstTime; ++j) {
            instructions.emplace_back(1); // Standard duration 1 tick
        }
        
        Process p(input.id, input.arrivalTime, input.priority, instructions);
        emulator.loadProcess(p);
    }

    emulator.run();
    emulator.printGanttChart();
    std::cout << std::endl;
}

int main() {
    std::cout << "Vibe CPU Emulator" << std::endl;

    int numProcesses;
    std::cout << "Enter number of processes: ";
    if (!(std::cin >> numProcesses)) return 1;

    std::vector<ProcessInput> inputs;
    for (int i = 0; i < numProcesses; ++i) {
        int arrivalTime, burstTime, priority;
        std::cout << "Process " << (i + 1) << " Arrival Time | Burst Time | Priority: ";
        std::cin >> arrivalTime >> burstTime >> priority;
        inputs.push_back({i + 1, arrivalTime, burstTime, priority});
    }

    // FCFS
    FCFSScheduler fcfs;
    runSimulation(&fcfs, "FCFS", inputs);

    // SJF
    SJFScheduler sjf;
    runSimulation(&sjf, "SJF", inputs);

    // Preemptive SJF
    PreemptiveSJFScheduler psjf;
    runSimulation(&psjf, "Preemptive SJF", inputs);

    // Priority
    PriorityScheduler prioritySched;
    runSimulation(&prioritySched, "Priority", inputs);

    // RR
    RRScheduler rr;
    runSimulation(&rr, "Round Robin", inputs);

    return 0;
}
