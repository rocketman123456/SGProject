#include "SGTime.h"
#include <iostream>
#include <iomanip> // put_time
#include <ctime>   // localtime
#include <sstream> // stringstream
using namespace std;
using namespace SG;

void SG::SGTime::Initialize(Resolution res)
{
	m_Resolution = res;
	m_TimeCurrent = SystemClock::now();
	m_TimePrevious = m_TimeCurrent;
}

void SG::SGTime::Update()
{
	if (!m_isPause)
	{
		m_TimeCurrent = SystemClock::now();
		m_TimePrevious = m_TimeCurrent;
	}
}

double SG::SGTime::GetElapse()
{
	if (!m_isPause) {
		m_TimeCurrent = SystemClock::now();
	}
	switch (m_Resolution)
	{
	case Resolution::Low: {
		Seconds duration = std::chrono::duration_cast<Seconds>(m_TimeCurrent - m_TimePrevious);
		m_Elapse = double(duration.count()) * Seconds::period::num / Seconds::period::den * m_TimeScale;
	} break;
	case Resolution::Normal: {
		MicroSeconds duration = std::chrono::duration_cast<MicroSeconds>(m_TimeCurrent - m_TimePrevious);
		m_Elapse = double(duration.count()) * MicroSeconds::period::num / MicroSeconds::period::den * m_TimeScale;
	} break;
	case Resolution::High: {
		ManoSeconds duration = std::chrono::duration_cast<ManoSeconds>(m_TimeCurrent - m_TimePrevious);
		m_Elapse = double(duration.count()) * ManoSeconds::period::num / ManoSeconds::period::den * m_TimeScale;
	} break;
	default:
		break;
	}
	return m_Elapse;
}

void SG::SGTime::SingleStep()
{
	m_TimeCurrent = SystemClock::now();
	m_TimePrevious = m_TimeCurrent;
	if (!m_isPause)
	{	
		m_Elapse = (1.0f / 30.0f) * m_TimeScale;
	}
	else
	{
		m_Elapse = 0.0;
	}
	m_CurrentTime += m_Elapse;
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