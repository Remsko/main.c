#include "unistd.h"
#include "stdlib.h"

/* Chained list structure */
typedef struct s_list
{
	struct s_list	*next;
	char content;
} t_list;

/* The following ten functions return the hexadecimal corresponding to the
	 digit read*/
char print_zero(void)
{
	/* 0011 1111 */
	return (0x3F);
}

char print_one(void)
{
	/* 0000 0110 */
  return (0x06);
}

char print_two(void)
{
	/* 0101 1011 */
  return (0x5B);
}

char print_three(void)
{
	/* 0100 1111 */
  return (0x4F);
}

char print_four(void)
{
	/* 0110 0110 */
  return (0x66);
}

char print_five(void)
{
	/* 0110 1101 */
  return (0x6D);
}

char print_six(void)
{
	/* 0111 1101 */
  return (0x7D);
}

char print_seven(void)
{
	/* 0000	0111 */
  return (0x07);
}

char print_height(void)
{
	/* 0111	1111 */
  return (0x7F);
}

char print_nine(void)
{
	/* 0110	1111 */
  return (0x67);
}

/* The following three functions print spaces, pipes and underscores according
	 to the state of the bit evaluated. For example, the first function print an
	 underscore if the content's first bit is 1 and spaces if it is 0 */
void print_first_line(t_list *alist)
{
	while (alist != NULL)
	{
		if (alist->content & (1 << 0))
			write(1, " _ ", 3);
		else
			write(1, "   ", 3);
		alist = alist->next;
	}
	write(1, "\n", 1);
}

void print_second_line(t_list *alist)
{
	while (alist != NULL)
	{
		if (alist->content & (1 << 5))
			write(1, "|", 1);
		else
			write(1, " ", 1);
		if (alist->content & (1 << 6))
			write(1, "_", 1);
		else
			write(1, " ", 1);
		if (alist->content & (1 << 1))
			write(1, "|", 1);
		else
			write(1, " ", 1);
		alist = alist->next;
	}
	write(1, "\n", 1);
}

void print_third_line(t_list *alist)
{
	while (alist != NULL)
	{
		if (alist->content & (1 << 4))
			write(1, "|", 1);
		else
			write(1, " ", 1);
		if (alist->content & (1 << 3))
			write(1, "_", 1);
		else
			write(1, " ", 1);
		if (alist->content & (1 << 2))
			write(1, "|", 1);
		else
			write(1, " ", 1);
		alist = alist->next;
	}
	write(1, "\n\n", 2);
}

/* The following four functions allow the manipulation of chained lists */
void list_reverse(t_list **alist)
{
	t_list	*next;
	t_list	*previous;

	previous = NULL;
	while (*alist != NULL)
	{
		next = (*alist)->next;
		(*alist)->next = previous;
		previous = (*alist);
		*alist = next;
	}
	*alist = previous;
}

void list_add_start(t_list **head, t_list *new)
{
	if (head != NULL && new != NULL)
	{
		new->next = *head;
		*head = new;
	}
}

t_list *list_new(int content)
{
	t_list *new;

	if ((new = (t_list *)malloc(sizeof(t_list))) != NULL)
	{
		new->next = NULL;
		new->content = content;
	}
	return (new);
}


void list_delete(t_list **head)
{
	t_list *tmp;

	if (head != NULL)
	{
		while (*head)
		{
			tmp = (*head)->next;
			free(*head);
			*head = tmp;
		}
		*head = NULL;
	}
}

/* Main */
int main(int argc, char **argv)
{
	/* Variable declarations */
	char (*number_handler[10])(void);
	t_list *lst;
	int i;
	int j;
	int nb;
	int ret;

	/* Variable initialization */
	lst = NULL;
	number_handler[0] = print_zero;
	number_handler[1] = print_one;
	number_handler[2] = print_two;
	number_handler[3] = print_three;
	number_handler[4] = print_four;
	number_handler[5] = print_five;
	number_handler[6] = print_six;
	number_handler[7] = print_seven;
	number_handler[8] = print_height;
	number_handler[9] = print_nine;

	/* Populating the chained list */
	if (argc > 1)
	{
		i = 1;
		while (argv[i] != NULL)
		{
			j = 0;
			while (argv[i][j])
			{
				nb = argv[i][j] - '0';
				if (nb >= 0 && nb <= 9)
				{
					ret = (*number_handler[nb])();
					list_add_start(&lst, list_new(ret));
				}
				else
					break;
				++j;
			}
			++i;
		}
		/* Inversion of elements and displaying lines */
		list_reverse(&lst);
		print_first_line(lst);
		print_second_line(lst);
		print_third_line(lst);
		list_delete(&lst);
	}
	return (0);
}
