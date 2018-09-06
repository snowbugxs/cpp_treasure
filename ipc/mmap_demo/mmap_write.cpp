#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

typedef struct Student
{
    int age;
    char name[20];
    char sex;
} Student;

/// 此进程用于创建映射区进行写
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("./a.out file");
        exit(1);
    }

    Student student = {10, "ageofempires", 'm'};

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(2);
    }
    /// 拓展文件大小
    ftruncate(fd, sizeof(Student));

    /// 创建一个结构体大小的共享映射区. 共享映射区可以当做数组区看待
    Student *p = (Student *)mmap(NULL, sizeof(Student), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    /// 一定要对 mmap 和 munmap 的返回值做检测
    if (MAP_FAILED == p)
    {
        perror("mmap");
        exit(3);
    }

    /// 可以关闭文件描述符了
    close(fd);

    int numCount = 50;
    while (numCount--)
    {
        memcpy(p, &student, sizeof(Student));
        student.age++;
        sleep(1);
    }

    /// 一定要对 mmap 和 munmap 的返回值做检测
    int ret = munmap(p, sizeof(student));
    if (ret < 0)
    {
        perror("munmap");
        exit(4);
    }

    return 0;
}
