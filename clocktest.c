#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start_t, end_t;
    double total_t;
    int i;

    start_t = clock();
    printf("程序启动， start_t = %ld\n", start_t);
    printf("开始循环, start_t = %ld\n", start_t);
    for(i = 0; i < 1000000000; i++){

    }
    end_t = clock();
    printf("循环结束，end_t = %ld\n", end_t);

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("CPU占用的总时间：%f\n",total_t);
    return 0;
}

