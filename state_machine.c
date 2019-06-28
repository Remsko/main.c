#include <stdbool.h>
#include <stdio.h>

typedef enum		e_state {
	ST_ERROR,
	ST_INIT,
	ST_SPACE,
	ST_WORD,
	ST_MAX
}					state;

static const char	*state_print[ST_MAX] = {
	[ST_ERROR] = "Error",
	[ST_INIT]  = "Init ",
	[ST_SPACE] = "Space",
	[ST_WORD]  = "Word "
};

typedef enum		e_color {
	RESET,
	BOLD,
	UNDER,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	AQUA,
	GREY,
	WHITE,
	COL_MAX
}					t_color;

static const char	* const colors[COL_MAX] = {
	[RESET] = "\e[0m",
	[BOLD] = "\e[1m",
	[UNDER] = "\e[4m",
	[RED] = "\e[31m",
	[GREEN] = "\e[32m",
	[YELLOW] = "\e[33m",
	[BLUE] = "\e[34m",
	[PURPLE] = "\e[35m",
	[AQUA] = "\e[36m",
	[GREY] = "\e[37m",
	[WHITE] = "\e[38m",
};

static const state	transitions[ST_MAX][256] = {
	[ST_INIT ... ST_WORD][' ' + 1 ... '~'] = ST_WORD,
	[ST_INIT ... ST_WORD][' '] = ST_SPACE,
};

static const bool	counter[ST_MAX][ST_MAX] = {
	[ST_INIT ... ST_SPACE][ST_WORD] = true
};

static int			get_word_count(const char *str)
{
	int				count;
	state			next;
	state			prev;

	count = 0;
	prev = ST_INIT;
	while (*str) {
		next = transitions[prev][*str];
		count += counter[prev][next];
		printf("%s[%s%s%c%s%s] %s%s%s -> %s%s%s | count: %s%d%s\n",
				colors[GREY],
				colors[BOLD], colors[GREEN], *str, colors[RESET],
				colors[GREY],
				colors[PURPLE], state_print[prev], colors[RESET],
				colors[YELLOW], state_print[next], colors[RESET],
				colors[GREEN], count, colors[RESET]
		);
		prev = next;
		++str;
	}
	return (count);
}

int					main(int c, char **v)
{
	if (c > 1)
		printf("Words in argv[1]: %d\n", get_word_count(v[1]));
}
