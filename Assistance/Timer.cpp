#include "pch.h"
#include "Timer.h"

LARGE_INTEGER Timer::m_frequency;
std::vector < std::tuple <LARGE_INTEGER, LARGE_INTEGER, std::string >> Timer::m_TimeTag_V;

void Timer::InitTimer()
{
	QueryPerformanceFrequency(&m_frequency);
}

void Timer::StartMeasure(const std::string& setTag)
{
	LARGE_INTEGER BeginTime;
	QueryPerformanceCounter(&BeginTime);
	m_TimeTag_V.push_back(std::make_tuple(BeginTime, LARGE_INTEGER(), setTag));
}

void Timer::StopMeasure(const std::string& findTag)
{
	LARGE_INTEGER endTime;
	QueryPerformanceCounter(&endTime);

	// �±װ� ��ġ�Ѵٸ� ���ͷ����͸� ��ȯ
	auto it =
		std::find_if(m_TimeTag_V.begin(), m_TimeTag_V.end(), [findTag](const std::tuple< const LARGE_INTEGER&, const LARGE_INTEGER&, const std::string& >& e)
		{
			return std::get<static_cast<int>(TimerComp::Tag)>(e) == findTag;
		}
	);

	if (it != m_TimeTag_V.end())
	{
		std::get<static_cast<int>(TimerComp::EndTime)>(*it) = endTime;
	}
}

void Timer::PrintResult()
{
	// ���
	for (int i = 0; i < m_TimeTag_V.size(); ++i)
	{
		if (std::get<static_cast<int>(TimerComp::EndTime)>(m_TimeTag_V[i]).QuadPart == 0)
		{
			std::cout << "Tag : " << std::get<static_cast<int>(TimerComp::Tag)>(m_TimeTag_V[i]) << ", \t���� : ������ �ð� ����" << std::endl;
			continue;
		}

		INT64 elapsedTime = std::get<static_cast<int>(TimerComp::EndTime)>(m_TimeTag_V[i]).QuadPart - std::get<static_cast<int>(TimerComp::StartTime)>(m_TimeTag_V[i]).QuadPart;
		float duringTime = (float)elapsedTime / (float)m_frequency.QuadPart;

		std::cout << "Tag : "<< std::get<static_cast<int>(TimerComp::Tag)>(m_TimeTag_V[i]) <<  ", \t�ɸ� �ð� = "<< duringTime * 1000 << "/ms" << std::endl;
		DebugString::PDS("Tag : %s, �ɸ� �ð� = %f /ms", std::get<static_cast<int>(TimerComp::Tag)>(m_TimeTag_V[i]).c_str(), duringTime * 1000);
	}
}
