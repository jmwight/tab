#include <stdio.h>
#include <string.h>
#include "tab.h"

#define MAXSZ	256
#define TABSIZE	8

int main(void)
{
	/* get string from user */
	int c, i;
	i = 0;
	char s[MAXSZ];
	while((c = getchar()) != EOF && i < MAXSZ - 2)
		s[i++] = c;
	s[i] = '\0';

	/* run detab function */
	int len, ch_saved;
	len = strlen(s);
	ch_saved = entab(s, MAXSZ, TABSIZE);
	
	printf("\n%s", s);
	printf("\nPrev Length: %8d", len);
	printf("\nCharacters Saved: %8d\n", ch_saved);
}
