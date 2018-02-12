#include <stdio.h>

int main()
{
	int x=12;
	int y=10;
    int t;

    y = x+2;
    t = y;
    x = t;

	printf("x = %d, t = %d, y = %d \n", x,t, y);

    return 0;
}
