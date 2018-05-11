#include <stdio.h>
////编写一个函数实现n^k,递归实现
////不算k等于负数的情况
//
//int numk(int n,int k)
//{
//    if(n == 0)
//    {
//        return 0;
//    }else
//    {
//        if(k > 0)
//        {
//            return n*numk(n,k-1);
//        }else
//        {
//            return 1;
//        }
//    }
//    
//}
//
//int main()
//{
//    printf("n = ? k = ?\n");
//    int num = 0;
//    int k = 0;
//    scanf("%d%d",&num,&k);
//    printf("n ^ k = %d\n",numk(num,k));
//    return 0;
//}


// 写一个递归函数DigitSum(n)，输入一个非负整数，返回组成它的数字之和
// 例如，调用DigitSum(1729)，则应该返回1+7+2+9，它的和是19

//int Digitsum(int n)
//{
//    int sum = 0;
//    if(n <= 0)
//    {
//        return 0;
//    }else
//    {
//        sum =  n%10+Digitsum(n/10);
//        return sum;
//    }
//}
//
//
//int main()
//{
//    printf("n = ?\n");
//    int n = 0;
//    scanf("%d",&n);
//    printf("result = %d\n",Digitsum(n));
//    return 0;
//}

// 编写一个函数reverse_string(char * string)（递归实现） 
// 实现：将参数字符串中的字符反向排列。 
// 要求：不能使用C函数库中的字符串操作函数。 


//void reverse_string(char *string)
//{
//     if(string==NULL)
//     {
//         printf("error");
//         return;
//     }
//     if(*string){
//         string++;
//         reverse_string(string);
//         printf("%c",*(string-1));
//     }
//}
//
//int main()
//{
//    char* str = "abcde";
//    reverse_string(str);
//     printf("\n");
//    return 0;
//}

//递归和非递归分别实现strlen
//

//int count = 0;
//int my_strlenre(char *str)//递归版
//{
//    if(str == NULL)
//    {
//        printf("error\n");
//    }
//    if(*str)
//    {
//        count++;
//        str++;
//        my_strlenre(str);
//    }
//    return count;
//}
//
//int my_strlen(char *str)//非递归版
//{
//    if(str == NULL)
//    {
//        printf("error\n");
//    }
//    while(*str)
//    {
//        count++;
//        str++;
//    }
//    return count;
//}
//int main()
//{
//    char *str = "abcde";
//    printf("%d\n",my_strlen(str));
//    return 0;
//}


//递归和非递归分别实现求n的阶乘

//int FactorialRe(int n)//递归版
//{
//    if( n <= 1 )
//    {
//        return 1;
//    }
//    return n*FactorialRe(n-1);
//}
//
//int Factorial(int n)//非递归版
//{
//    int sum = 1;
//    while(n > 1)
//    {
//        sum = sum * n;
//        n = n - 1;
//    }
//    return sum;
//}
//int main()
//{
//    int n = 0;
//    printf("n = ?\n");
//    scanf("%d",&n);
//    if(n <= 0)
//    {
//        printf("error\n");
//        return 0;
//    }
//    printf("n  Factorial =  %d\n",Factorial(n));
//    return 0;
//}

void ReverseNumPrint(int n)
{
    if(n == 0)
    return;
    ReverseNumPrint(n/10);
    printf("%d ",n%10);
}

int main()
{
    int n = 0;
    printf("n = ?\n");
    scanf("%d",&n);
    ReverseNumPrint(n);
    printf("\n");
    return 0;
}
