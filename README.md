Dining Philosophers Problem
===========================


The Dining Philosophers Problem is a process synchronization problem first proposed by Dijkstra.  A group of Philosophers sit around a table taking turns thinking and eating.  Adjacent philosophers share a fork, and a philosopher must acquire both forks before they begin eating.  While thinking, they ignore the forks.


This implementation utilizes C++11's lock() method to acquire both forks at the same time.
