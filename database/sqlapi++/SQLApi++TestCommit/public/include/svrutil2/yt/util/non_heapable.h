#pragma once

#include <stdio.h>

namespace yt
{
	//�̳���������಻��new
	class NonHeapable
	{
		private:
			void * operator new(size_t/* size*/) throw() {
				return NULL;
			}
			void operator delete(void* /*p*/){
			}
	};
}

