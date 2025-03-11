#include <stdio.h>
#include <string.h>

#define MAXSZ	256
#define TABSZ	8

int detab(char *s);

int main(void)
{
	int c, i;
	i = 0;
	char s[MAXSZ];
	while((c = getchar()) != EOF && i < MAXSZ - 2)
		s[i++] = c;
	s[i] = '\0';

	int n, prev_ch;
	prev_ch = 0;
	for(n = 0; n < i; ++n, ++pos)
	{
		if((s[n] == ' ' || s[n] == '\t') && prev_ch == ' ' || s[n])
			tab_and_space(s, &n, &pos);
		prev_ch = s[n];
	}
	printf("\n%s", s);
	printf("\nBefore: %8d", i);
	printf("\nBefore: %8d\n", n);
}

/* detab: This takes in a string with first position of '\t' or ' ' and rearranges it 
 * and adds it to the given string, then moves pointer ahead to first non blank 
 * space character. Returns removed spaces  */
int detab(char *s, size_t MAXLEN, size_t TABSZ)
{
	if(strlen(s) == 0)
	{
		printf("Input string is empty\n");
		return -1;
	}
	
	int stsz, edsz;
        stsz = (int) strlen(s); // get starting size of string	
	char tmp[stsz+1];
	strcpy(tmp, s);
	
	/* now work with our tmp string */
	int i, j, pos, pos_prev;
	i = j = pos = pos_prev = 0;
	while(s[i] != '\0')
	{
		/* we need to update pos something possibly other than 1 because tab advances not one character but to next tab stop */
		if(s[i] == '\t' && s[i-1] != ' ')
		{
			pos_prev = pos;
			pos += TABSZ - pos % TABSZ;
		}

		if((s[i] == '\t' || s[i] == ' ') && s[i-1] == ' ')
		{
			/* look ahead?? */
			/* next tab defined as "TABSZ - pos % TABSZ" */
			/* look ahead code */
			/* rewind back one character to start at beginning */
			--i;
			--j;
			if(s[i] == '\t')
			{
				pos = pos_prev;
			}
			int i_tmp = i;
			
			/* see what ending position would be from all the spaces and tabs */
			while(s[i_tmp] == ' ' || s[i_tmp] == '\t')
			{
				if(s[i] == '\t')
					pos += TABSZ - pos % TABSZ;
				else if(s[i_tmp] == ' ')
					++pos;
				else
					printf("error\n");
				++i_tmp;
			}

			/* difference pos and pos_prev is spaces (if that is relevant) */
			int total_spaces, tab_sp_inc;
		        total_spaces = pos - prev_pos;

			/* now replace with as many tabs as possible */
			while((tab_sp_inc = TABSZ - pos % TABSZ) < spaces)
			{
				tmp[j++] = '\t';
				prev_pos += tab_sp_inc;
				spaces -= tab_sp_inc;
			}

			/* now add appropriate amount of spaces */
			while(spaces > 0)
			{
				tmp[j++] = ' ';
				spaces--;
			}

		}
		++i;

	}
	tmp[j] = '\0';
	int saved_space = i - j; /* we will return this as the spaces saved */
	j = 0;
	do
	{
		s[j] = tmp[j];
	} while(tmp[j++] != '\0');

	return saved_spaces;
}
