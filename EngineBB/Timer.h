#pragma once
#include <chrono>

/// <summary>
/// deltaŸ���� ������� 
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
	double m_SecondsPerCount;	// Ŭ�ϴ� �ɸ��� �ð�, (1 / m_SecondsPerCount)�� �����ָ� (/s), (1 / m_SecondsPerCount * 1000)�� �����ָ� (/ms) �� ���´�.
	double m_DeltaTime;
	double m_ElapsedTime;

	__int64 m_BaseTime;
	__int64 m_PausedTime;		
	__int64 m_StopTime;			// stop��Ų �ð�
	__int64 m_PrevTime;			// ���� �ֱٿ� reset�ϰų� start�� �ð� / �Ǵ� Tick�� ��� �ð�
	__int64 m_CurrTime;			// 

	bool m_Stopped;				// stop�������� true
};
