#ifndef __queue_hpp__
#define __queue_hpp__
#include <list>
#include <mutex>
#include <utility>
using std::pair;



enum class PAction {Waiting, Thinking, Eating, Finished };
using Task=pair<PAction,size_t>;

class QueueAction
{
	QueueAction(const QueueAction &rhs) = delete;
	QueueAction& operator=(const QueueAction &rhs) = delete;
public:
	QueueAction() = default;
	~QueueAction() = default;
	QueueAction(QueueAction &&rhs) = default;
	QueueAction& operator=(QueueAction &&rhs) = default;


	list<Task> m_queue;
	Task next();
};

#endif
