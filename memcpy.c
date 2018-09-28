#include <stdio.h>
#include <string.h>

typedef struct  s_test
{
    int     poulet;
    char    *nugget;
    long    *barbecue;
}               t_test;

int main(void)
{
    t_test test1;
    t_test test2;

    test1.poulet = 666;
    test1.nugget = "666";
    test1.barbecue = (long [3]){6, 6, 6};

    memcpy((void *)&test2, (void *)&test1, sizeof(t_test));
    
    printf("%d\n%s\n", test2.poulet, test2.nugget);

    for (int i = 0; i < 3; i++)
	    printf("%ld", test2.barbecue[i]);

    return (printf("\n"));
}
