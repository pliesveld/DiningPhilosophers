#ifndef __philosopher_hpp__
#define __philosopher_hpp__
#include <thread>
//using std::this_thread;
#include <mutex>
using std::unique_lock;
using std::defer_lock;
#include <chrono>
using std::chrono::duration;

#include "queue.hpp"


class Philosopher
{
public:
	Philosopher(size_t _id, mutex &_lh, mutex &_rh,QueueAction &_task) : id(_id), lh(_lh), rh(_rh), task_queue(_task) { };

	size_t id;
	mutex &lh;
	mutex &rh;
	QueueAction &task_queue;

	PAction action = PAction::Waiting;

	template<typename T1,typename T2>
	void eat(const duration<T1,T2> &d);

	template<typename T1,typename T2>
	void thinking(const duration<T1,T2> &d);

};

template<typename T,size_t N>
vector<Philosopher>
set_table(T (&table) [N], QueueAction &taskq)
{
	vector<Philosopher> v;
	v.reserve(N);
	v.emplace_back(Philosopher(0,table[N-1],table[0],taskq));
	for(size_t i = 1; i < N;++i)
		v.emplace_back(Philosopher(i,table[i-1],table[i],taskq));
	
	return v;
}

#include "philosopher.tcc"

#endif
