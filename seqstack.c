#include"seqstack.h"
//初始化
void SeqStackInit(SeqStack* seq)
{
    seq->capacity = 1000;
    seq->data = (SeqStackType*)malloc(seq->capacity*sizeof(SeqStackType));
    seq->size = 0;
}

//清空栈
void SeqStackDestroy(SeqStack* seq)
{
    free(seq->data);
    seq->size = 0;
    seq->capacity = 1000;
}

//如果当前栈已经满了，就要动态扩容
SeqStackType* SeqStackExpand(SeqStack* seq)
{
    if(seq==NULL){
        //非法输入
        return NULL;
    }
    SeqStackType* newseq = (SeqStackType*)malloc(2*(seq->capacity)+1);
    size_t i = 0;
    for(;i<seq->size;i++){
        newseq[i] = seq->data[i];
    }
    seq->capacity = 2*(seq->capacity)+1;
    free(seq->data);
    return newseq;
}
//入栈（尾插）

void SeqStackPush(SeqStack* seq,SeqStackType value)
{
    if(seq==NULL){
        //非法输入
        return;
    }
    if(seq->size>=seq->capacity){
        seq->data = SeqStackExpand(seq);
    }
    seq->data[seq->size] = value;
    seq->size++;
}

//出栈（尾删）
void SeqStackPop(SeqStack* seq)
{
    if(seq==NULL){
        //非法输入
        return;
    }
    if(seq->size==0){
        //空栈
        return;
    }
    seq->size--;
}

//取栈顶元素
int SeqStackFindTop(SeqStack* Seq,SeqStackType* value)
{
    if(Seq==NULL)
    {
        //非法输入
        return 0;
    }
    if(Seq->size==0){
        //空栈
        return 0;
    }
   *value = Seq->data[Seq->size-1]; 
    return 1;
}
/*
void SeqStackPrintChar(SeqStack* seq,const char* msg)
{
    if(seq==NULL){
        //非法输入
        return;
    }
    size_t  i = 0;
    for(;i<seq->size;i++){
        printf("[%c] ",seq->data[i]);
    }
    printf("\n");
    printf("%s\n",msg);
}
*/
/*
void SeqStackAssgin(SeqStack* cur_path, SeqStack* short_path)
{
    SeqStackDestroy(short_path);
    short_path->size = cur_path->size;
    short_path->capacity = cur_path->capacity;
    short_path->data = (SeqStackType*)malloc(short_path->capacity * sizeof(SeqStackType));
    size_t i = 0;
    for(; i<cur_path->size; i++)
    {
        short_path->data[i] = cur_path->data[i];
    }
    return;
}
*/
//通常栈是不允许进行遍历的
//但是如果是进行调试或者测试，这个是例外
//因此在这里的函数虽然进行了遍历，但是仅用于调试
/*
 * void SeqStackDebugPrint(SeqStack* stack, const char* msg)
{
    printf("%s\n",msg);
    size_t i = 0;
    for(;i < stack->size;i++)
    {
        printf("[%d %d]\n",stack->data[i].row,stack->data[i].col);
    }
}
*/
/*
void TestInit()
{
    TESTHEAD;
    SeqStack seq;
    SeqStackInit(&seq);
}

void TestPush()
{
    TESTHEAD;
    SeqStack seq;
    SeqStackInit(&seq);
    SeqStackPush(&seq,'a');
    SeqStackPush(&seq,'b');
    SeqStackPush(&seq,'c');
    SeqStackPush(&seq,'d');
    SeqStackPrintChar(&seq,"入栈四个元素");
}

void TestPop()
{
    TESTHEAD;
    SeqStack seq;
    SeqStackInit(&seq);
    SeqStackPush(&seq,'a');
    SeqStackPush(&seq,'b');
    SeqStackPush(&seq,'c');
    SeqStackPush(&seq,'d');
    SeqStackPrintChar(&seq,"入栈四个元素");
    SeqStackPop(&seq);
    SeqStackPop(&seq);
    SeqStackPrintChar(&seq,"出栈两个元素");
}
void TestGetTop()
{
    TESTHEAD;
    SeqStack seq;
    SeqStackInit(&seq);
    SeqStackPush(&seq,'a');
    SeqStackPush(&seq,'b');
    SeqStackPush(&seq,'c');
    SeqStackPush(&seq,'d');
    SeqStackPrintChar(&seq,"入栈四个元素");
    SeqStackType value;
    int ret = SeqStackFindTop(&seq,&value);
    printf("ret: except: 1 , real: %d \n",ret);
    printf("value: except: d, real: %c \n",value);
}
int main()
{
    TestPop();
    return 0;
}*/
