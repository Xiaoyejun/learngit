#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b)
{
    return (*(int*)a-*(int*)b);
}
void swap(char *a , char *b, size_t size)
{
    if(a == NULL || b == NULL || size <= 0)
    {
        return;
    }
    char tmp;
//    char *pa = (char*)a;
//    char *pb = (char*)b;
    size_t i = 0;
    for(; i < size ; i++)
    {
//        tmp = *pa;
//        *(pa++) = *pb;
//        *(pb++) = tmp;
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void my_qsort(void* arr,size_t num,size_t size,int (*cmp)(const void *a,const void *b))
{
    if(arr == NULL || num <= 0 || size <= 0 || cmp == NULL)
    {
        return;
    }
    size_t i = 0;
    for(; i < num - 1; i++)
    {
        size_t j = 0;
        for(; j < num - i - 1; j++)
        {              
            if(cmp(arr+j*size,arr + (j+1)*size) > 0)
            {
                swap(arr + j*size,arr + (j+1)*size,size);
            }
        }
    }
}

int main()
{
    int arr1[5] = {2,6,1,3,6};
    my_qsort(arr1,5,sizeof(arr1[0]),cmp);
    int i = 0;
    for(; i<5; i++)
    {
        printf("%d ",arr1[i]);
    }
    printf("\n");
    return 0;
}
