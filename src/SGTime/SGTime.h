#pragma once
#include <time.h>
namespace SG
{
	// 用于快速获取时间，包括不同精度等级
	class SGTime
	{
	private:
		// time_t 类型为 __int64
		time_t nowtime;
		struct tm* local;//精度为秒
	public:
		SGTime();
		~SGTime();
		void DSPTime();
	};
}