#include "StopWatch.h"

StopWatch::StopWatch()
{
	status = STOP;
	QueryPerformanceFrequency(&freq);
	memset(&beginTime, 0, sizeof(beginTime));
	memset(&endTime, 0, sizeof(endTime));
}

void StopWatch::begin()
{
	if (status == STOP)
	{
		QueryPerformanceCounter(&beginTime);
		status = RUN;
	}
}

void StopWatch::end()
{
	if (status == RUN)
	{
		QueryPerformanceCounter(&endTime);
		status = STOP;
	}
}

double StopWatch::duration()
{
	if (status == STOP)
	{
		return (double)(endTime.QuadPart - beginTime.QuadPart) / (double)freq.QuadPart;
	}
	else
	{
		return -1;
	}
}
