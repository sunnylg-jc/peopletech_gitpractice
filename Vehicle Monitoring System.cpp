#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// Enum for sensor status
enum class SensorStatus {
    OK,
    WARNING,
    CRITICAL
};

// Base Sensor interface
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual SensorStatus getStatus() const = 0;
    virtual double getData() const = 0;
    virtual std::string getName() const = 0;
    virtual void update() = 0;
};

// EngineSensor with deterministic update
class EngineSensor : public Sensor {
private:
    double temperature;
    double step = 1.5;
    bool increasing = true;

public:
    EngineSensor() : temperature(75.0) {}

    void update() override {
        if (increasing) {
            temperature += step;
            if (temperature >= 120.0)
                increasing = false;
        } else {
            temperature -= step;
            if (temperature <= 70.0)
                increasing = true;
        }
    }

    SensorStatus getStatus() const override {
        if (temperature < 90.0) return SensorStatus::OK;
        else if (temperature < 110.0) return SensorStatus::WARNING;
        else return SensorStatus::CRITICAL;
    }

    double getData() const override {
        return temperature;
    }

    std::string getName() const override {
        return "Engine Sensor";
    }
};

// BatterySensor with deterministic update
class BatterySensor : public Sensor {
private:
    double voltage;
    double step = 0.1;
    bool increasing = true;

public:
    BatterySensor() : voltage(12.5) {}

    void update() override {
        if (increasing) {
            voltage += step;
            if (voltage >= 14.0)
                increasing = false;
        } else {
            voltage -= step;
            if (voltage <= 11.5)
                increasing = true;
        }
    }

    SensorStatus getStatus() const override {
        if (voltage >= 12.5) return SensorStatus::OK;
        else if (voltage >= 12.0) return SensorStatus::WARNING;
        else return SensorStatus::CRITICAL;
    }

    double getData() const override {
        return voltage;
    }

    std::string getName() const override {
        return "Battery Sensor";
    }
};

// TirePressureSensor with deterministic update
class TirePressureSensor : public Sensor {
private:
    double pressure;
    double step = 0.5;
    bool increasing = true;

public:
    TirePressureSensor() : pressure(32.0) {}

    void update() override {
        if (increasing) {
            pressure += step;
            if (pressure >= 40.0)
                increasing = false;
        } else {
            pressure -= step;
            if (pressure <= 28.0)
                increasing = true;
        }
    }

    SensorStatus getStatus() const override {
        if (pressure >= 30.0 && pressure <= 36.0) return SensorStatus::OK;
        else if ((pressure >= 28.0 && pressure < 30.0) || (pressure > 36.0 && pressure <= 38.0))
            return SensorStatus::WARNING;
        else
            return SensorStatus::CRITICAL;
    }

    double getData() const override {
        return pressure;
    }

    std::string getName() const override {
        return "Tire Pressure Sensor";
    }
};

// Vehicle class holding sensors
class Vehicle {
private:
    std::string id;
    std::vector<std::shared_ptr<Sensor>> sensors;

public:
    Vehicle(const std::string& vehicleId) : id(vehicleId) {}

    void addSensor(const std::shared_ptr<Sensor>& sensor) {
        sensors.push_back(sensor);
    }

    void updateSensors() {
        for (auto& sensor : sensors) {
            sensor->update();
        }
    }

    void printReport() const {
        std::cout << "Vehicle ID: " << id << "\n";
        for (const auto& sensor : sensors) {
            std::cout << "  " << sensor->getName() << ": " << sensor->getData() << " | Status: ";
            switch (sensor->getStatus()) {
                case SensorStatus::OK:
                    std::cout << "OK";
                    break;
                case SensorStatus::WARNING:
                    std::cout << "WARNING";
                    break;
                case SensorStatus::CRITICAL:
                    std::cout << "CRITICAL";
                    break;
            }
            std::cout << "\n";
        }
        std::cout << "----------------------\n";
    }

    std::string getId() const {
        return id;
    }
};

// Singleton VehicleManager without threading
class VehicleManager {
private:
    std::vector<std::shared_ptr<Vehicle>> vehicles;

    VehicleManager() {}

public:
    VehicleManager(const VehicleManager&) = delete;
    VehicleManager& operator=(const VehicleManager&) = delete;

    static VehicleManager& getInstance() {
        static VehicleManager instance;
        return instance;
    }

    void addVehicle(const std::shared_ptr<Vehicle>& vehicle) {
        vehicles.push_back(vehicle);
    }

    void removeVehicle(const std::string& id) {
        vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(),
            [&id](const std::shared_ptr<Vehicle>& v) {
                return v->getId() == id;
            }), vehicles.end());
    }

    void updateAllVehicles() {
        for (auto& vehicle : vehicles) {
            vehicle->updateSensors();
        }
    }

    void printAllReports() const {
        for (const auto& vehicle : vehicles) {
            vehicle->printReport();
        }
    }
};

int main() {
    auto& manager = VehicleManager::getInstance();

    auto car1 = std::make_shared<Vehicle>("Car-001");
    car1->addSensor(std::make_shared<EngineSensor>());
    car1->addSensor(std::make_shared<BatterySensor>());
    car1->addSensor(std::make_shared<TirePressureSensor>());

    auto car2 = std::make_shared<Vehicle>("Car-002");
    car2->addSensor(std::make_shared<EngineSensor>());
    car2->addSensor(std::make_shared<BatterySensor>());
    car2->addSensor(std::make_shared<TirePressureSensor>());

    manager.addVehicle(car1);
    manager.addVehicle(car2);

    char choice;
    do {
        std::cout << "Update sensors and print reports? (y/n): ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            manager.updateAllVehicles();
            manager.printAllReports();
        }
    } while (choice == 'y' || choice == 'Y');

    std::cout << "Exiting...\n";
    return 0;
}
