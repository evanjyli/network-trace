// Simple trace logger for network packets
// Format: sender receiver length latency
#include <fstream>
#include <mutex>
#include <iostream>

class NetworkTraceLogger {
public:
    static NetworkTraceLogger* getInstance() {
        static NetworkTraceLogger instance("network_trace.log");
        return &instance;
    }
    
    void log(int sender, int receiver, unsigned length, long latency) {
        std::lock_guard<std::mutex> lock(mtx);
        if (logfile.is_open()) {
            logfile << sender << " " << receiver << " " << length << " " << latency << "\n";
            logfile.flush();
        }
    }
    
private:
    NetworkTraceLogger(const char* filename) {
        logfile.open(filename, std::ios::out | std::ios::app);
        if (!logfile.is_open()) {
            std::cerr << "Warning: Could not open network trace file: " << filename << std::endl;
        }
    }
    
    ~NetworkTraceLogger() {
        if (logfile.is_open()) {
            logfile.flush();
            logfile.close();
        }
    }
    
    // Delete copy constructor and assignment operator
    NetworkTraceLogger(const NetworkTraceLogger&) = delete;
    NetworkTraceLogger& operator=(const NetworkTraceLogger&) = delete;
    
    std::ofstream logfile;
    std::mutex mtx;
};
