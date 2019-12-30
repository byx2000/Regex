#pragma once

class StopWatch
{
public:
	StopWatch();
	~StopWatch();
	void begin();
	void end();
	double duration();
private:
	enum { STOP, RUN } status;
	void* freq;
	void* beginTime;
	void* endTime;
};