#pragma once
#include <time.h>
namespace SG
{
	// ���ڿ��ٻ�ȡʱ�䣬������ͬ���ȵȼ�
	class SGTime
	{
	private:
		// time_t ����Ϊ __int64
		time_t nowtime;
		struct tm* local;//����Ϊ��
	public:
		SGTime();
		~SGTime();
		void DSPTime();
	};
}