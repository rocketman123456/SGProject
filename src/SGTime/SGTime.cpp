#include "SGTime.h"
#include <iostream>
using namespace std;

SG::SGTime::SGTime()
{
	nowtime = time(NULL); //获取日历时间
	local = localtime(&nowtime);  //获取当前系统时间
}

SG::SGTime::~SGTime()
{

}

void SG::SGTime::dsptime() {
    char* pxq[] = { "日","一","二","三","四","五","六" };
    cout << local->tm_year + 1900 << "年" << local->tm_mon + 1 << "月" << local->tm_mday << "日 ";
    cout << local->tm_hour << ":" << local->tm_min << ":" << local->tm_sec << " ";
}