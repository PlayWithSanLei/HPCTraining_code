#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
 
#define MAX_SIZE 10000
 
void Merge(int* a, int* b,int start, int middle, int end)
{
    int na1, na2, nb, i;
    na1 = start;
    nb = start;
    na2 = middle + 1;
 
    while ((na1 <= middle) && (na2 <= end)) {
        if (a[na1] <= a[na2]) {
            b[nb++] = a[na1++];
        } else {
            b[nb++] = a[na2++];
        }
    }
 
    if (na1 <= middle) {
        for (i = na1; i <= middle; i++) {
            b[nb++] = a[i];
        }
    }
    if (na2 <= end) {
        for (i = na2; i <= end; i++) {
            b[nb++] = a[i];
        }
    }
 
    for (i = start; i <= end; i++) {
        a[i] = b[i];
    }
}
 
void Merge_Sort(int* a, int* b, int start, int end)
{
    int middle;
    
    if (start < end) {
        middle = (start + end) / 2;
        Merge_Sort(a, b, start, middle);
        Merge_Sort(a, b, middle + 1, end);
        Merge(a, b, start, middle, end);
    }
}
 
int main(int argc,char *argv[])
{
    int arr[MAX_SIZE];
    int comm_sz;
    int my_rank;
    int length = 0;
    int size;
    int* sub;
    int* tmp;
    int* result = NULL;
    int * tmp_for_last;
    int i;
    FILE* fpread;
 
    // 读文件
    for (i = 0; i < MAX_SIZE; i++) {
        arr[i] = -9999;
    }
 
    fpread = fopen(argv[1], "r");
    if (fpread == NULL) {  
	    printf("Read error!");        
	    return 0;  
    }
    for (i = 0; !feof(fpread); i++) {
        fscanf(fpread, "%d ", &arr[i]);
        length++;
    }
 
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    size = length / comm_sz;  // 计算每个进程所需数组的大小
    sub = (int *)malloc(size * sizeof(int));  // 为进程所用数组开辟空间
 
    MPI_Scatter(arr, size, MPI_INT, sub, size, MPI_INT, 0, MPI_COMM_WORLD);  // 将数组元素分发给每个进程
 
    tmp = (int *)malloc(size * sizeof(int));  // 开辟归并排序时需要的临时数组
    Merge_Sort(sub, tmp, 0, size - 1);
 
    if(my_rank == 0) {
        result = (int *)malloc(length * sizeof(int));  // 开辟结果所需的数组空间（与输入数组一样大）
    }
 
    MPI_Gather(sub, size, MPI_INT, result, size, MPI_INT, 0, MPI_COMM_WORLD);  // 将各进程排序的数组收集到0号进程
 
    if (my_rank == 0) {
        tmp_for_last = malloc(length * sizeof(int));
        Merge_Sort(result, tmp_for_last, 0, length - 1);
 
        // 打印结果
        printf("\nThe result is: \n");
        for (i = 0; i < length; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
 
        free(result);
        free(tmp_for_last);
    }
    free(sub);
    free(tmp);
    
    MPI_Finalize();
    return 0;
}

