#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 1024

char* strCpy(char* dest, const char* src)
{
    if(dest == NULL || src == NULL)
    {
        return NULL;
    }
    char* cur = dest;
    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return cur;
}

char* strCat(char* dest,char* src)
{
    if(dest == NULL || src == NULL)
    {
        return NULL;
    }
    char* cur = dest;
    while(*dest != '\0')
    {
        dest++;
    }
    while(*src != '\0')
    {
        *dest = *src;
        src++;
        dest++;
    }
    *dest = '\0';
    return cur;
}

char* strStr(char* dest, char* src)
{
    if(dest == NULL || src == NULL)
    {
        return NULL;
    }
    if(!*src)
        return dest;
    while(*dest)
    {
        if(*dest == *src && strncmp(dest,src,strlen(src)) == 0)
        {
            return dest;
        }
        dest++;
    }
    return NULL;
}

int strnCmp(char *str1, char* str2, size_t count)
{
    assert(str1 != NULL || str2 != NULL);
    int num = 0;
    while(*str1 != '\0' && *str2 != '\0' && count != 0)
    {
        num = *str1 - *str2;
        count--;
    }
    return num;
}

void* memCpy(void *dest, const void* src , int count)
{
    if(dest == NULL || src == NULL || count <= 0)
    {
        return NULL;
    }
    char *to = (char*)dest;
    char *from = (char*)src;
    while(count--)
    {
        *(to++) = *(from++);
    }
    return dest;
}

void* memMove(void *dest, const void* src , int count)
{
    if(dest == NULL || src == NULL || count <= 0)
    {
        return NULL;
    }
    char *to = (char*)dest;
    char *from = (char*)src;
    if(to > from + count || from < to){
        while(count--)
        {
            *(to++) = *(from++);
        }
    }else
    {
        to = to + count - 1;
        from = from + count - 1;
        while(count--)
        {
            *(to--) = *(from--);
        }
    }
    return dest;
}
char* strnCpy(char* dest,const char* src,int size)
{
    if(dest == NULL || src == NULL || size <= 0)
    {
        return dest;
    }
    char* cur = dest;
    size_t len_dest = sizeof(dest);
    if(size > (int)len_dest)
    {
        return dest;
    }
    size_t len_src = strlen(src);
    while(size--)
    {
        if(len_src <= 0)
        {
            *(dest++) = '\0';
            continue;
        }
        len_src--;
        *(dest++) = *(src++);
    }
    *dest = '\0';
    return cur;
}

char* strnCat(char* dest, char* src, int size)
{
    if(dest == NULL || src == NULL || size <= 0)
    {
        return dest;
    }
    size_t len_dest = strlen(dest);
    size_t len_src = strlen(src);
    char* cur = dest + len_dest;
    while(size--)
    {
        if(len_src == 0)
        {
            *cur = '\0';
            return dest;
        }
        *(cur++) = *(src++);
        len_src--;
    }
    *cur = '\0';
    return dest;
}

int main()
{
    char arr[MAX] = "abcde";
    char *src = "abcdef";
    strnCat(arr,src,8);
    printf("%s \n",arr);
    return 0;
}
