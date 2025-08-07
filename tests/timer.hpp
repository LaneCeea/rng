#pragma once

#include <chrono>
#include <string>
#include <cstdio>

class CPUTimer {
public:
    using ClockTy = std::chrono::steady_clock;
    using TimePointTy = ClockTy::time_point;
    using DurationTy = std::chrono::duration<double, std::milli>;

public:
    CPUTimer(const std::string& Info) {
        m_Info = Info;
        m_Start = ClockTy::now();
    }
    
    ~CPUTimer() {
        TimePointTy End = ClockTy::now();
        DurationTy Duration = End - m_Start;
        std::printf("%30s - %10.5f ms\n", m_Info.c_str(), Duration.count());
    }

private:
    std::string m_Info;
    TimePointTy m_Start;
};
