#pragma once
#include "SGIRuntimeModule.h"
#include <time.h>
#include <string>
#include <chrono>

namespace SG
{
	// 用于快速获取时间，包括不同精度等级
	class SGTime
	{
	public:
		explicit SGTime(float start = 0.0f) :m_TimeCurrent(start), m_TimeScale(1.0f), m_isPause(false) {};
		~SGTime() {};
		void DisplayTime(); // this function is for debug

		void Update(double dt);
		void SingleStep();
	public:
		void GenerateDateString(); // may get down the performance
		inline const std::string& GetDateString() { return m_DateString; }
		inline void SetPaused(bool pause) { m_isPause = pause; }
		inline bool IsPaused() { return m_isPause; }
		inline void SetTimeScale(float scale) { m_TimeScale = scale; }
		inline float GetTimeScale() { return m_TimeScale; }
		inline double GetTime() { return m_TimeCurrent; }
	protected:
		double m_TimeCurrent;
		float m_TimeScale;
		bool m_isPause;
		std::string m_DateString; // can be use for save data
	};
}
