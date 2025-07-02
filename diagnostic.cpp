#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

// Enum for component status
enum class ComponentStatus {
    OK,
    ERROR
};

// Interface for diagnostics
class IDiagnostic {
public:
    virtual ComponentStatus runSelfCheck() = 0;
    virtual std::string generateReport() = 0;
    virtual ~IDiagnostic() = default;
};

// Engine Diagnostic class
class EngineDiagnostic : public IDiagnostic {
public:
    ComponentStatus runSelfCheck() override {
        std::cout << "Engine: Running self-check...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate work
        return ComponentStatus::OK;
    }

    std::string generateReport() override {
        return "Engine Report: OK";
    }
};

// Battery Diagnostic class
class BatteryDiagnostic : public IDiagnostic {
public:
    ComponentStatus runSelfCheck() override {
        std::cout << "Battery: Running self-check...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate work
        return ComponentStatus::OK;
    }

    std::string generateReport() override {
        return "Battery Report: OK";
    }
};

// Simple Singleton Logger (just prints to console)
class Logger {
private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
};

// Template function to print any report
template<typename T>
void printReport(const T& report) {
    std::cout << "[REPORT] " << report << std::endl;
}

// Diagnostics Manager that runs diagnostics asynchronously
class DiagnosticsManager {
    std::unique_ptr<IDiagnostic> engine;
    std::unique_ptr<IDiagnostic> battery;
    std::vector<std::string> reports;
    std::mutex reportMutex;
    std::mutex flagMutex;
    bool engineRunning = false;
    bool batteryRunning = false;

public:
    DiagnosticsManager() {
        engine = std::make_unique<EngineDiagnostic>();
        battery = std::make_unique<BatteryDiagnostic>();
    }

    void runEngineDiagnosticAsync() {
        flagMutex.lock();
        if (engineRunning) {
            Logger::getInstance().log("Engine diagnostic is already running!");
            flagMutex.unlock();
            return;
        }
        engineRunning = true;
        flagMutex.unlock();

        std::thread t([this]() {
            engine->runSelfCheck();
            auto report = engine->generateReport();

            reportMutex.lock();
            reports.push_back(report);
            reportMutex.unlock();

            Logger::getInstance().log(report);

            flagMutex.lock();
            engineRunning = false;
            flagMutex.unlock();
        });
        t.detach();
    }

    void runBatteryDiagnosticAsync() {
        flagMutex.lock();
        if (batteryRunning) {
            Logger::getInstance().log("Battery diagnostic is already running!");
            flagMutex.unlock();
            return;
        }
        batteryRunning = true;
        flagMutex.unlock();

        std::thread t([this]() {
            battery->runSelfCheck();
            auto report = battery->generateReport();

            reportMutex.lock();
            reports.push_back(report);
            reportMutex.unlock();

            Logger::getInstance().log(report);

            flagMutex.lock();
            batteryRunning = false;
            flagMutex.unlock();
        });
        t.detach();
    }

    void printAllReports() {
        reportMutex.lock();
        if (reports.empty()) {
            std::cout << "[INFO] No reports available yet.\n";
            reportMutex.unlock();
            return;
        }
        for (const auto& r : reports) {
            printReport(r);
        }
        reportMutex.unlock();
    }
};

// Main menu for user interaction
int main() {
    DiagnosticsManager manager;
    int choice = 0;

    do {
        std::cout << "\n--- Vehicle Diagnostics Menu ---\n";
        std::cout << "1. Run Engine Diagnostic\n";
        std::cout << "2. Run Battery Diagnostic\n";
        std::cout << "3. Show All Reports\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manager.runEngineDiagnosticAsync();
                break;
            case 2:
                manager.runBatteryDiagnosticAsync();
                break;
            case 3:
                manager.printAllReports();
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
