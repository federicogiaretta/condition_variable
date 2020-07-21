// PC.h

#ifndef PC_H
#define PC_H

#include <queue>
#include <mutex>
#include <condition_variable>

typedef int datatype;

class PC
{
public:
	void append(const datatype& v);
	datatype take();

private:
	std::queue<datatype> buffer_;
	std::mutex mutex_;
	std::condition_variable not_empty_;
};


#endif