#include <string.h>
#include <stdio.h>
#include "tab.h"

void copy(char *src, char *dest);

/* detab: removes all tabs and replaces with the appropriate number of spaces. 
 * Returns the number of extra characters */
/* TODO: IMPLEMENT MAXLEN */
int detab(char *s, size_t maxlen, size_t tbw, size_t tstart)
{
	char s_cpy[maxlen];
	copy(s, s_cpy);

	int n, p, offst, newline;
	n = offst = 0;
	newline = 1;

	while(s_cpy[n] != '\0')
	{
		if(s_cpy[n] == '\t')
		{
			int w;
			// first tab is remainder or modulus. Subsequent tabs are just tab width.
			/* if it's  a new line tabwidth is possibly effectively wider */
			if(newline)
			{

				w = tbw * tstart - (n + offst) % tbw;
				newline = 0;
			}
			else
			{
				w = tbw - (n + offst) % tbw;
			}
			/* if new line add appropriate number of extra tabs (if any specified) */
			for(p = 0; p < w; ++p)
			{
				s[n+offst] = ' ';
				++offst;
			}
			--offst;
		}
		else
		{
			s[n+offst] = s_cpy[n];
			if(s_cpy[n] == '\n')
				newline = 1;

		}
		++n;
	}
	s[n+offst] = '\0';
	//return n+offst;
	return offst; /* I think this will tell us the extra characters added */
}

/* entab: This takes in a string with first position of '\t' or ' ' and rearranges it
 * and adds it to the given string, then moves pointer ahead to first non blank
 * space character. Returns removed spaces  */ //TODO: INTEGRATE MAXLEN IN
int entab(char *s, size_t maxlen, size_t tabsz, size_t tstart)
{
	if(strlen(s) == 0)
	{
		printf("Input string is empty\n");
		return -1;
	}

	char tmp[strlen(s)+1];

	/* now work with our tmp string */
	int i, j, pos, pos_prev, newline;
	i = j = pos = pos_prev = 0;
	newline = 1;
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
					/* if it's a new line add appropriate number of extra spaces (if any)
					 * to calculated ending position */
					if(newline)
					{
						pos += tabsz * tstart - pos % tabsz;
						newline = 0;
					}
					else
					{
						pos += tabsz - pos % tabsz;
					}
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
			if(s[i] == '\n')
				newline = 1;
			++pos;
		}
		++i;

	}
	tmp[j] = '\0';
	strcpy(s, tmp);

	return i-j;
}

/* copies source string into destination string. Just felt like writing my own for fun instead
 * of using function in standard string.h library */
void copy(char *src, char *dest)
{
    int i = 0;
    while((dest[i] = src[i]) != '\0')
        ++i;
}
