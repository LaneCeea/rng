#pragma once

#include <chrono>
#include <cstdio>

class CPUTimer {
public:
    using ClockTy = std::chrono::steady_clock;
    using TimePointTy = ClockTy::time_point;
    using DurationTy = std::chrono::duration<double, std::milli>;

public:
    CPUTimer(std::string_view Info) :
        m_Info(Info),
        m_Start(ClockTy::now())
    {}
    
    ~CPUTimer() {
        TimePointTy End = ClockTy::now();
        DurationTy duration = End - m_Start;
        std::printf("%30s - %10.5f ms\n", m_Info.data(), duration.count());
    }

private:
    std::string_view m_Info;
    TimePointTy m_Start;
};
