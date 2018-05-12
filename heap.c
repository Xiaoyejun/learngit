
#include "heap.h"

#include <stdio.h>
#include <string.h>
int Greater(HeapType a, HeapType b)
{
    return a > b?1:0;
}

int Less(HeapType a, HeapType b)
{
    return a < b?1:0;
}

//初始化堆
void HeapInit(Heap* heap,Compare cmp)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    heap->size = 0;
    heap->com = cmp;
}
void Swap(HeapType *a, HeapType *b)
{
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
}

//上浮函数
void AdjustUp(Heap* heap, size_t child)
{
    if(heap == NULL)
    {
        return;
    }
    if(child == 0)
    {
        return;
    }
    size_t parents = (child - 1)/2;
    if(!heap->com(heap->data[parents],heap->data[child]))
    {
        Swap(&heap->data[parents],&heap->data[child]);
        AdjustUp(heap, parents);
    }else
    {
        return;
    }
}


//插入元素
void HeapInsert(Heap* heap, HeapType value)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    if(heap->size >= HeapMaxSize)
    {
        //堆满了
        return;
    }
    heap->data[heap->size++] = value;
    size_t child = heap->size - 1;
    AdjustUp(heap, child);
}
//取堆顶元素
int HeapRoot(Heap* heap, HeapType* value)
{
    if(heap == NULL || value == NULL)
    {
        return 0;
    }
    if(heap->size <= 0)
    {
        return 0;
    }
    *value = heap->data[0];
    return 1;
}

HeapType Cmp(Heap* heap,HeapType a, HeapType b)
{
    return heap->com(a,b) ? a : b;
}

void AdjustDown(Heap* heap, size_t parents, size_t size)
{
    if(heap == NULL || parents >= size - 1 )
    {
        return;
    }
    size_t child = parents*2 + 1; 
    while(child > 0 && child < size)
    {
        if(child + 1 < size)
        {
            if(!heap->com(heap->data[child],heap->data[child+1]))
            {
                child += 1;
            }
        }
        if(!heap->com(heap->data[parents],heap->data[child]))
        {
            Swap(&heap->data[parents],&heap->data[child]);
            parents = child;
            child = parents*2 + 1;
        }else{
            break;
        }
    }
    return;
}

//删除堆顶元素
void HeapErase(Heap* heap)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    if(heap->size <= 0)
    {
        //空堆
        return;
    }
    Swap(&heap->data[heap->size-1], &heap->data[0]);
    heap->size--;
    AdjustDown(heap,0,heap->size);
    return;
}

//判断堆是否为空
int HeapEmpty(Heap* heap)
{
    if(heap == NULL || heap->size == 0)
    {
        return 0;
    }
    return 1;
}
//求堆中元素个数
size_t HeapSize(Heap* heap)
{
    if(heap == NULL || heap->size == 0)
    {
        return 0;
    }
    return heap->size;
}
//创建堆
void HeapCreate(HeapType array[], Heap* heap,size_t size)
{
    if(heap == NULL || size <= 0)
    {
        return;
    }
    size_t index = 0;
    while(size--)
    {
        HeapInsert(heap,array[index]);
        index++;
    }
}

//堆排序
void HeapSort(HeapType array[], Heap* heap, size_t size)
{
    if(heap == NULL || size <= 0)
    {
        return;
    }
    size_t num = size;
    HeapCreate(array,heap,size);
    while(size--)
    {
        HeapErase(heap);
    }
    memcpy(array,heap->data,num*sizeof(HeapType));
}

//销毁堆
void HeapDestroy(Heap* heap)
{
    if(heap == NULL)
    {
        return;
    }
    heap->size = 0;
}

//////////////////////////////////////
////////TEST PART///////////////////
//////////////////////////////////////

void HeapPrint(Heap* heap, const char* msg)
{
    if(heap == NULL)
    {
        return;
    }
    printf("%s ",msg);
    size_t i = 0;
    for(; i<heap->size;i++)
    {
        printf("[%c|%lu] ",heap->data[i], i);
    }
    printf("\n");
}

void TestInit()
{
    TESTHEAD;
    Heap heap;
    HeapInit(&heap,Less);
    printf("except %p ,actural %p\n",Less,heap.com);
}


void TestInsert()
{
    TESTHEAD;
    Heap heap;
    HeapInit(&heap,Less);
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'g');
    HeapInsert(&heap,'d');
    HeapPrint(&heap,"插入六个元素");
    printf("\n");
}
void TestHeapRoot()
{
    TESTHEAD;
    Heap heap;
    HeapInit(&heap,Less);
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapType value;
    int ret = HeapRoot(&heap, &value);
    printf("root except a ,actual %c \n",value);
    printf("ret except 1, actual %d \n",ret);
}
void TestErase()
{
    TESTHEAD;
    Heap heap;
    HeapInit(&heap,Less);
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'h');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'g');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapErase(&heap);
    HeapPrint(&heap,"删除一个堆顶元素");
    HeapErase(&heap);
    HeapPrint(&heap,"删除一个堆顶元素");
    HeapErase(&heap);
    HeapPrint(&heap,"删除一个堆顶元素");
}

void TestHeapCreate()
{
    TESTHEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapType array[] = {'a','d','g','c','b','e','f'};
    HeapCreate(array,&heap,sizeof(array)/sizeof(array[0]));
    HeapPrint(&heap,"创建了一个堆");
}
//升序排序
void TestHeapSort()
{
    TESTHEAD;
    Heap heap;
    HeapInit(&heap, Greater);
    HeapType array[] = {'a','d','g','c','b','e','f'};
    size_t i = 0;
    size_t num = sizeof(array)/sizeof(array[0]);
    printf("排序前: ");
    for(; i < num; i++)
    {
        printf("%c ",array[i]);
    }
    printf("\n");
    HeapSort(array,&heap,num);
    printf("排序后: ");
    for(i = 0; i < num;i++)
    {
        printf("%c ",array[i]);
    }
    printf("\n");
}
int main()
{
    TestInit();
    TestInsert();
    TestHeapRoot();
    TestErase();
    TestHeapCreate();
    TestHeapSort();
    return 0;
}
