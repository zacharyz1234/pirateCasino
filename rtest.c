#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<string.h>
#include<time.h>

int main() //THIS DOES NOT WORK
{
    unsigned int val;

    rand_s(&val);
    
    int num;

    for(int i = 0; i < 100; i++)
    {
        num = (val % 36) + 1;
        printf("%d ", num);

        if(i >= 90)
        {
            sleep(1);
        }
        system("cls");
    }
}