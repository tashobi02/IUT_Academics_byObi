#ifndef CPU_HPP
#define CPU_HPP

#include "Process.hpp"

class CPU {
public:
    CPU();
    
    // Executes one tick of the current process
    // Returns true if a process was running, false if idle
    bool execute();
    
    // Assigns a process to the CPU
    void setProcess(Process* process);
    
    Process* getCurrentProcess() const;
    bool isIdle() const;

private:
    Process* currentProcess;
};

#endif // CPU_HPP
