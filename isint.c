#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		tmp;

	len = (n <= 0);
	tmp = n;
	while (++len && tmp)
		tmp /= 10;
	if (!(str = (char*)malloc(sizeof(*str) * (len))))
		return (NULL);
	str[--len] = '\0';
	tmp = (n < 0) ? -1 : 1;
	while (len)
	{
		str[--len] = (n % 10) * tmp + '0';
		n /= 10;
	}
	tmp < 0 ? *str = '-' : 0;
	return (str);
}

typedef struct	s_test
{
	char *an_int;
	char *a_long;
	char *nothing;
}		t_test;

int	main(void)
{
	t_test test;

	test = (t_test){"123", "11111111111", "jfzaojfz"};

	int implicit_cast1 = atoi(test.an_int);
	int implicit_cast2 = atoi(test.a_long);
	int implicit_cast3 = atoi(test.nothing);

	char *cmp1 = ft_itoa(implicit_cast1);
	char *cmp2 = ft_itoa(implicit_cast2);
	char *cmp3 = ft_itoa(implicit_cast3);

	int bool1 = (strcmp(cmp1, test.an_int) != 0);
	int bool2 = (strcmp(cmp2, test.a_long) != 0);
	int bool3 = (strcmp(cmp3, test.nothing) != 0);

	printf("string = %s is%san int\n", test.an_int, bool1 == 1 ? " NOT " : " ");
	printf("string = %s is%san int\n", test.a_long, bool2 == 1 ? " NOT " : " ");
	printf("string = %s is%san int\n", test.nothing, bool3 == 1 ? " NOT " : " ");
}
