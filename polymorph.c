#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef	struct	s_poly
{
	void	*content;
	int	size;
}		t_poly;

typedef struct	s_one
{
	char	*content;
	int	size;
	int	toto;
	int	titi;
}		t_one;

int	main(void)
{
	t_poly	*poly;
	t_one	*one;

	one = (t_one *)malloc(sizeof(t_one));
	one->content = strdup("test");
	one->size = strlen(one->content);
	one->toto = 550;
	one->titi = 1100;
	poly = (t_poly *)one;
	printf("%d %s\n", poly->size, (char *)poly->content);
	return (0);
}
