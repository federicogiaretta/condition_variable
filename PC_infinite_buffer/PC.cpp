// PC.cpp

#include "PC.h"

void PC::append(const datatype& item)
	{
		std::unique_lock<std::mutex> mlock(mutex_);
		buffer_.push(item);
		mlock.unlock();
		not_empty_.notify_one();
	}

datatype PC::take()
	{
		std::unique_lock<std::mutex> mlock(mutex_);
		while (buffer_.empty())
			not_empty_.wait(mlock);
		datatype w = buffer_.front();
		buffer_.pop();
		return w;
	}