/**
 * Merge_Sort: 归并排序的递归实现
 * 注：算法导论上给出的合并排序算法
 * 递归过程是将待排序集合一分为二，
 * 直至排序集合就剩下一个元素为止，然后不断的合并两个排好序的数组
 * T(n) = O(nlgn)
**/
#include <stdio.h>
#define LEN 8

// 合并
void merge(int a[], int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int left[n1], right[n2];
    int i, j, k;

    for (i = 0; i < n1; i++) /* left holds a[start..mid] */
        left[i] = a[start+i];
    for (j = 0; j < n2; j++) /* right holds a[mid+1..end] */
        right[j] = a[mid+1+j];

    i = j = 0;
    k = start;
    while (i < n1 && j < n2)
        if (left[i] < right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];

    while (i < n1) /* left[] is not exhausted */
        a[k++] = left[i++];
    while (j < n2) /* right[] is not exhausted */
        a[k++] = right[j++];
}

// merge_sort()：先排序，再合并
void merge_sort(int a[], int start, int end)
{
    int mid;
    if (start < end)
    {
        mid = (start + end) / 2;
        printf("sort (%d-%d, %d-%d) %d %d %d %d %d %d %d %d\n",
               start, mid, mid+1, end,
               a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);

        // 分解 + 解决：Divide + Conquer
        merge_sort(a, start, mid); // 递归划分原数组左半边array[start...mid]
        merge_sort(a, mid+1, end); // 递归划分array[mid+1...end]
        // 合并：Combine
        merge(a, start, mid, end); // 合并

        printf("merge (%d-%d, %d-%d) to %d %d %d %d %d %d %d %d\n",
               start, mid, mid+1, end,
               a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
    }
}

int main(void)
{
    int a[LEN] = { 5, 2, 4, 7, 1, 3, 2, 6 };
    merge_sort(a, 0, LEN-1);

    return 0;
}