// scheduler_functions_only.cpp
// One .cpp file. No custom struct/class types (pure C-style arrays + functions).
// Demonstrates: FCFS, SJF (non-preemptive), Preemptive SJF, Priority (non-preemptive), Round Robin.
// Uses a simple "one instruction per tick" execution model.
// Page of output will show which PID gets CPU each tick.

#include <iostream>
#include <iomanip>
#include <cstddef>
using namespace std;

static const int MAX_PROCS = 32;

// -----------------------------
// Process "model" (no struct/class)
// -----------------------------
enum ProcessState {
    NEW = 0,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

static int g_procCount = 0;
static ProcessState g_state[MAX_PROCS];
static int g_totalInstr[MAX_PROCS];
static int g_pc[MAX_PROCS];
static int g_prio[MAX_PROCS];

static void resetProcesses() {
    g_procCount = 0;
    for (int i = 0; i < MAX_PROCS; ++i) {
        g_state[i] = NEW;
        g_totalInstr[i] = 0;
        g_pc[i] = 0;
        g_prio[i] = 0;
    }
}

static int createProcess(int totalInstructions, int priority) {
    if (g_procCount >= MAX_PROCS) return -1;
    const int pid = g_procCount++;
    g_state[pid] = READY;
    g_totalInstr[pid] = totalInstructions;
    g_pc[pid] = 0;
    g_prio[pid] = priority;
    return pid;
}

static int remaining(int pid) {
    int r = g_totalInstr[pid] - g_pc[pid];
    return (r > 0) ? r : 0;
}

static void runOneInstruction(int pid) {
    if (pid < 0) return;
    if (g_state[pid] == TERMINATED) return;

    g_state[pid] = RUNNING;
    g_pc[pid]++;

    if (g_pc[pid] >= g_totalInstr[pid]) {
        g_state[pid] = TERMINATED;
    } else {
        // After this "tick", CPU can reschedule, so we mark it READY again.
        g_state[pid] = READY;
    }
}

static const char* stateName(ProcessState s) {
    switch (s) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "?";
    }
}

// -----------------------------
// Tiny circular queue utilities (no struct/class)
// -----------------------------
static void q_init(int q[], int& head, int& tail, int& count) {
    (void)q;
    head = tail = count = 0;
}
static bool q_empty(int count) { return count == 0; }

static bool q_push(int q[], int& head, int& tail, int& count, int pid) {
    (void)head;
    if (count >= MAX_PROCS) return false;
    q[tail] = pid;
    tail = (tail + 1) % MAX_PROCS;
    count++;
    return true;
}
static int q_front(const int q[], int head, int count) {
    if (count <= 0) return -1;
    return q[head];
}
static int q_pop(int q[], int& head, int& tail, int& count) {
    (void)tail;
    if (count <= 0) return -1;
    int pid = q[head];
    head = (head + 1) % MAX_PROCS;
    count--;
    return pid;
}

// ============================================================
// FCFS (non-preemptive style: keep the head until it terminates)
// ============================================================
static int fcfsQ[MAX_PROCS];
static int fcfsHead, fcfsTail, fcfsCount;

static void FCFS_reset() {
    q_init(fcfsQ, fcfsHead, fcfsTail, fcfsCount);
}
static void FCFS_addProcess(int pid) {
    if (pid < 0) return;
    g_state[pid] = READY;
    q_push(fcfsQ, fcfsHead, fcfsTail, fcfsCount, pid);
}
static int FCFS_nextProcess() {
    // Remove terminated from the front
    while (!q_empty(fcfsCount) && g_state[q_front(fcfsQ, fcfsHead, fcfsCount)] == TERMINATED) {
        q_pop(fcfsQ, fcfsHead, fcfsTail, fcfsCount);
    }
    if (q_empty(fcfsCount)) return -1;
    return q_front(fcfsQ, fcfsHead, fcfsCount); // do NOT pop (matches your original FCFS)
}

// ==================================
// SJF (non-preemptive) - keep current
// ==================================
static int sjfList[MAX_PROCS];
static int sjfN;
static int sjfCurrent;

static void SJF_reset() {
    sjfN = 0;
    sjfCurrent = -1;
}
static void SJF_addProcess(int pid) {
    if (pid < 0) return;
    g_state[pid] = READY;
    if (sjfN < MAX_PROCS) sjfList[sjfN++] = pid;
}
static int SJF_nextProcess() {
    if (sjfCurrent >= 0 && g_state[sjfCurrent] != TERMINATED) {
        return sjfCurrent; // non-preemptive
    }

    int best = -1;
    for (int i = 0; i < sjfN; ++i) {
        int pid = sjfList[i];
        if (pid < 0 || g_state[pid] == TERMINATED) continue;
        if (best < 0 || remaining(pid) < remaining(best)) best = pid;
    }

    sjfCurrent = best;
    return sjfCurrent;
}

