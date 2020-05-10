#pragma once
#include "SGIRuntimeModule.h"
#include <time.h>
#include <string>
#include <chrono>

namespace SG
{
	enum Resolution
	{
		Low = 0,
		Normal,
		High,
	};

	using SystemClock = std::chrono::system_clock;
	using ManoSeconds = std::chrono::nanoseconds;
	using MicroSeconds = std::chrono::microseconds;
	using Seconds = std::chrono::seconds;
	// 用于快速获取时间，包括不同精度等级
	Interface SGTime
	{
	public:
		SGTime() {
			m_TimeCurrent = SystemClock::now();
			m_TimePrevious = m_TimeCurrent;
		}
		void Update();
		void SingleStep();
		void GenerateDateString(); // may get down the performance
		void DisplayTime(); // this function is for debug

		virtual double GetElapse() = 0;

		inline double GetCurrentTime() { return m_CurrentTime; }
		inline void SetPaused(bool pause) { m_isPause = pause; }
		inline bool IsPaused() { return m_isPause; }
		inline void SetTimeScale(double scale) { m_TimeScale = scale; }
		inline double GetTimeScale() { return m_TimeScale; }
		inline const std::string& GetDateString() { return m_DateString; }
	protected:
		std::string m_DateString; // can be use for save data
		SystemClock::time_point m_TimeCurrent;
		SystemClock::time_point m_TimePrevious;
		double m_Elapse = 0.0;
		double m_CurrentTime = 0.0;
		double m_TimeScale = 1.0;
		bool m_isPause = false;
	};

	class SGTimeHigh : implements SGTime
	{
	public:
		virtual double GetElapse() override;
	};

	class SGTimeNormal : implements SGTime
	{
	public:
		virtual double GetElapse() override;
	};

	class SGTimeLow : implements SGTime
	{
	public:
		virtual double GetElapse() override;
	};
}
