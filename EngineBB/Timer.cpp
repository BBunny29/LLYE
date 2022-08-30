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

// Reset������������ �ð��� �����Ѵ�.stop�������� �ð��� �������� �ʴ´�
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
        m_PausedTime += (startTime - m_StopTime); // startTime - m_StopTime = p(����� �ð�)

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

    // m_DeltaTime = ���� loop�� ���۵Ƚð� ~ ���� loop�� ���۵Ƚð�(/ms)
    m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

    m_PrevTime = m_CurrTime;

    // �����ð�
    m_ElapsedTime += m_DeltaTime;

    if (m_DeltaTime < 0.0f)
    {
        m_DeltaTime = 0.0f;
    }
}

/// <summary>
/// Tick()�� ��ڿ� �������� ������ �־�� �Ѵ�.
/// </summary>
/// <param name="fps"></param>
/// <returns></returns>
bool Timer::FixFrame(float fps)
{
    // �����ð�(m_ElapsedTime)�� 1/������ ���� Ŀ���� 0���� �ʱ�ȭ
    // ex) 60�������̶�� m_ElapsedTime�� 0.01666���� Ŀ���ԵǸ� true���� ��ȯ�Ѵ�.
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

