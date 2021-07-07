#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Print_list(int a[]) {
    for(int i = 0; i < 4; i++) {
        printf("%d ", a[i]);
    }
}
void Count_sort(int a[], int n) {
    int i, j, count;
    int *temp = malloc(n*sizeof(int));
    for(i = 0;i < n;i++) {
        count = 0;
        for(j = 0;j < n;j++) {
            if(a[j] < a[i])
                count++;
            else if(a[j] == a[i]&&j<i)
                count++;
            temp[count] = a[i];
        }  
    }
   memcpy(a, temp, n*sizeof(int));
   free(temp);
}

int main() {
    int n = 4;
    int a[4] = {10,9,8,7};

    Count_sort(a, n);
    Print_list(a);
    printf("\n");
    return 0;
}
