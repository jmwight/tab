#include <stdio.h>
#include <string.h>

#define MAXSZ	256
#define TABSZ	8

int tab_and_space(char *s, int *i, int *pos);

int main(void)
{
	int c, i, pos;
	i = 0;
	char s[MAXSZ];
	while((c = getchar()) != EOF)
		s[i++] = c;
	s[i] = '\0';

	int n;
	for(n = 0; n < i; ++n, ++pos)
	{
		if(s[n] == ' ' || s[n] == '\t')
			tab_and_space(s, &n, &pos);
	}
	printf("\n%s", s);
	printf("\nBefore: %8d", i);
	printf("\nBefore: %8d\n", n);
}

/* TODO: call this function something better 
 * This takes in a string with first position of '\t' or ' ' and rearranges it 
 * and adds it to the given string, then moves pointer ahead to first non blank 
 * space character */
int tab_and_space(char *s, int *i, int *pos)
{
	if(s[*i] != ' ' && s[*i] != '\t')
		return -1; /* we got something that tabs or spaces */
	
	/* TODO: do something if \0 is encountered */

	int end, tabmod, n, spacecnt; //TODO: REMOVE tabmod, IT'S NOT NEEDED ANYMORE

	/* find end of blank space */
	end = *i;
	while(s[end] != '\0' && (s[end] == ' ' || s[end] == '\t'))
		++end;

	/* find out how much it would have advanced it */
	tabmod = TABSZ - *i % TABSZ; //TODO: REMOVE THIS LINE AFTER DEBUGGING, IT'S NOT NEEDED ANYMORE
	spacecnt = 0;
	for(n = *i; n < end; n++)
	{
		if(s[n] == '\t')
		{
			spacecnt = TABSZ - (n + spacecnt) % TABSZ;
		}
		else if(s[n] == ' ')
		{
			++spacecnt;
		}
		else
			printf("error: non whitespace character encountered when not supposed to be.");
	}

	/* now find minimum spaces and tabs we need to do and fix string provided to us */
	n = 0;
	while(spacecnt > 0)
	{
		/* add in all the tabs until the tabs bring us too far */
		if(spacecnt / TABSZ)
		{
			s[*i] = 'T';
			int tabmov = TABSZ - *i % TABSZ;
			spacecnt -= tabmov;
			++*i;
			*pos += tabmov;
			
		}
		/* add all the spaces until we run out */
		else
		{
			//s[*i++] = ' ';
			s[*i++] = 'S';
			++*pos;
		}
	}

	/* now move the remaining string forward */
	strcpy(&s[*i], &s[end+1]);
}
