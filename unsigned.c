#include <stdio.h>

int	main(void)
{
	unsigned int u_intmax;

	u_intmax = ~0u;

	printf("max = %u\n", u_intmax);
	printf("min = %u\n", ++u_intmax);

	return (0);
}
