
mutex cout_mutex;


template<typename T1,typename T2>
void Philosopher::eat(const duration<T1,T2> &d)
{
	{
		unique_lock<mutex> lck_left {lh,defer_lock};
		unique_lock<mutex> lck_right {rh,defer_lock};
		lock(lck_left,lck_right);
		action = PAction::Eating;

		{
			std::lock_guard<mutex> lock(cout_mutex);
			std::cout << "Philosopher #" << id << " eating for " << d.count() << "ms\n";
		}

		std::this_thread::sleep_for(d);
	}

	{
		std::lock_guard<mutex> lock(cout_mutex);
		std::cout << "Philosopher #" << id << " finished eating.\n";
	}

	action = PAction::Waiting;
}

template<typename T1,typename T2>
void Philosopher::thinking(const duration<T1,T2> &d)
{
	action = PAction::Thinking;

	{
		std::lock_guard<mutex> lock(cout_mutex);
		std::cout << "Philosopher #" << id << " thinking for " << d.count() << "ms\n";
	}

	std::this_thread::sleep_for(d);

	{
		std::lock_guard<mutex> lock(cout_mutex);
		std::cout << "Philosopher #" << id << " finished thinking\n";
	}

	action = PAction::Waiting;
}

