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
#ifndef ZL_JOBQUEUE_FILE_H
#define ZL_JOBQUEUE_FILE_H

#include <queue>
#include <mutex>
#include <condition_variable>

namespace ZL
{ 

struct tagFIFO {};  //先进先出
struct tagFILO {};  //后进先出
struct tagPRIO {};  //按优先级出

template <typename Job, typename Queue = std::queue<Job>, typename Order = tagFIFO >
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

		return PopOne(job, Order());
	}

	virtual bool TryPop(JobType& job)
	{
		LockGuard lock(mutex_);

		if (queue_.empty() && !stop_flag_)
			return false;

		return PopOne(job, Order());
	}

	virtual void Stop()
	{
		stop_flag_ = true;
		has_job_.notify_all();
	}
	template <typename T>
	bool PopOne(JobType& job, T tag)
	{
		job = queue_.front();
		queue_.pop();
		return true;
	}
	template <>
	bool PopOne(JobType& job, tagFIFO tag)
	{
		job = queue_.front();
		queue_.pop();
		return true;
	}
	template <>
	bool PopOne(JobType& job, tagFILO tag)
	{
		job = queue_.back();
		queue_.pop();
		return true;
	}
	template <>
	bool PopOne(JobType& job, tagPRIO tag)
	{
		job = queue_.top();
		queue_.pop();
		return true;
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

} /* namespace ZL */

#endif /* ZL_JOBQUEUE_FILE_H */