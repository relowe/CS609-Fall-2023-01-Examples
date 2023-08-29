#include <stdio.h>

int main()
{
    int x=0;
    const char *msg = "hello, world\n";

    printf("%d\n", x = x+1);
    printf("%d\n", x+=1);
    printf("%d\n", ++x);
    printf("%d\n", x++);

    printf("%d\n", x);

    x = 0;
    while(msg[x]) {
        putchar(msg[x++]);
    }
}