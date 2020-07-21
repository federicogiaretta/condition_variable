// test_PC.cpp

#include <iostream>
using std::cout;
using std::endl;
#include <thread>
using std::thread;
#include <mutex>
using std::mutex;
#include <vector>
using std::vector;
#include "PC.h"

const int num_consumers{4};
const int items_to_consume{200};
const int items_to_produce{items_to_consume * num_consumers};

PC q;

void producer() 
{
	for (int i=1; i <= items_to_produce; ++i) {
		cout << "Producer ---> " << i << endl;	
		q.append(i);
	}
}

void consumer(int cons_i) 
{
	for (int i=0; i < items_to_consume; ++i) {
		datatype d = q.take();
		cout << "Consumer (" << cons_i << ") --->" << d << endl;
	}
}

int main()
{
	// start the producer thread
	thread prod1(producer);

	// start the consumer threads
	vector<thread> consumers;
	for (int i=0; i<num_consumers; ++i)
		consumers.push_back(thread{consumer, i});
	
	prod1.join();
  
	std::vector<std::thread>::iterator consumer_it;
	for (consumer_it=consumers.begin(); consumer_it != consumers.end(); ++consumer_it)
		consumer_it->join();

	std::cout<<"Exiting from Main Thread"<<std::endl;
	return 0;
}