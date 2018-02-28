#pragma once

#include <chrono>

class SimpleTimer {
public:
    SimpleTimer() : m_timestamp{timer_clock::now()} {
    }

    void reset() {
        m_timestamp = timer_clock::now();
    }

    double elapsed() const {
        return std::chrono::duration_cast<std::chrono::duration<double,
                std::milli>>(timer_clock::now() - m_timestamp).count();
    }

private:
    typedef std::chrono::high_resolution_clock timer_clock;
    std::chrono::time_point<timer_clock> m_timestamp;
};