// =======================================
// Preemptive SJF - pick shortest remaining
// =======================================
static int psjfList[MAX_PROCS];
static int psjfN;

static void PSJF_reset() {
    psjfN = 0;
}
static void PSJF_addProcess(int pid) {
    if (pid < 0) return;
    g_state[pid] = READY;
    if (psjfN < MAX_PROCS) psjfList[psjfN++] = pid;
}
static int PSJF_nextProcess() {
    int best = -1;
    for (int i = 0; i < psjfN; ++i) {
        int pid = psjfList[i];
        if (pid < 0 || g_state[pid] == TERMINATED) continue;
        if (best < 0 || remaining(pid) < remaining(best)) best = pid;
    }
    return best;
}

// ==================================
// Priority (non-preemptive) - keep current
// lower number = higher priority
// ==================================
static int prioList[MAX_PROCS];
static int prioN;
static int prioCurrent;

static void Priority_reset() {
    prioN = 0;
    prioCurrent = -1;
}
static void Priority_addProcess(int pid) {
    if (pid < 0) return;
    g_state[pid] = READY;
    if (prioN < MAX_PROCS) prioList[prioN++] = pid;
}
static int Priority_nextProcess() {
    if (prioCurrent >= 0 && g_state[prioCurrent] != TERMINATED) {
        return prioCurrent; // non-preemptive
    }

    int best = -1;
    for (int i = 0; i < prioN; ++i) {
        int pid = prioList[i];
        if (pid < 0 || g_state[pid] == TERMINATED) continue;
        if (best < 0 || g_prio[pid] < g_prio[best]) best = pid;
    }

    prioCurrent = best;
    return prioCurrent;
}

// =======================
// Round Robin (time quantum)
// =======================
static int rrQ[MAX_PROCS];
static int rrHead, rrTail, rrCount;
static int rrCurrent;
static std::size_t rrQuanta;
static std::size_t rrUsed;

static void RR_reset(std::size_t quantum) {
    q_init(rrQ, rrHead, rrTail, rrCount);
    rrCurrent = -1;
    rrQuanta = (quantum == 0) ? 1 : quantum;
    rrUsed = 0;
}
static void RR_addProcess(int pid) {
    if (pid < 0) return;
    g_state[pid] = READY;
    q_push(rrQ, rrHead, rrTail, rrCount, pid);
}
static int RR_nextProcess() {
    // Continue current if quantum remains
    if (rrCurrent >= 0 &&
        g_state[rrCurrent] != TERMINATED &&
        rrUsed < rrQuanta) {
        rrUsed++;
        return rrCurrent;
    }

    // Quantum exhausted: requeue current if still alive
    if (rrCurrent >= 0 && g_state[rrCurrent] != TERMINATED) {
        q_push(rrQ, rrHead, rrTail, rrCount, rrCurrent);
    }

    rrUsed = 0;

    // Drop terminated at front
    while (!q_empty(rrCount) && g_state[q_front(rrQ, rrHead, rrCount)] == TERMINATED) {
        q_pop(rrQ, rrHead, rrTail, rrCount);
    }

    if (q_empty(rrCount)) {
        rrCurrent = -1;
        return -1;
    }

    rrCurrent = q_pop(rrQ, rrHead, rrTail, rrCount);
    rrUsed = 1;
    return rrCurrent;
}

// -----------------------------
// Demo helpers
// -----------------------------
static void printProcSummary() {
    cout << "Process summary:\n";
    for (int pid = 0; pid < g_procCount; ++pid) {
        cout << "  P" << pid << ": total=" << g_totalInstr[pid]
                  << " pc=" << g_pc[pid] << " rem=" << remaining(pid)
                  << " prio=" << g_prio[pid] << " state=" << stateName(g_state[pid]) << "\n";
    }
}

static bool allTerminated() {
    for (int pid = 0; pid < g_procCount; ++pid) {
        if (g_state[pid] != TERMINATED) return false;
    }
    return true;
}

