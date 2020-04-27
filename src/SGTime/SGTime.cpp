#include "SGTime.h"
#include <iostream>
#include <iomanip> // put_time
#include <ctime>   // localtime
#include <sstream> // stringstream

using namespace std;

void SG::SGTime::Update(double dtReal)
{
	if (!m_isPause)
	{
		m_TimeCurrent += dtReal * m_TimeScale;
	}
}

void SG::SGTime::SingleStep()
{
	if (!m_isPause)
	{
		m_TimeCurrent += (1.0f / 30.0f) * m_TimeScale;
	}
}

void SG::SGTime::DisplayTime()
{
	GenerateDateString();
	cout << GetDateString() << endl;
}

void SG::SGTime::GenerateDateString()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	m_DateString = ss.str();
}
