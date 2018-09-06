#include "common.h"

int main()
{
    int shmid = GetShm(4096);
    sleep(3);

    /// 新的进程挂接到那块共享内存空间, 可以直接看到内存中的东西
    char *buf = (char *)shmat(shmid, (void*)0, 0);

    int numCount = 60;
    while (numCount--)
    {
        printf("%s\n", buf);
        sleep(1);
    }

    shmdt(buf);
    return 0;
}