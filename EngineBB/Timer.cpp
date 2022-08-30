#include "pch.h"
#include "Timer.h"

Timer::Timer()
    : m_Dtime(0.0f)
    , m_SecondsPerCount(0.0f)
    , m_DeltaTime(0.0f)
    , m_ElapsedTime(0.0f)
    , m_BaseTime(0)
    , m_PausedTime(0)
    , m_StopTime(0)
    , m_PrevTime(0)
    , m_CurrTime(0)
    , m_Stopped(false)
{
    __int64 countsPerSec = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
    m_SecondsPerCount = 1.0f / (double)countsPerSec;
}

Timer::~Timer()
{
}

// Reset했을때부터의 시간을 리턴한다.stop했을때의 시간은 포함하지 않는다
float Timer::TotalTime()const
{
    // If we are stopped, do not count the time that has passed since we stopped.
    // Moreover, if we previously already had a pause, the distance 
    // mStopTime - mBaseTime includes paused time, which we do not want to count.
    // To correct this, we can subtract the paused time from mStopTime:  
    //
    //                     |<--paused time-->|
    // ----*---------------*-----------------*------------*------------*------> time
    //  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

    if (m_Stopped)
    {
        return (float)(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
    }

    // The distance mCurrTime - mBaseTime includes paused time,
    // which we do not want to count.  To correct this, we can subtract 
    // the paused time from mCurrTime:  
    //
    //  (mCurrTime - mPausedTime) - mBaseTime 
    //
    //                     |<--paused time-->|
    // ----*---------------*-----------------*------------*------> time
    //  mBaseTime       mStopTime        startTime     mCurrTime

    else
    {
        return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
    }
}

float Timer::DeltaTime() const
{
    //DebugString::PDS("%f", (float)m_Dtime);

    return (float)m_Dtime;
}

void Timer::Reset()
{
    __int64 currTime;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    m_BaseTime = currTime;
    m_PrevTime = currTime;
    m_StopTime = 0.0f;
    m_Stopped = false;
}

void Timer::Start()
{
    __int64 startTime = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

    // Accumulate the time elapsed between stop and start pairs.
    //
    //                     |<-------p------->|
    // ----*---------------*-----------------*------------> time
    //  mBaseTime       mStopTime        startTime     

    if (m_Stopped)
    {
        m_PausedTime += (startTime - m_StopTime); // startTime - m_StopTime = p(멈췄던 시간)

        m_PrevTime = startTime;
        m_StopTime = 0.0f;
        m_Stopped = false;
    }
}

void Timer::Stop()
{
    if (!m_Stopped)
    {
        __int64 currTime = 0;
        QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

        m_StopTime = currTime;
        m_Stopped = true;
    }
}

void Timer::Tick()
{
    if (m_Stopped)
    {
        m_DeltaTime = 0.0f;
        return;
    }

    __int64 currTime = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
    m_CurrTime = currTime;

    // m_DeltaTime = 이전 loop가 시작된시간 ~ 현재 loop가 시작된시간(/ms)
    m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

    m_PrevTime = m_CurrTime;

    // 누적시간
    m_ElapsedTime += m_DeltaTime;

    if (m_DeltaTime < 0.0f)
    {
        m_DeltaTime = 0.0f;
    }
}

/// <summary>
/// Tick()을 잰뒤에 프레임을 고정해 주어야 한다.
/// </summary>
/// <param name="fps"></param>
/// <returns></returns>
bool Timer::FixFrame(float fps)
{
    // 누적시간(m_ElapsedTime)이 1/프레임 보다 커지면 0으로 초기화
    // ex) 60프레임이라면 m_ElapsedTime이 0.01666보다 커지게되면 true값을 반환한다.
    if (m_ElapsedTime > 1.0f / (fps))
    {
        m_Dtime = m_ElapsedTime;
        m_ElapsedTime = 0.0f;
        return true;
    }
    else
    {
        return false;
    }
}

