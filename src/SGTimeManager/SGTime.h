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
	class SGTime
	{
	public:
		void Initialize(Resolution res);
		void Update();
		void SingleStep();
		void GenerateDateString(); // may get down the performance
		void DisplayTime(); // this function is for debug

		inline const std::string& GetDateString() { return m_DateString; }
		inline double GetCurrentTime() { return m_CurrentTime; }
		inline double GetElapse() { return m_Elapse; }
		inline void SetPaused(bool pause) { m_isPause = pause; }
		inline bool IsPaused() { return m_isPause; }
		inline void SetTimeScale(double scale) { m_TimeScale = scale; }
		inline double GetTimeScale() { return m_TimeScale; }
	protected:
		Resolution m_Resolution;
		std::string m_DateString; // can be use for save data
		SystemClock::time_point m_TimeCurrent;
		SystemClock::time_point m_TimePrevious;
		double m_Elapse = 0.0;
		double m_CurrentTime = 0.0;
		double m_TimeScale = 1.0;
		bool m_isPause = false;
	};
}
