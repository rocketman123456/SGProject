#include "SGTime.h"
#include <iostream>
using namespace std;

SG::SGTime::SGTime()
{
	nowtime = time(NULL); //��ȡ����ʱ��
	local = localtime(&nowtime);  //��ȡ��ǰϵͳʱ��
}

SG::SGTime::~SGTime()
{

}

void SG::SGTime::dsptime() {
    char* pxq[] = { "��","һ","��","��","��","��","��" };
    cout << local->tm_year + 1900 << "��" << local->tm_mon + 1 << "��" << local->tm_mday << "�� ";
    cout << local->tm_hour << ":" << local->tm_min << ":" << local->tm_sec << " ";
}