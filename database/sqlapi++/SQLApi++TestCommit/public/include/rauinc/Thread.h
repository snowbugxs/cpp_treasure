// Thread.h: interface for the CThread class .
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_THREAD_H__78AB7118_0B3F_4314_A272_B539E6E11EA6__INCLUDED_)
#define AFX_THREAD_H__78AB7118_0B3F_4314_A272_B539E6E11EA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <windows.h>

typedef HANDLE THREAD_HANDLE ;
#else
#include <pthread.h>
typedef pthread_t THREAD_HANDLE ;
#endif



/**������һ���̶߳���
*/

class CThread  
{
public:
	/**���캯��
	*/

	CThread();
	
	/**��������
	*/

	virtual ~CThread();
	
	/**����һ���߳�
	* @return true:�����ɹ� false:����ʧ��
	*/

	virtual bool Create();
	
	/**�߳̿�ʼ���У����麯�����������̳�ʵ��
	*/

	virtual void Run()=0;
	
	/**�麯�����������һЩʵ��������
	* @return true:�����ɹ� false:����ʧ��
	*/

	virtual bool InitInstance();
	
	/**�麯�����������ʵ��
	*/

	virtual void ExitInstance();
	
	/**��ñ��̶߳���洢���߳̾��
	* @return ���̶߳���洢���߳̾���߳̾��
	*/

	inline THREAD_HANDLE GetHandle();


	/**��õ�ǰ�̵߳ľ������
	* @return ��ǰ�̵߳ľ��
	*/

	static THREAD_HANDLE GetCurrentHandle();

	void Join();
private:

	 THREAD_HANDLE m_hThread;	/**< �߳̾�� */
public:
#ifdef WIN32

	 DWORD m_dwThreadId;
#endif
};


inline THREAD_HANDLE CThread::GetHandle()
{
	return m_hThread;
}

#endif // !defined(AFX_THREAD_H__78AB7118_0B3F_4314_A272_B539E6E11EA6__INCLUDED_)
