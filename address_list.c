#include "address_list.h"
#include <assert.h>

//通讯录初始化
void AddressListInit(AddressList* head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    head->capaity = 1000;
    head->data = (LinkMan*)malloc(head->capaity*sizeof(LinkMan));
    assert(head != NULL);
    head->size = 0;
}
//提供方法：
//如果当前通讯录满了，就要动态扩容
LinkMan* AddressListExpand(AddressList* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    LinkMan* new_head = (LinkMan*)malloc(2*head->capaity*sizeof(LinkMan)+sizeof(LinkMan));
    size_t i = 0;
    for(; i < head->size; i++)
    {
        new_head[i] = head->data[i];
    }
    free(head->data);
    return new_head;
}
//1. 添加联系人信息 
void AddressListPush(AddressList* head, LinkMan value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->size == head->capaity)
    {
        //通讯录满了
        head->data = AddressListExpand(head);
        head->capaity = 2*head->capaity+1;
    }
    head->data[head->size++] = value;
}
//2. 删除指定联系人信息 
void AddressListPop(AddressList* head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->size == 0)
    {
        //空的通讯录
        return;
    }
    head->size--;
}
//3. 查找指定联系人信息 
LinkMan* AddressListFind(AddressList* head, const char* name)
{
    if(head == NULL || name == NULL)
    {
        return NULL;
    }
    size_t  i = 0;
    for(; i<head->size; i++)
    {
        if(strcmp(head->data[i].name,name) == 0)
        {
            return &head->data[i];
        }
    }
    return NULL;
}
//4. 修改指定联系人信息 
void AddressListRevise(AddressList* head, LinkMan new_value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    size_t i = 0;
    for(; i<head->size; i++)
    {
        if(strcmp(head->data[i].name,new_value.name) == 0)
        {
            head->data[i] = new_value;
            return;
        }
    }
    return;
}
//5. 显示所有联系人信息 
void AddressListPrint(AddressList* head)
{
    if(head == NULL)
    {
        return;
    }
    size_t i = 0;
    for(; i < head->size ;i++)
    {
        LinkMan person = head->data[i];
        printf("[姓名]:%s \n",person.name);
        printf("[性别]:%s \n",person.sex == MAN?"MAN":"WOMAN");
        printf("[年龄]:%lu \n",person.age);
        printf("[电话]:%lu \n",person.phone_number);
        printf("[住址]:%s \n",person.address);
        printf("\n");
    }
}
//6. 清空所有联系人 
void AddressListDestroy(AddressList* head)
{
    if(head == NULL)
    {
        return;
    }
    free(head->data);
    head->size = 0;
    head->capaity = 0;
}
//7. 以名字排序所有联系人
void AddressListSortByName(AddressList* head)
{
    if(head == NULL)
    {
        return;
    }
    size_t i = 0;
    LinkMan tmp;
    for(; i < head->size; i++)
    {
        size_t j = 0;
        for(; j < head->size - i - 1; j++)
        {
            if(strcmp(head->data[j].name,head->data[j+1].name) > 0)
            {
                tmp = head->data[j];
                head->data[j] = head->data[j+1];
                head->data[j+1] = tmp;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////
//////////TEST      PART////////////////////////////////////////
////////////////////////////////////////////////////////////////
#if 0
void Test()
{
    AddressList list;
    AddressListInit(&list);
    LinkMan man1,man2,man3;
    //man1
    strcpy(man1.name,"张三");
    man1.sex = MAN;
    man1.age = 18;
    man1.phone_number = 10086;
    strcpy(man1.address,"陕西省西安市");
    //man2
    strcpy(man2.name,"李四");
    man2.sex = MAN;
    man2.age = 19;
    man2.phone_number = 10088;
    strcpy(man2.address,"北京市朝阳区");
    //man3
    strcpy(man3.name,"翠花");
    man3.sex = WOMAN;
    man3.age = 18;
    man3.phone_number = 10087;
    strcpy(man3.address,"辽宁省沈阳市");

    AddressListPush(&list,man1);
    AddressListPush(&list,man2);
    AddressListPush(&list,man3);
    AddressListPrint(&list);

    AddressListPop(&list);
    AddressListPrint(&list);

    LinkMan* cur = AddressListFind(&list,"李四");
    printf("[姓名]:%s \n",cur->name);

    LinkMan man4;
    strcpy(man4.name,"张三");
    man4.age = 20;
    man4.phone_number = 10081;
    strcpy(man4.address,"黑龙江省哈尔滨市");
    man4.sex = WOMAN;
    AddressListRevise(&list,man4);
    AddressListPrint(&list);
    AddressListDestroy(&list);
}

void _AddressListPush()
{
    LinkMan man;
}

#endif
int main()
{
//    Test();
    return 0;
}
