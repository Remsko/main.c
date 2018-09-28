#include <string.h>
#include <stdio.h>

#define FLAG_l (1 << 0)
#define FLAG_R (1 << 1)
#define FLAG_a (1 << 2)

int	main(int ac, char **av)
{
	const char	*existing_flags = "lRa";
	char		*tmp;
	unsigned char	flags;
	int		i;

	--ac;
	flags = 0;
	while (ac > 1)
	{
		i = 0;
		if (av[ac][i] == '-')
		{
			++i;
			while (av[ac][i] != '\0')
			{
				if ((tmp = strchr(existing_flags, av[ac][i])) != NULL)
				{
					flags |= 1 << (tmp - existing_flags);
				}
				++i;
			}
		}
		--ac;
	}
	printf("option l = %d\n", (flags & FLAG_l) ? 1 : 0);
	printf("option R = %d\n", (flags & FLAG_R) ? 1 : 0);
	printf("option a = %d\n", (flags & FLAG_a) ? 1 : 0);
}
