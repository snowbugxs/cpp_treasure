#pragma once

namespace yt
{
	/*! \brief ����Ҫ�󲻿ɸ�ֵ(��������)���඼���Լ̳��ڴ�
	 *  \note ժ��IceUtil::::noncopyable
	 */
	class NonCopyable
	{

		protected:
			NonCopyable() {}
			~NonCopyable() {}

		private:
			NonCopyable(const NonCopyable &);
			const NonCopyable & operator=(const NonCopyable &);
	};
}

