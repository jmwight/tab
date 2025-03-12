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
int detab(char *s, size_t maxlen, size_t tabsz)
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
			pos += tabsz - pos % tabsz;
		}

		if((s[i] == '\t' || s[i] == ' ') && s[i-1] == ' ')
		{
			/* look ahead?? */
			/* next tab defined as "tabsz - pos % tabsz" */
			/* look ahead code */
			/* rewind back one character to start at beginning */
			--i;
			/* j--; REMOVED */
			if(s[i] == '\t')
			{
				pos = pos_prev;
			}
			//int i_tmp = i; I don't think this is needed and could possibly be deleted 
			
			/* see what ending position would be from all the spaces and tabs */
			while(s[i] == ' ' || s[i] == '\t') /* changing all i_tmp to i */
			{
				if(s[i] == '\t')
					pos += tabsz - pos % tabsz;
				else if(s[i] == ' ')
					++pos;
				else
					printf("error\n");
				++i;
			}

			/* difference pos and pos_prev is spaces (if that is relevant) */
			int total_spaces, tab_sp_inc;
		        total_spaces = pos - pos_prev;

			/* now replace with as many tabs as possible */
			while((tab_sp_inc = tabsz - pos % tabsz) < total_spaces)
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

	return saved_space;
}
