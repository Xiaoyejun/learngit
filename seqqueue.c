#include "seqqueue.h"


void SeqQueueInit(SeqQueue* seq)
{
    if(seq==NULL)
    {
        //非法输入
        return;
    }
    seq->head = 0;
    seq->tail = 0;
    seq->size = 0;
}

void SeqQueuePush(SeqQueue* seq,SeqQueueType value)
{
    if(seq==NULL)
    {
        //非法输入
        return;
    }
    if(seq->size == SeqQueueMaxSize)
    {
        //队列已满
        return;
    }
    if(seq->tail==SeqQueueMaxSize&&seq->size<SeqQueueMaxSize)
   //此时tail已经到了数组末尾，而size还没有达到最大值，说明
   //head前有空出的位置，所以将tail赋值0，直到size达到最大值，才说明队列已经满了 
    {
        seq->tail = 0;
    }
    seq->data[seq->tail++] = value;
    seq->size++;
}

void SeqQueuePop(SeqQueue* seq)
{
    if(seq==NULL)
    {
        //非法输入
        return;
    }
    if(seq->size == 0)
    {
        //空队列
        return;
    }
    if(seq->head == SeqQueueMaxSize)
    {
        seq->head = 0;
    }
    else
    {
        seq->head++;
    }
    seq->size--;
}

int SeqQueueGetTop(SeqQueue* seq,SeqQueueType* value)
{
    if(seq==NULL)
    {
        //非法输入
        return 0;
    }
    if(seq->size==0)
    {
        //空队列
        return 0;
    }
    *value = seq->data[seq->head];
    return 1;
}

void SeqQueuePrintChar(SeqQueue* seq,const char* msg)
{
    if(seq==NULL)
    {
        //非法输入
        return;
    }
    size_t i = 0;
    for(;i<seq->size;i++)
    {
        if(seq->head+i==SeqQueueMaxSize)
        {
            size_t j = 0;
            for(;j<seq->tail;j++)
            {
                printf("[%c] ",seq->data[j]);
            }
            break;
        }
        printf("[%c] ",seq->data[seq->head+i]);
    }
    printf("\n");
    printf("[%s]\n",msg);
}
/*void Test()
{
    SeqQueue seq;
    SeqQueueInit(&seq);
    SeqQueuePush(&seq,'a');
    SeqQueuePush(&seq,'b');
    SeqQueuePush(&seq,'c');
    SeqQueuePush(&seq,'d');
    SeqQueuePrintChar(&seq,"尝试四个元素入队列");
    SeqQueueType value;
    int ret;
    ret = SeqQueueGetTop(&seq,&value);
    printf("except: 1 ,real: %d\n",ret);
    printf("except: a ,real: %c\n",value);
    SeqQueuePop(&seq);
    ret = SeqQueueGetTop(&seq,&value);
    printf("except: 1 ,real: %d\n",ret);
    printf("except: b ,real: %c\n",value);
    SeqQueuePop(&seq);
    ret = SeqQueueGetTop(&seq,&value);
    printf("except: 1 ,real: %d\n",ret);
    printf("except: c ,real: %c\n",value);
    ret = SeqQueueGetTop(&seq,&value);
    printf("except: 1 ,real: %d\n",ret);
    printf("except: c ,real: %c\n",value);
    SeqQueuePop(&seq);
    ret = SeqQueueGetTop(&seq,&value);
    printf("except: 1 ,real: %d\n",ret);
}*/
