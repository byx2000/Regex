#pragma once

#include <Windows.h>

class StopWatch
{
	

public:
	StopWatch();
	void begin();
	void end();
	double duration();
private:
	enum { STOP, RUN } status;
	LARGE_INTEGER freq;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;
	
};