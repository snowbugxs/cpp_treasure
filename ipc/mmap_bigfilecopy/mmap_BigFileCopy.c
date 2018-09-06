#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    ///1. 打开进程数
    int n;
    if (argc < 3 || argc > 4)
    {
        printf("Enter like this : ./a.out file_src file_dst [proc_number]\n");
        exit(1);
    }
    else if (argc == 3) //用户未指定，默认创建5个进程。
        n = 5;
    else
        n = atoi(argv[3]);

    ///2. 打开源文件
    int fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0)
    {
        perror("open");
        exit(2);
    }

    ///3. 打开目标文件，不存在就创建，存在则截断为0的大小。
    int fd_dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd_dst < 0)
    {
        perror("open");
        exit(3);
    }

    ///4. 获取源文件大小。
    struct stat sbuf;
    int ret = fstat(fd_src, &sbuf); //fd_src所指向的文件信息保存到结构体sbuf中。
    if (ret < 0)
    {
        perror("fstat");
        exit(4);
    }
    int flen = sbuf.st_size; //源文件大小。
    if (flen < n)            //文件长度小于进程个数。
    {
        n = flen;
    }

    ///5. 根据文件大小拓展目标文件。
    ret = ftruncate(fd_dst, flen); //将参数fd指定的文件大小改为参数length指定的大小
    if (ret < 0)
    {
        perror("ftruncate");
        exit(5);
    }
    ///6. 为源文件创建映射。
    // void *mmap(void *addr, size_t length, int prot, int flags,  int fd, off_t offset);
    //addr == NULL,表示内核选择一个合适的地址创建一个length大小的共享内存，
    char *mp_src = (char *)mmap(NULL, flen, PROT_READ, MAP_SHARED, fd_src, 0); //0，表示将fd_src所指向的文件从起始映射到共享内存中，共享内存的权限为只读，进程间共享。
    if (mp_src == MAP_FAILED)                                                  //mmap一定要检查返回值。
    {
        perror("mmap");
        exit(6);
    }
    close(fd_src);

    ///7. 为目标文件创建映射。
    char *mp_dst = (char *)mmap(NULL, flen, PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);
    if (mp_dst == MAP_FAILED) //mmap一定要检查返回值。
    {
        perror("mmap");
        exit(7);
    }
    close(fd_dst);

    ///8. 求出每个进程拷贝的字节数。
    int bs = flen / n;
    //求出均分后余下的字节数，让最后一个子进程处理。
    int mod = flen % bs;

    char *temp_src = mp_src;
    char *temp_dst = mp_dst;

    ///9. 创建n个子进程。
    int i;
    pid_t pid;
    for (i = 0; i < n; ++i)
    {
        printf("create %dth proc\n", i);
        if ((pid = fork()) == 0)
            break;
    }
    if (n == i) //父进程。
    {
        int j = 0;
        for (j = 0; j < n; ++j)
            wait(NULL);
    }
    ///10. 子进程拷贝，最后一个子进程，它多处理均分后剩下的字节数。
    else if (i == (n - 1))
    {
        printf("i = %d\n", i);
        memcpy(temp_dst + i * bs, temp_src + i * bs, bs + mod);
    }
    ///11. 第一个子进程拷贝开头, 应该可以和后面合并
//    else if (i == 0)
//    {
//        printf("i = %d\n", i);
//        memcpy(temp_dst, temp_src, bs);
//    }
    else
    {
        printf("i = %d\n", i);
        memcpy(temp_dst + i * bs, temp_src + i * bs, bs);
    }

    ///11. 释放映射区。

    munmap(mp_src, flen);
    munmap(mp_dst, flen);

    return 0;
}
