#include <stdio.h>

typedef struct	s_struct
{
	char	*test1;
	int	test2;
}		t_struct;

int	main(void)
{
	void		*tmp;
	char		*douze = "12";
	int		*undeux = (int [2]){1, 2};
	t_struct	*unetdeux = (t_struct[2]){{"1", 1},{"2", 2}};

	printf("CHAR\n\n\n");
	printf("sizeof(char) = %zu\n\n", sizeof(char));

	tmp = douze;
	printf("ptr hexa value case 0 = %d\n", (int)tmp);
	douze++;
	tmp = douze;
	printf("ptr hexa value case 1 = %d\n", (int)tmp);

	printf("\n\n\n\n");


	printf("INT\n\n\n");
	printf("sizeof(int) = %zu\n\n", sizeof(int));	

	tmp = undeux;
	printf("ptr hexa value case 0 = %d\n", (int)tmp);
	undeux++;
	tmp = undeux;
	printf("ptr hexa value case 1 = %d\n", (int)tmp);

	printf("\n\n\n\n");


	printf("STRUCT\n\n\n");
	printf("sizeof(t_struct) = %zu\n\n", sizeof(t_struct));	

	tmp = unetdeux;
	printf("ptr hexa value case 0 = %d\n", (int)tmp);
	unetdeux++;
	tmp = unetdeux;
	printf("ptr hexa value case 1 = %d\n", (int)tmp);

	return (0);
}
