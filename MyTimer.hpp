#ifndef INC_MYTIMER_H
#define INC_MYTIMER_H
#include <SFML\System.hpp>

struct MyTimer {
	int			Time;
	sf::Clock	clk;
	bool		started;

	MyTimer(int time):
	Time(time),
	started(false){

	}

	void StartTimer() {
		clk.Reset();
		started = true;
	}
	int GetTicks() {
		return clk.GetElapsedTime();
	}
	bool End() {
		if(Time == 0) return false;
		int current = clk.GetElapsedTime();
		if(current  > Time) {
			return true;
		} else return false;
	}
	bool is_started() {
		return started;
	}
	
};
#endif