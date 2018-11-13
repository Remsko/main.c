#include <stdio.h>

int		main(void)
{
	int len = 2;

	printf("%d\n", len % 8);
	switch (len % 8)
	{
		case 3:
			goto do3;
		case 2:
			goto do2;
		case 1:
			goto do1;
	}
	do
	{
		do3:
			printf("do3\n");
		do2:
			printf("do2\n");
		do1:
			printf("do1\n");
		len -= 1;
	} while (len != 0);

	return (0);
}
