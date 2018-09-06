#pragma once

#include <pthread.h>

namespace yt 
{
	//֪ͨ��Ļ���
	struct Notification
	{
		virtual ~Notification() {}
		virtual void notify() = 0;
	};
	//socket֪ͨ��
	class SocketNotification : public Notification
	{
		public:
			inline void SetFD(int fd){
				m_fd = fd;
			}
			inline int GetFD() const{
				return m_fd;
			}
			virtual void notify();
		private:
			int m_fd;
	};
	//�ź�֪ͨ��
	class SignalNotification : public Notification
	{
		public:
			SignalNotification(int sig) : m_sig(sig){}
			virtual void notify();
		private:
			int m_sig;
	};
}

