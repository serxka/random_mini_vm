#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>


// wtf lmao
int main (int argc, char *argv[])
{
	// check we have args
	if (argc != 3) {
		fprintf(stderr, "Usage: [INPUT] [OUTPUT]\n  Example: hex2bin code.hex code.bin\n");
		exit (-1);
	}

	// open our files
	FILE *input = fopen (argv[1], "r");
	FILE *output = fopen (argv[2], "a+");
	if (!input) {
		perror ("Error loading input file");
		exit (-1);
	}
	if (!output) {
		perror ("Error loading output file");
		exit (-1);
	}

	unsigned char value = 0x0;
	int second = 0;
	char c = 0;
	while ((c = fgetc(input)) != EOF)
	{
		if (c <= '9' && c >= '0') {

		// check thats its a proper hex value
				goto convert;			
		} else if (isalpha(c)){
			int letter = tolower(c);
			if (letter <= 'f' && letter >= 'a') {
				goto convert;
			 }

			continue;
		} else {continue;					}
		convert:

				if (second){
					value |= strtol(&c, NULL, 16);

					second = 0;
					fwrite(&value, 1, 1, output);

					value =0;
					continue;
				}
				value = strtol(&c, NULL, 16) << 4;

				second = 1;
	}
	fflush (output);
	fclose (input);
	fclose (output);
	
	exit (0);
}