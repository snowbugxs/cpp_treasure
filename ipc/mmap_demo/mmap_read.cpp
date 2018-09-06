#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

typedef struct Student
{
    int age;
    char name[20];
    char sex;
} Student;

/// 这个进程用于读
int main(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("./a.out file");
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(2);
    }

    Student *p = (Student *)mmap(NULL, sizeof(Student), PROT_READ, MAP_SHARED, fd, 0);
    if (MAP_FAILED == p)
    {
        perror("mmap");
        exit(3);
    }
    close(fd);

    int numCount = 50;
    while (numCount--)
    {
        printf("age = %d, name = %s, sex: %c\n", p->age, p->name, p->sex);
        sleep(1);
    }

    /// 一定要对 mmap 和 munmap 的返回值做检测
    int ret = munmap(p, sizeof(Student));
    if (ret < 0)
    {
        perror("munmap");
        exit(4);
    }

    return 0;
}