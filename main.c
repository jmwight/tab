#include <stdio.h>
#include <string.h>

#define MAXSZ	256
#define TABSIZE	8

int detab(char *s, size_t maxlen, size_t tabsz);

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
	ch_saved = detab(s, MAXSZ, TABSIZE);
	
	printf("\n%s", s);
	printf("\nPrev Length: %8d", len);
	printf("\nCharacters Saved: %8d\n", ch_saved);
}

/* detab: This takes in a string with first position of '\t' or ' ' and rearranges it 
 * and adds it to the given string, then moves pointer ahead to first non blank 
 * space character. Returns removed spaces  */ //TODO: INTEGRATE MAXLEN IN 
int entab(char *s, size_t maxlen, size_t tabsz)
{
	if(strlen(s) == 0)
	{
		printf("Input string is empty\n");
		return -1;
	}
	
	char tmp[strlen(s)+1];
	
	/* now work with our tmp string */
	int i, j, pos, pos_prev;
	i = j = pos = pos_prev = 0;
	while(s[i] != '\0')
	{
		/* we need to update pos something possibly other than 1 because tab advances not one character but to next tab stop */
		/*if(s[i] == '\t' && s[i-1] != ' ')
		{
			pos_prev = pos;
			pos += tabsz - pos % tabsz;
			tmp[j++] = s[i++];
		}*/

		if((s[i] == '\t' || s[i] == ' ') && (s[i-1] == ' ' || s[i-1] == '\t'))
		{
			--i;
			j--;
			if(s[i] == '\t')
			{
				pos = pos_prev;
			}
			else
			{
				--pos;
				pos_prev = pos;
			}
			
			/* see what ending position would be from all the spaces and tabs */
			while(s[i] == ' ' || s[i] == '\t') 
			{
				if(s[i] == '\t')
					pos += tabsz - pos % tabsz;
				else if(s[i] == ' ')
					++pos;
				else
					printf("error\n");
				++i;
			}
			--i;

			/* difference pos and pos_prev is spaces (if that is relevant) */
			int total_spaces, tab_sp_inc;
		        total_spaces = pos - pos_prev;

			/* now replace with as many tabs as possible */
			while((tab_sp_inc = tabsz - pos_prev % tabsz) <= total_spaces)
			{
				tmp[j++] = '\t';
				pos_prev += tab_sp_inc;
				total_spaces -= tab_sp_inc;
			}

			/* now add appropriate amount of spaces */
			while(total_spaces > 0)
			{
				tmp[j++] = ' ';
				total_spaces--;
			}

		}
		else
		{
			tmp[j++] = s[i];
			++pos;
		}
		++i;

	}
	tmp[j] = '\0';
	strcpy(s, tmp);

	return i-j;
}
