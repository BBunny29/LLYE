#pragma once
#include <windows.h>
#include <ctime>
#include <vector>
#include <tuple>

/// <summary>
/// 속도를 측정하기 위해 만든 클래스
/// 
/// 2022.08.17 B.Bunny
/// </summary>

/// ※ 중요 함수 ※
/// WINAPI : QueryPerformanceCounter()
//  성능 카운터값을 가져온다.절대적인 시간값을 의미하는것 같다.
/// WINAPI : QueryPerformanceFrequency()
//  성능 카운터의 빈도를 가져온다.내 컴퓨터에서는 10000000이라는 결과를 얻었다.

//  1. 첫번째로 QueryPerformanceCounter()를 실행해 얻은값
//  2. 두번째로 QueryPerformanceCounter()를 실행해 얻은값
//  3. QueryPerformanceFrequency() 로 얻은 성능 카운터의 빈도
//
/// => ((2 - 1) / 3) * 1000  = 1과 2사이의 걸린시간(/ms = 1/1000초)

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
/// 시간측정을 시작하는 함수와 끝내는 함수는 시간재는 일 외의 일은 하지 않도록했다.
/// debugString을 출력하는것만으로도 1~2초정도의 부하가 생기기때문.  
/// 시간을 재고 tuple에 <시작시간, 끝나는시간, 태그> 를 넣고 그것들을 벡터에 넣어서 저장하고 
/// Print함수에서 다같이 출력하는식으로 작동한다.
/// 
/// 멤버로 static변수나 static 함수를 가지고있다면 전역생성자가 호출되지않아도 그 변수와 함수를 사용할수 있다.
/// (그 함수들을 사용할때 생성자가 호출되었다고 보증할수없다.)
/// 그래서 InitTimer함수를 만들었다.
/// 
/// StopMeasure()함수를 호출할때 tag로 m_TimeTag_V를 탐색하는 역할까지 같이하기 때문에
/// 같은 시기에 시간을 재더라도 뒤쪽으로 갈수록 오차가 쌓여
/// 1번쨰와 4번째의 차이가 거의 1초차이가 난다.
/// StopMeasure()함수에서 끝나는 시간을 담아놓는 vector를 따로 만들고
/// PrintResult()함수에서 탐색하는 식으로 변경해야겠다.
///  
/// 위와 같이 수정하려했는데 그러지 않아도 될것같다. 
/// m_TimeTag_V가 1000개의 요소를 가지고 있을때 첫번째로 잰시간과의 차이가 4배정도 차이가 난다.
/// 그런데 내가만들 게임에서 과연 1000개의 타이머가 필요할까?
/// 10개정도만 있어도 충분할것같기에 나중에 필요하다면 위와같이 수정하겠다.
/// 
/// 2022.08.20 B.Bunny
/// </summary>

