#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NAME_MAX 24
#define ADDRESS_MAX 256
//实现一个通讯录； 
//通讯录可以用来存储1000个人的信息，每个人的信息包括： 
//姓名、性别、年龄、电话、住址 
typedef enum Sex{
    MAN,
    WOMAN
}Sex;

typedef struct LinkMan{
   char name[NAME_MAX];//姓名
   Sex sex;            //性别
   size_t age;         //年龄
   size_t phone_number;//电话号码
   char address[ADDRESS_MAX];//住址
}LinkMan;

typedef struct AddressList{
    LinkMan* data;
    size_t size;
    size_t capaity;
}AddressList;

//通讯录初始化
void AddressListInit(AddressList* head);
//提供方法： 
//1. 添加联系人信息 
void AddressListPush(AddressList* head, LinkMan value);
//2. 删除指定联系人信息 
void AddressListPop(AddressList* head);
//3. 查找指定联系人信息 
LinkMan* AddressListFind(AddressList* head, const char* name);
//4. 修改指定联系人信息 
void AddressListRevise(AddressList* head, LinkMan new_value);
//5. 显示所有联系人信息 
void AddressListPrint(AddressList* head);
//6. 清空所有联系人 
void AddressListDestroy(AddressList* head);
//7. 以名字排序所有联系人
void AddressListSortByName(AddressList* head);



















