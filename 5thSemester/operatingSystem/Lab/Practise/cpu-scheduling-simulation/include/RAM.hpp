#ifndef RAM_HPP
#define RAM_HPP

#include "Process.hpp"
#include <list>
#include <map>

// Represents the system memory, holding all processes
class RAM {
public:
    void addProcess(const Process& process);
    Process* getProcess(int id);
    std::vector<Process*> getAllProcesses();

private:
    std::list<Process> processes; // Using list for pointer stability
};

#endif // RAM_HPP
