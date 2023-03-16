#pragma once
#include <iostream>
#include <chrono>

class PerformanceMeasurement {
public:
    PerformanceMeasurement() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    ~PerformanceMeasurement() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Duration: " << duration.count() << "ms" << std::endl;
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
};