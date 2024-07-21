#include "Onyx/Core/Timer.h"

Onyx::Timer::Timer() {
    m_bIsRunning = false;
    Reset();
}

void Onyx::Timer::Tick()
{
    if (m_bIsRunning) {
        m_tPrevious = m_tCurrent;
        m_tCurrent = std::chrono::high_resolution_clock::now();

        m_Duration += (m_tCurrent - m_tPrevious);
    }
}

void Onyx::Timer::Start()
{
    m_bIsRunning = true;
}

void Onyx::Timer::Stop()
{
    m_bIsRunning = false;
}

void Onyx::Timer::Reset()
{
    m_tPrevious = std::chrono::high_resolution_clock::now();
    m_tCurrent = std::chrono::high_resolution_clock::now();

    m_Duration = {};
}