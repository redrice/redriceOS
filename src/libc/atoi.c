#include <stdlib.h>

int atoi(char *str)
{
	int r = 0;
  
	for (int i = 0; str[i] != '\0'; ++i)
		r = r*10 + str[i] - '0';

	return r;
}

