#include <stdio.h>
#include <string.h>
#include "tab.h"
#include <stdlib.h>

#define MAXSZ	10240
#define TABSIZE	8

#define true	1
#define false	0

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Usage: ./tab e/d\n");
		return -1;
	}

	int d, e, fi, fo, tbw, following; /* following for something like a file path following */
	char *f_i_path, *f_o_path;
	d = e = fi = fo = following = false;
	tbw = -1;

	/* Options: -d for detab, -e for entab, -i for reading from file, -o for writeint to a file */
	while(--argc > 0)
	{
		char c;
		if(**++argv == '-')
			++*argv;
		while((c = *(*argv)++) != '\0' && !following)
		{
			switch(c)
			{
			case 'e':
				e = true;
				break;
			case 'd':
				d = true;
				break;
			case 'i':
				fi = true;
				f_i_path = *++argv; /* set pointer to next argument */
				--argc;
				following = true;
				break;
			case 'o':
				fo = true;
				f_o_path = *++argv;
				following = true;
				--argc;
				break;
			case 't':
				tbw = atoi(*++argv);
				following = true;
				--argc;
				if(tbw < 1 || tbw >= MAXSZ)
				{
					printf("Error: tabwidth must be [1, MAXSZ)\n");
					tbw = TABSIZE;
				}
				following = true;
				break;
			}
		}
		following = false;

	}

	if(e && d)
	{
		printf("Usage: can only be entab or detab not both!\n");
		return -1;
	}
	else if(!e && !d)
	{
		printf("Usage: must specify either entab or detab!\n");
		return -1;
	}

	/* if tabwidth wasn't set we will set to default */
	if(tbw == -1)
		tbw = TABSIZE;

	/* Get data from text file if specified. If not get directly from stdin */
	char s[MAXSZ];	
	if(fi)
	{
		char *pos = s;
		char buf[MAXSZ];
		FILE *f = fopen(f_i_path, "r");
		int c;
		while((c = fgetc(f)) != EOF && c != '\0')
		{
			*pos++ = c;
			putchar(c);
		}
		fclose(f);
	}
	else
	{
		/* get string from user */
		int c, i;
		i = 0;
		while((c = getchar()) != EOF && i < MAXSZ - 2)
			s[i++] = c;
		s[i] = '\0';
	}

	int len, ch_saved;
	len = strlen(s);

	/* entab was specified */
	if(e)
	{
		ch_saved = entab(s, MAXSZ, tbw);
	}
	/* detab was specified */
	else if(d)
	{
		ch_saved = detab(s, MAXSZ, tbw);
	}

	printf("\n%s", s);
	printf("\nPrev Length: %8d", len);
	printf("\nCharacters Saved (extra): %8d\n", ch_saved);

	/* write results to given output file if specified */
	if(fo)
	{
		FILE *f = fopen(f_o_path, "w");
		fputs(s, f);
		fclose(f);
	}
}
