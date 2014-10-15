#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	FILE* debug_file = fopen("debug.txt", "w");
	char bobby[1100];
	int idx_search, idx_bobby = 0;
	int brackets = 0;
	int c, n_repeat, i, j;

	while ((c = getchar()) != EOF) {
		if (c >= 'a' && c <= 'z' && (brackets == 0))
			putchar(c);
		else if (c >= 'a' && c <= 'z' && brackets)
			bobby[idx_bobby++] = c;
		else if (c == '[') {
			bobby[idx_bobby++] = '[';
			brackets++;
		}
		else if (c == ']') {
			n_repeat = 0;
			c = getchar();
			while (isdigit(c)) {
				n_repeat = (n_repeat * 10) + (c - '0');
				c = getchar();
			}
			
			ungetc(c, stdin);
			
			if (brackets == 1) {
				for (i = 0; i < n_repeat; i++)
					for (j = 1; j < idx_bobby; j++)
						putchar(bobby[j]);
				idx_bobby = 0;
			}
			
			else {
				for (idx_search = idx_bobby; bobby[idx_search] != '['; idx_search--) ;
				
				for (i = 0; i < n_repeat; i++) 
					for (j = 0; j < (idx_bobby - idx_search - 1); j++) {
						if (i == 0) 
							bobby[idx_search+j] = bobby[idx_search+j+1];
						
						else 
							bobby[j + idx_search + (i * (idx_bobby - idx_search - 1))] = bobby[idx_search + j];
						
					}

				idx_bobby = idx_search + ((idx_bobby - idx_search - 1) * n_repeat);
			}

			brackets--;
		}
		
		else if (c == '\n')
			putchar('\n');
		
	}
}
