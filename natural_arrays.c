#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline long		get_digit_len(int base, long max)
{
	const char	tmp[256];

	switch (base) {
		case 16:
			snprintf((char*)tmp, 256, "%lx", max);
			break;
		case 8:
			snprintf((char*)tmp, 256, "%lo", max);
			break;
		default:
			snprintf((char*)tmp, 256, "%ld", max);
			break;
	}
	return (strlen(tmp));
}

int						main()
{
	long		xsize, ysize, zsize;
	long		*table;

	xsize = 5;
	ysize = 4;
	// This is a 1d allocated array
	table = malloc(sizeof(long) * xsize * ysize);
	// A bit weird of a syntax but well...
	long	(*t2d)[xsize][ysize] = ((long(*)[xsize][ysize])table);

	// Fill the table
	for (int x = 0; x < xsize * ysize; ++x)
		table[x] = x;

	printf("This is a demonstration on how to use variable typing in c.\n");
	printf("Here we are using it to easily access arrays with continuous memory.\n\n");
	printf("Here is an allocated array of size \e[35m%ld\e[0;2mx\e[0;34m%ld\e[0m \e[2m(\e[0m%ld\e[2m)\e[0m:\n", xsize, ysize, xsize * ysize);

	// Format digits len for formating
	long		len = get_digit_len(10, xsize * ysize);

	// Start reading as 1d array
	printf("As 1d Array: \e[35m[\e[0m\n\t");
	for (int i = 0; i < xsize * ysize; ++i)
	{
		printf("%*ld", (int)len, table[i]);
		if (i < xsize * ysize - 1)
		{
			printf("\e[2m,\e[0m");
			if (i % xsize == xsize - 1)
				printf("\n\t");
			else
				printf(" ");
		}
	}
	printf("\n\e[35m]\e[0m\n");

	// Start reading as 2d array
	printf("As 2d Array: \e[35m[\e[0m\n");
	for (int x = 0; x < xsize; ++x)
	{
		printf("\t\e[34m[\e[0m ");
		for (int y = 0; y < ysize; ++y)
		{
			printf("%*ld", (int)len, (*t2d)[x][y]);
			if (y < ysize - 1)
				printf("\e[2m,\e[0m ");
		}
		if (x < xsize - 1)
			printf(" \e[34m]\e[2m,\e[0m\n");
		else
			printf(" \e[34m]\e[0m\n");
	}
	printf("\e[35m]\e[0m\n");

	free(table);

	printf("\n");

	xsize = 3;
	ysize = 4;
	zsize = 5;

	printf("Now let's look at this one which is \e[35m%ld\e[0;2mx\e[0;34m%ld\e[0;2mx\e[0;32m%ld\e[0m "
			"\e[2m(\e[0m%ld\e[2m)\e[0m "
			"\e[2m(\e[0mlong\e[2m)\e[0m"
			":\n",
			xsize, ysize, zsize, xsize * ysize * zsize);

	// Format digits len for formating
	len = get_digit_len(10, xsize * ysize * zsize);
	table = malloc(sizeof(long) * xsize * ysize * zsize);
	// Casting to vla pointer to use the c array natural syntax
	// A bit weird of a syntax but well...
	long	(*t3d)[xsize][ysize][zsize] = ((long(*)[xsize][ysize][zsize])table);

	for (int i = 0; i < xsize * ysize * zsize; ++i)
		table[i] = i;

	// Start reading as 1d array
	printf("As 1d (long) Array: \e[35m[\e[0m\n\t");
	for (int i = 0; i < xsize * ysize * zsize; ++i)
		{
			printf("%*ld", (int)len, table[i]);
			if (i < xsize * ysize * zsize - 1)
			{
				if (i % (xsize * ysize) == xsize * ysize - 1)
					printf("\e[2m,\e[0m\n\t");
				else
					printf("\e[2m,\e[0m ");
			}
		}
	printf("\n\e[35m]\e[0m\n");

	// Start reading as 3d array
	printf("As 3d (long) Array: \e[35m[\e[0m\n"); // [
	for (int x = 0; x < xsize; ++x)
	{
		printf("\t\e[34m[\e[0m "); // [
		for (int y = 0; y < ysize; ++y)
		{
			printf("\e[32m[\e[0m"); // [
			for (int z = 0; z < zsize; ++z)
			{

				// This is it right there
				printf("%*ld", (int)len, (*t3d)[x][y][z]);

				if (z < zsize - 1) printf("\e[2m,\e[0m"); // ,
			}
			printf("\e[32m]\e[0m"); // ]
			if (y < ysize - 1)
				printf("\e[32;2m,\e[0m "); // ,
		}
		printf(" \e[34m]\e[0m"); // ]
		if (x < xsize - 1)
			printf("\e[34;2m,\e[0m"); // ,
		printf("\n"); // newline
	}
	printf("\e[35m]\e[0m\n"); // ]

	// This is the element count so since we divided it by 2 with the type change.
	// 		(in x86_64 anyway).
	// This could be any of the axis really, I just chose x because of the printing.
	zsize *= 2;
	// Casting to vla pointer to use the c array natural syntax
	int	(*t3di)[xsize][ysize][zsize] = ((int(*)[xsize][ysize][zsize])table);
	printf("\e[2mNote: Here we virtually change the size to keep reading the same amount of memory.\e[0m\n");
	printf("\e[2mNote: the memory seems reversed because of the little endian of the machine.\e[0m\n");

	printf("As 3d (int) Array: \e[35m[\e[0m\n"); // [
	for (int x = 0; x < xsize; ++x)
	{
		printf("\t\e[34m[\e[0m "); // [
		for (int y = 0; y < ysize; ++y)
		{
			printf("\e[32m[\e[0m"); // [
			for (int z = 0; z < zsize; ++z)
			{

				// This is it right there
				printf("%0*d", (int)len, (*t3di)[x][y][z]);

				if (z < zsize - 1) printf("\e[2m,\e[0m"); // ,
			}
			printf("\e[32m]\e[0m"); // ]
			if (y < ysize - 1) printf("\e[32;2m,\e[0m "); // ,
		}
		printf(" \e[34m]\e[0m"); // ]
		if (x < xsize - 1)
			printf("\e[34;2m,\e[0m"); // ,
		printf("\n"); // newline
	}
	printf("\e[35m]\e[0m\n"); // ]

	free(table);
}
