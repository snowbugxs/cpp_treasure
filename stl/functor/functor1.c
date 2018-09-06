/*
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int compare_ints_function(void*A,void*B)
{
	return*((int*)(A))<*((int*)(B));
}
void sort(void*first_item,size_t item_size,void*last_item,int(*cmpfunc)(void*,void*));
int main(void)
{
	int items[]={4,3,1,2};
	sort((void*)(items),sizeof(int),(void*)(items +3), compare_ints_function);
	return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>

//Callback function 
int compare_ints_function(const void*A,const void*B)
{
    return*((int*)(A)) - *((int*)(B));
}

//Declaration of C sorting function 
//void qsort(void*first_item,size_t item_size,void*last_item,int(*cmpfunc)(void*,void*));

int main(void)
{
    int items[]={4,3,1,2};
    qsort((void*)(items),4,sizeof(int), compare_ints_function);
    int i = 0;
    for( i = 0; i < 4; i++)
    {
        printf("%d\n", items[i]);
    }
    return 0;
}


/*
#include <stdio.h>  
#include <stdlib.h>  

int sort_function( const void *a, const void *b)  
{     
    return *(int*)a-*(int*)b;  
}  
  
int main()  
{  
     
   int list[5] = { 54, 21, 11, 67, 22 };  
   qsort((void *)list, 5, sizeof(list[0]), sort_function); 
   int  x;  
   for (x = 0; x < 5; x++)  
          printf("%i\n", list[x]);  
                    
   return 0;  
}
*/
