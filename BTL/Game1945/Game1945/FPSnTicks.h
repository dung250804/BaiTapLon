#pragma once

#ifndef FPS_TICKS_H
#define FPS_TICKS_H

class FPSnTicks
{
public:
	FPSnTicks();
	~FPSnTicks();

	void start();
	void stop();
	void paused();
	void unpaused();

	int GetTicks();
	bool is_paused();
	bool is_started();

private:
	int start_tick;
	int paused_tick;

	bool is_paused_;
	bool is_started_;
};



#endif