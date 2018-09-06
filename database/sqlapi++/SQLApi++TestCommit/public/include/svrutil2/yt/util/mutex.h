#pragma once

#include <pthread.h>
#include <sys/sem.h>
#include "lockable.h"

namespace yt
{
	class Mutex : public Lockable
	{
		public:
			virtual int Acquire(bool block = true) = 0;
	};
	//����
	class NullMutex : public Mutex
	{
		public:
			virtual int Acquire(bool /*block*/ = true){ return 0; }
			virtual int Release() { return 0; }
		public:
			static NullMutex * Instance();
	};
	//�߳���
	class ThreadMutex : public Mutex
	{
		public:
			ThreadMutex();
			virtual ~ThreadMutex();
			virtual int Acquire(bool block = true);
			virtual int Release();
		private:
			pthread_mutex_t mutex_;
	};
	//����û�õ�
	class SemMutex : public Mutex
	{
		public:
			SemMutex(key_t key, int oflag = 0644);
			virtual int Acquire(bool block = true);
			virtual int Release();

		private:
			int semid_;
	};
}

