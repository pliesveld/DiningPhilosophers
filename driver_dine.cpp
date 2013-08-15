#include <vector>
using std::vector;
#include <thread>
using std::thread;
#include <mutex>
using std::mutex;

#include <iostream>
using std::cout;
using std::endl;

#include  <chrono>
using std::chrono::milliseconds;
using std::chrono::seconds;

#include <list>
using std::list;
#include <utility>
using std::move;
using std::pair;
#include <functional>
using std::ref;
using std::bind;

#include <random>
using std::uniform_int_distribution;
using std::default_random_engine;

#include "philosopher.hpp"




class Rand_int
{
public:
   std::random_device rd;
   std::mt19937 gen;
   std::uniform_int_distribution<> uniform_dist;

	Rand_int(int lo, int hi) : rd(), gen(rd()), uniform_dist(lo,hi) { }
	inline int operator()() { return uniform_dist(gen); }
};
	


QueueAction MakeRandomQueue()
{
	Rand_int ac(1,2);
	Rand_int dur(1,50);


	QueueAction qa;
	for(int i = 0;i < 1000;++i)
	{
		if(ac()%2 == 0)
		{
			pair<PAction,size_t> ne{PAction::Eating,dur()};
			qa.m_queue.emplace_back(move(ne));
		} else {
			pair<PAction,size_t> ne{PAction::Thinking,dur()};
			qa.m_queue.emplace_back(move(ne));
		}

	}

	return qa;
}


void PhilThread(Philosopher &p)
{
	PAction na;
	size_t d;

	while (true)
	{
		std::tie(na,d) = p.task_queue.next();
		switch(na)
		{
			case PAction::Thinking:
				p.thinking(milliseconds{d*10});
				break;
			case PAction::Eating:
				p.eat(milliseconds{d*10});
				break;
			case PAction::Waiting:
				break;
			case PAction::Finished:
				return;
				break;

		}
	}

}


int main()
{
	mutex table[5];
	QueueAction tq(MakeRandomQueue());
	vector<Philosopher> vec = set_table(table,tq);

	vector<thread> mthreads;

	mthreads.reserve(5);

	for( auto &pd : vec )
	{
		thread nthread{PhilThread,ref(pd)};
		mthreads.emplace_back(move(nthread));
	}

	
	for( auto &t : mthreads )
	{
		t.join();
	}


}
