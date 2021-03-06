#ifndef DOMAIN_SETTINGS_HPP
#define DOMAIN_SETTINGS_HPP

//#include "task.hpp"
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

struct domain_settings {

	std::priority_queue<task*, std::vector<task*>, task> task_list;
	long interval;
	std::mutex list_mutex;
	std::condition_variable nfull;
	std::function<void()> fillup;
	bool do_fillup;

	domain_settings() : list_mutex() {

		interval = 0;
		fillup = nullptr;
		do_fillup = true;
	}

	void operator=(domain_settings &&other) {
		
		std::swap(fillup, other.fillup);
		interval = other.interval;
		do_fillup = other.do_fillup;
	}
};

#endif
