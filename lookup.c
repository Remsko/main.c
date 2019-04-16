#include <stddef.h>
#include <stdio.h>

/*
 * This is used a type throughout this program
 *
 * It's mainly for being explicit though I wouldn't recommend using something
 *   else as this is the best way to use it I know.
 *   Using pointers is out of the question and using it can be confusing.
 */

typedef enum	e_type
{
	TYPE_1,
	TYPE_2,
	TYPE_3,
	TYPE_4,
	TYPE_MAX
}				t_type;

/*
 * The following structures are each form the data can take.
 *
 * You can view them as the argument of the callback though it is not accurate.
 */

typedef struct	s1
{
	t_type		type;
	void		*data;
}				t_s1;

typedef struct	s2
{
	t_type		type;
	int			data;
}				t_s2;

typedef struct	s3
{
	t_type		type;
	void		*data;
	int			padding;
}				t_s3;

/*
 * This is the tagged union itself.
 */

typedef union	u_data
{
	t_type		type;
	t_s1		s1;
	t_s2		s2;
	t_s3		s3;
}				t_data;

// Defining the callback function type
typedef void	(*t_cb_ptr)(t_data);
// Defining the parser for the data
typedef t_data	(*t_data_ptr)(void*);

/*
 * Implementation of the callback functions.
 *
 * Note that you can use the same callback for multiple types and vice versa.
 */

void			func1(t_data data)
{
	printf("Data as s1 [%d]: '%p'\n", data.type, data.s1.data);
}

void			func2(t_data data)
{
	printf("Data as s2 [%d]: '%d'\n", data.type, data.s2.data);
}

void			func3(t_data data)
{
	printf("Data as s3 [%d]: '%p' '%d'\n", data.type, data.s3.data, data.s3.padding);
}

/*
 * Implementation of the data generation function
 *   This part of the program is optional to not use it just give the data in
 *   arument to `func_select` and generate it somewhere else.
 */

t_data			generate_generic_data(void *data)
{
	return ((t_data){
		.s1 = (t_s1){
			.type = TYPE_1,
			.data = data,
		}
	});
}

t_data			generate_int_data(void *data)
{
	return ((t_data){
		.s2 = (t_s2){
			.type = TYPE_2,
			.data = (int)data,
		}
	});
}

t_data			generate_big_data(void *data)
{
	return ((t_data){
		.s3 = (t_s3){
			.type = TYPE_3,
			.data = data,
			.padding = (short)data,
		}
	});
}

/*
 * And then the meat of the program, the selecter of callback.
 *
 * On this example we have a lookup of function pointer corresponding to
 *   the type of the data sent. But you can implement whatever as long as you can
 *   distinguish between different data, though type matching is the most common.
 */

void			func_select(t_type type, void *data)
{
	static t_cb_ptr		callback[TYPE_MAX] = {
		[TYPE_1] = &func1,
		[TYPE_2] = &func2,
		[TYPE_3] = &func3,
		[TYPE_4] = &func2,
	};
	static t_data_ptr	generate[TYPE_MAX] = {
		[TYPE_1] = &generate_generic_data,
		[TYPE_2] = &generate_int_data,
		[TYPE_3] = &generate_big_data,
		[TYPE_4] = &generate_generic_data,
	};

	callback[type](generate[type](data));
}

/*
 * Some random test to show the output.
 *
 * If you don't understand the way tagged union works, refer to `poly_pocket.c`
 *
 * Here type 4 is a little funky if you understand why it displays that way
 *   you more or less understand the concept.
 */

int				main(void)
{
	func_select(TYPE_4, (void*)23645237);
	func_select(TYPE_3, (void*)12);
	func_select(TYPE_2, (void*)42);
	func_select(TYPE_1, (void*)1254);
}
