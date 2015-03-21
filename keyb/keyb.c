#include "../inc/key.h"
#include <stdio.h>

int main(void)
{
    int key;
    while(1){
        key = getch();
        printf("%d\n", key);
    }
    return 0;
}
