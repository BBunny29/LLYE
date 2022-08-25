#pragma once
#include <chrono>

/// <summary>
/// delta타임을 얻기위한 
/// </summary>
class Timer :public Singleton<Timer>
{
public:
	Timer();
	~Timer();

	float TotalTime() const;  // in seconds
	float DeltaTime() const; // in seconds

	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  // Call every frame.

	bool FixFrame(float fps);

	double m_Dtime;
private:
	double m_SecondsPerCount;	// 클록당 걸리는 시간, (1 / m_SecondsPerCount)을 곱해주면 (/s), (1 / m_SecondsPerCount * 1000)을 곱해주면 (/ms) 가 나온다.
	double m_DeltaTime;
	double m_ElapsedTime;

	__int64 m_BaseTime;
	__int64 m_PausedTime;		
	__int64 m_StopTime;			// stop시킨 시간
	__int64 m_PrevTime;			// 가장 최근에 reset하거나 start한 시간 / 또는 Tick을 쟀던 시간
	__int64 m_CurrTime;			// 

	bool m_Stopped;				// stop시켰을시 true
};