// -----------------------------
// Demonstrations
// -----------------------------
static void demoFCFS() {
    cout << "\n================ FCFS Demo ================\n";
    resetProcesses();
    FCFS_reset();

    int p0 = createProcess(6, 2);
    int p1 = createProcess(3, 1);
    int p2 = createProcess(4, 3);

    FCFS_addProcess(p0);
    FCFS_addProcess(p1);
    FCFS_addProcess(p2);

    for (int t = 0; t < 30 && !allTerminated(); ++t) {
        int pid = FCFS_nextProcess();
        if (pid < 0) break;
        cout << "t=" << std::setw(2) << t << "  -> run P" << pid << " (rem=" << remaining(pid) << ")\n";
        runOneInstruction(pid);
    }

    printProcSummary();
}

static void demoSJF_nonpreemptive() {
    cout << "\n========== SJF (Non-preemptive) Demo ==========\n";
    resetProcesses();
    SJF_reset();

    int p0 = createProcess(10, 2);
    int p1 = createProcess(4,  1);
    int p2 = createProcess(6,  3);

    SJF_addProcess(p0);
    SJF_addProcess(p1);
    SJF_addProcess(p2);

    for (int t = 0; t < 40 && !allTerminated(); ++t) {
        int pid = SJF_nextProcess();
        if (pid < 0) break;
        cout << "t=" << std::setw(2) << t << "  -> run P" << pid << " (rem=" << remaining(pid) << ")\n";
        runOneInstruction(pid);
    }

    printProcSummary();
}

static void demoSJF_preemptive() {
    cout << "\n========== SJF (Preemptive) Demo ==========\n";
    resetProcesses();
    PSJF_reset();

    // Start with two longer jobs
    int p0 = createProcess(12, 0);
    int p1 = createProcess(8,  0);

    PSJF_addProcess(p0);
    PSJF_addProcess(p1);

    // At t=3, introduce a very short job to show preemption
    int shortJobPid = -1;

    for (int t = 0; t < 40 && !allTerminated(); ++t) {
        if (t == 3) {
            shortJobPid = createProcess(2, 0);
            PSJF_addProcess(shortJobPid);
            cout << "t=" << std::setw(2) << t << "  ++ new short job arrives: P" << shortJobPid << " (total=2)\n";
        }

        int pid = PSJF_nextProcess();
        if (pid < 0) break;
        cout << "t=" << std::setw(2) << t << "  -> run P" << pid << " (rem=" << remaining(pid) << ")\n";
        runOneInstruction(pid);
    }

    printProcSummary();
}

static void demoPriority_nonpreemptive() {
    cout << "\n====== Priority (Non-preemptive) Demo ======\n";
    resetProcesses();
    Priority_reset();

    // Lower prio value = higher priority.
    int p0 = createProcess(7, 2); // medium
    int p1 = createProcess(5, 5); // low
    int p2 = createProcess(6, 1); // high (will start)

    Priority_addProcess(p0);
    Priority_addProcess(p1);
    Priority_addProcess(p2);

    int lateHigh = -1;

    for (int t = 0; t < 40 && !allTerminated(); ++t) {
        // Introduce an even higher priority process while one is running.
        // Because this scheduler is NON-preemptive, it won't switch until current finishes.
        if (t == 2) {
            lateHigh = createProcess(3, 0); // highest
            Priority_addProcess(lateHigh);
            cout << "t=" << std::setw(2) << t << "  ++ new HIGHER priority arrives: P" << lateHigh << " (prio=0)\n";
        }

        int pid = Priority_nextProcess();
        if (pid < 0) break;
        cout << "t=" << std::setw(2) << t << "  -> run P" << pid << " (prio=" << g_prio[pid] << " rem=" << remaining(pid) << ")\n";
        runOneInstruction(pid);
    }

    printProcSummary();
}

static void demoRoundRobin() {
    cout << "\n============== Round Robin Demo ==============\n";
    resetProcesses();
    RR_reset(/*quantum=*/2);

    int p0 = createProcess(5, 0);
    int p1 = createProcess(4, 0);
    int p2 = createProcess(3, 0);

    RR_addProcess(p0);
    RR_addProcess(p1);
    RR_addProcess(p2);

    for (int t = 0; t < 40 && !allTerminated(); ++t) {
        int pid = RR_nextProcess();
        if (pid < 0) break;
        cout << "t=" << std::setw(2) << t << "  -> run P" << pid << " (rem=" << remaining(pid) << ") [qUsed=" << rrUsed << "/" << rrQuanta << "]\n";
        runOneInstruction(pid);
    }

    printProcSummary();
}

// -----------------------------
// main(): demonstrate them all
// -----------------------------
int main() {
    demoFCFS();
    demoSJF_nonpreemptive();
    demoSJF_preemptive();
    demoPriority_nonpreemptive();
    demoRoundRobin();
    return 0;
}