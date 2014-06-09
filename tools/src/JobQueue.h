// ***********************************************************************
// Filename         : JobQueue.h
// Author           : LIZHENG
// Created          : 2014-06-08
// Description      : 同步队列，可工作于多线程环境下，可用于线程之间数据存取
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-08
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef JobQUEUE_FILE_H
#define JobQUEUE_FILE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename Job, typename Queue = std::queue<Job> >
class JobQueue
{
public:
	typedef Job                                 JobType;
	typedef Queue	                            QueueType;
	typedef std::mutex							MutexType;
	typedef std::lock_guard<MutexType>		    LockGuard;
	typedef std::condition_variable_any		    ConditionType;

public:
	JobQueue() : stop_flag_(false) {}
	virtual ~JobQueue(){ Stop(); }

public:
	virtual void Push(const JobType& job)
	{
		LockGuard lock(mutex_);
		queue_.push(job);
		has_job_.notify_one();
	}

	virtual bool Pop(JobType& job)
	{
		LockGuard lock(mutex_);
		while (queue_.empty() && !stop_flag_)
		{
			has_job_.wait(mutex_);
		}
		if (stop_flag_)
		{
			return false;
		}

		job = queue_.front();
		queue_.pop();
		return true;
	}

	virtual void Stop()
	{
		stop_flag_ = true;
		has_job_.notify_all();
	}

private:
	JobQueue(const JobQueue&);
	JobQueue& operator=(const JobQueue&);

protected:
	bool             stop_flag_;
	MutexType        mutex_;
	ConditionType    has_job_;
	QueueType        queue_;
};


#endif /* JobQUEUE_FILE_H */