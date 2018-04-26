#include <stdio.h>
#include <unistd.h>
int main()
{
    daemon(0,0);
    while(1);
}
