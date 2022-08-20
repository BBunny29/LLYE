#pragma once
#include <windows.h>
#include <ctime>
#include <vector>
#include <tuple>

/// <summary>
/// �ӵ��� �����ϱ� ���� ���� Ŭ����
/// 
/// 2022.08.17 B.Bunny
/// </summary>

/// �� �߿� �Լ� ��
/// WINAPI : QueryPerformanceCounter()
//  ���� ī���Ͱ��� �����´�.�������� �ð����� �ǹ��ϴ°� ����.
/// WINAPI : QueryPerformanceFrequency()
//  ���� ī������ �󵵸� �����´�.�� ��ǻ�Ϳ����� 10000000�̶�� ����� �����.

//  1. ù��°�� QueryPerformanceCounter()�� ������ ������
//  2. �ι�°�� QueryPerformanceCounter()�� ������ ������
//  3. QueryPerformanceFrequency() �� ���� ���� ī������ ��
//
/// => ((2 - 1) / 3) * 1000  = 1�� 2������ �ɸ��ð�(/ms = 1/1000��)

class Timer
{
	enum class TimerComp
	{
		StartTime = 0,
		EndTime,
		Tag,
	};

private:
	static LARGE_INTEGER m_frequency;
	static std::vector < std::tuple <LARGE_INTEGER,LARGE_INTEGER, std::string >> m_TimeTag_V;

public:
	static void InitTimer();

	static void StartMeasure(const std::string& setTag);
	static void StopMeasure(const std::string& findTag);

	static void PrintResult();
};

/// <summary>
/// 
/// �ð������� �����ϴ� �Լ��� ������ �Լ��� �ð���� �� ���� ���� ���� �ʵ����ߴ�.
/// debugString�� ����ϴ°͸����ε� 1~2�������� ���ϰ� ����⶧��.  
/// �ð��� ��� tuple�� <���۽ð�, �����½ð�, �±�> �� �ְ� �װ͵��� ���Ϳ� �־ �����ϰ� 
/// Print�Լ����� �ٰ��� ����ϴ½����� �۵��Ѵ�.
/// 
/// ����� static������ static �Լ��� �������ִٸ� ���������ڰ� ȣ������ʾƵ� �� ������ �Լ��� ����Ҽ� �ִ�.
/// (�� �Լ����� ����Ҷ� �����ڰ� ȣ��Ǿ��ٰ� �����Ҽ�����.)
/// �׷��� InitTimer�Լ��� �������.
/// 
/// StopMeasure()�Լ��� ȣ���Ҷ� tag�� m_TimeTag_V�� Ž���ϴ� ���ұ��� �����ϱ� ������
/// ���� �ñ⿡ �ð��� ����� �������� ������ ������ �׿�
/// 1������ 4��°�� ���̰� ���� 1�����̰� ����.
/// StopMeasure()�Լ����� ������ �ð��� ��Ƴ��� vector�� ���� �����
/// PrintResult()�Լ����� Ž���ϴ� ������ �����ؾ߰ڴ�.
///  
/// ���� ���� �����Ϸ��ߴµ� �׷��� �ʾƵ� �ɰͰ���. 
/// m_TimeTag_V�� 1000���� ��Ҹ� ������ ������ ù��°�� ��ð����� ���̰� 4������ ���̰� ����.
/// �׷��� �������� ���ӿ��� ���� 1000���� Ÿ�̸Ӱ� �ʿ��ұ�?
/// 10�������� �־ ����ҰͰ��⿡ ���߿� �ʿ��ϴٸ� ���Ͱ��� �����ϰڴ�.
/// 
/// 2022.08.20 B.Bunny
/// </summary>

