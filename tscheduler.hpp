#pragma once

typedef unsigned thread_id;
typedef unsigned dom_id;
class task;
#include <mutex>
#include <thread>
#include <map>
#include <condition_variable>
#include <queue>

union thread_val {
	std::condition_variable *cv;
	task *t;
};

struct tscheduler {

	tscheduler();
	virtual void add_task(task*);
	task* get_task(unsigned thread_id);
	virtual void resolve();

	std::mutex resolve_m;
	bool stop;

	std::thread resolve_t;
	std::chrono::duration<long> resolve_t_to = std::chrono::seconds(5);

	std::map<thread_id, thread_val> threads;

	std::mutex thread_m;
	virtual ~tscheduler();

	void stopp();

	private:
		std::queue<task*> tasks;
		std::mutex tasks_m;
};
