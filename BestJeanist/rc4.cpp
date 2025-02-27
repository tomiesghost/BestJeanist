#include <Windows.h>
#include "rc4.h"

// https://github.com/anthonywei/rc4 
void rc4_setup(struct rc4_state* s, PUCHAR key, INT length)
{
	int i, j, k, * m, a;

	s->x = 0;
	s->y = 0;
	m = s->m;

	for (i = 0; i < 256; i++)
	{
		m[i] = i;
	}

	j = k = 0;

	for (i = 0; i < 256; i++)
	{
		a = m[i];
		j = (unsigned char)(j + a + key[k]);
		m[i] = m[j]; m[j] = a;
		if (++k >= length) k = 0;
	}
}

void rc4_crypt(struct rc4_state* s, PUCHAR data, INT length)
{
	int i, x, y, * m, a, b;

	x = s->x;
	y = s->y;
	m = s->m;

	for (i = 0; i < length; i++)
	{
		x = (unsigned char)(x + 1); a = m[x];
		y = (unsigned char)(y + a);
		m[x] = b = m[y];
		m[y] = a;
		data[i] ^= m[(unsigned char)(a + b)];
	}

	s->x = x;
	s->y = y;
}
