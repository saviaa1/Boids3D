#include <chrono>

class PerfTimer {
public:
    PerfTimer() {
        start_ = std::chrono::high_resolution_clock::now();
    }
    double GetMS() {
        auto duration = std::chrono::high_resolution_clock::now() - start_;

        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count() * 0.001;
    }

private:
    std::chrono::system_clock::time_point start_;
};
