#include <mutex>
using std::mutex;
using std::lock_guard;
#include <list>
using std::list;


#include "queue.hpp"
mutex m_acc;


Task QueueAction::next()
{
	lock_guard<mutex> lock{m_acc};
	Task t{PAction::Finished,0};
	if(!m_queue.empty())
	{
		t = m_queue.front();
		m_queue.pop_front();
		return t;
	}

	return t;
}
