#include "Emulator.hpp"
#include <iostream>
#include <iomanip>

Emulator::Emulator(Scheduler* sched) : scheduler(sched), curTick(0) {}

void Emulator::loadProcess(const Process& process) {
    ram.addProcess(process);
}

void Emulator::run() {
    std::cout << "Starting Emulation..." << std::endl;
    
    bool running = true;
    while (running) {
        // Check for new arrivals
        for (auto* p : ram.getAllProcesses()) {
            if (p->getState() == ProcessState::CREATED && p->getArrivalTime() <= curTick) {
                scheduler->addProcess(p);
                // Scheduler usually sets it to READY
            }
        }

        // Scheduler decides
        Process* next = scheduler->nextProcess();
        
        cpu.setProcess(next);
        
        // Execute CPU
        bool busy = cpu.execute();
        
        // Record history
        if (busy && cpu.getCurrentProcess()) {
            history.push_back({curTick, cpu.getCurrentProcess()->getId()});
        } else {
            history.push_back({curTick, -1}); // -1 for IDLE
        }
        
        curTick++;

        // Stop condition:
        // If CPU is idle AND scheduler has no more processes
        bool allTerminated = true;
        for (auto* p : ram.getAllProcesses()) {
            if (p->getState() != ProcessState::TERMINATED) {
                allTerminated = false;
                break;
            }
        }
        if (allTerminated) {
            running = false;
        }
    }
    std::cout << "Emulation Finished at tick " << curTick << "." << std::endl;
}

void Emulator::printGanttChart() const {
    std::cout << "\n=== Gantt Chart ===\n";
    if (history.empty()) return;

    // 1. Compress history into segments
    struct Segment {
        int processId;
        int startTime;
        int endTime;
    };
    std::vector<Segment> segments;

    if (!history.empty()) {
        int currentId = history[0].second;
        int startTime = history[0].first;
        
        for (size_t i = 1; i < history.size(); ++i) {
            if (history[i].second != currentId) {
                segments.push_back({currentId, startTime, history[i].first});
                currentId = history[i].second;
                startTime = history[i].first;
            }
        }
        segments.push_back({currentId, startTime, history.back().first + 1});
    }

    // Determine width for each segment
    int totalTime = segments.back().endTime;
    bool proportional = (totalTime <= 100);

    // Calculate segment widths
    std::vector<int> segmentWidths;
    for (const auto& seg : segments) {
        int duration = seg.endTime - seg.startTime;
        int width = proportional ? duration * 2 : 6;
        if (width < 6) width = 6;
        
        // Make sure width is enough for the label "P12"
        std::string label = (seg.processId == -1) ? "IDLE" : "P" + std::to_string(seg.processId);
        if (width < label.length() + 2) width = label.length() + 2;

        segmentWidths.push_back(width);
    }

    // Print Top Border
    std::cout << "+";
    for (int w : segmentWidths) {
        for (int k = 0; k < w; ++k) std::cout << "-";
        std::cout << "+";
    }
    std::cout << "\n";

    // Print Content
    std::cout << "|";
    for (size_t i = 0; i < segments.size(); ++i) {
        const auto& seg = segments[i];
        int width = segmentWidths[i];
        std::string label = (seg.processId == -1) ? "IDLE" : "P" + std::to_string(seg.processId);
        
        int padding = width - label.length();
        int leftPad = padding / 2;
        int rightPad = padding - leftPad;
        
        for(int k=0; k<leftPad; ++k) std::cout << " ";
        std::cout << label;
        for(int k=0; k<rightPad; ++k) std::cout << " ";
        std::cout << "|";
    }
    std::cout << "\n";

    // Print Bottom Border
    std::cout << "+";
    for (int w : segmentWidths) {
        for (int k = 0; k < w; ++k) std::cout << "-";
        std::cout << "+";
    }
    std::cout << "\n";

    // Print Numbers
    std::cout << segments[0].startTime;
    int currentPos = std::to_string(segments[0].startTime).length();

    for (size_t i = 0; i < segments.size(); ++i) {
        int width = segmentWidths[i];
        // The end of this segment is at a distance of (width + 1) ticks from the start of this segment visual
        // The '+' is 1 char. 
        // We want to align the next number under the '+' at the end of this block.
        
        std::string nextNum = std::to_string(segments[i].endTime);
        
        // Total chars to print to reach the right alignment:
        // We printed the previous number. We are at `currentPos`.
        // We want to be at a position relative to the start of the line.
        // Let's track expected visual position.
    }
    // Actually, simple padding loop is easier.
    // Re-print the loop for numbers with explicit spacing
    std::cout << "\r"; // Clear line if needed, or just new line
    
    // Easier way: Build the line string buffer
    std::string timeline = std::to_string(segments[0].startTime);
    for (size_t i = 0; i < segments.size(); ++i) {
        int width = segmentWidths[i];
        std::string nextStr = std::to_string(segments[i].endTime);
        
        // We need to add spaces until the length of timeline is equal to the position of the corresponding '+' 
        // Logic:
        // Start of bar i is at: i (implicit)
        // End of bar i (and start of i+1) is at accumulated width + (i+1)
        
        int targetLen = 0;
        for(size_t j=0; j<=i; ++j) targetLen += segmentWidths[j] + 1;
        // targetLen is the position of the '+' closing this segment. 
        // We want to center the number? No, usually left aligned to the tick mark.
        // The tick mark is the '+' character.
        // Position of '+' #1 (start) is 0.
        // Position of '+' #2 (end of seg 0) is width[0] + 1.
        
        // timeline currently has "0". Len = 1.
        // We want next number at width[0] + 1.
        // So we append spaces until len is width[0] + 1 - nextStr.length()/2 ?
        // Standard is left-aligned to the vertical bar.
        
        int targetPos = 0;
        for(size_t k=0; k<=i; ++k) targetPos += segmentWidths[k] + 1;
        
        int spacesNeeded = targetPos - timeline.length();
        // Since we want the number to *start* somewhat aligned, or centered? 
        // Usually aligned left if it fits, or centered.
        // If we strictly align left to the '+', we might overlap if segments are tiny.
        // But we ensured min width 6. 
        // "0" (len 1). target (say 7). spaces = 6. 
        // timeline becomes "0      ". Then append "5". "0      5".
        
        // Adjust for length of number to center it?
        // Let's just align left to the '+'.
        int correction = nextStr.length() / 2; // Rough center
        // Remove correction to center under '+'?
        // targetPos is the index of '+'.
        // We want center of number to be at targetPos?
        // Or start of number at targetPos?
        // If start at targetPos:
        if (spacesNeeded > 0) {
            timeline += std::string(spacesNeeded, ' ');
        }
        timeline += nextStr;
    }
    std::cout << timeline << "\n";

    std::cout << "===================\n";
}
