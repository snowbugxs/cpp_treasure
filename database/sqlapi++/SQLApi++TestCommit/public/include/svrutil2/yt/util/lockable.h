#pragma once

namespace yt
{
/*
���Ļ���
*/
	class Lockable
	{
		public:
			virtual ~Lockable(){}
			virtual int Release() = 0;
	};
}
