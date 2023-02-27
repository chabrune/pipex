#include "pipex.h"

// int main(void)
// {
//     int fd[2];
//     if(pipe(fd) == -1)
//     {
//         printf("Erreur");
//         return(1);
//     }
//     int id = fork();
//     if(id == 0)
//     {
//         close(fd[0]);
//         int x;
//         ft_printf("Input a number : ");
//         scanf("%d", &x);
//         if (write(fd[1], &x, sizeof(int)) == -1)
//             return(2);
//         close(fd[1]);
//     }
//     else
//     {
//         close(fd[1]);
//         int y;
//         if (read(fd[0], &y, sizeof(int)) == -1)
//             return(3);
//         close(fd[0]);
//         ft_printf("Got from child process %d\n", y);
//         wait(NULL);
//     }
//     return(0);
// }

int main(void)
{
    int arr[] = {42, 21, 0, 4, 2, 4};
    int fd1[2], fd2[2];
    int start, end;
    int arrSize = sizeof(arr) / sizeof(int);
    int child_a, child_b;

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
        return 1;
    child_a = fork();
    if (child_a == -1)
        return 2;
    if (child_a == 0)
    {
        start = 0;
        end = arrSize / 2;
    }
    else
    {
        child_b = fork();
        if(child_b == -1)
            return 3;
    }
    if(child_b == 0)
    {
        start = arrSize / 2;
        end = arrSize;
    }
    int sum = 0;
    int i = start;
    while(i < end)
    {
        sum += arr[i];
        i++;
    }

    if (child_b == 0 || child_a == 0)
        printf("Sum of each part of arr : %d\n", sum);
    //  write the sum from children and read from father
    if(child_a == 0)
    {
        close(fd1[0]);
        if(write(fd1[1], &sum, sizeof(int)) == -1)
            return(3);
        close(fd1[1]);
    }
    else if(child_b == 0)
    {
        close(fd2[0]);
        if(write(fd2[1], &sum, sizeof(int)) == -1)
            return(4);
        close(fd2[1]);
    }
    else
    {
        int sum1, sum2;
        close(fd1[1]);
        close(fd2[1]);
        if(read(fd1[0], &sum1, sizeof(int)) == -1)
            return(5);
        if(read(fd2[0], &sum2, sizeof(int)) == -1)
            return(5);
        printf("Total of sum is : %d\n", sum1 + sum2);
        close(fd1[0]);
        close(fd1[0]);
    }
    while(wait(NULL) != -1 || errno != ECHILD)
        ft_printf("Waited for a child to finish\n");
    return(0);
}
