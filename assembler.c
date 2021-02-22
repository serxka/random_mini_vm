// lets see if i can write an assembler

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

static void convert(char* str, uint8_t* buf);
static bool starts_with(const char* item, const char* match);

int main (int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s [FILE] [OUT]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE* as = fopen(argv[1], "r");
	if (as == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	FILE* out = fopen((argc >= 3) ? argv[2] : "a.out", "w");
	if (out == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, as)) != -1) {
		uint8_t data[4] = {0};
		convert(line, data);

		fwrite(data+1, 1, data[0], out);
	}

	fclose(as);
	fclose(out);

	exit(EXIT_SUCCESS);
}

static void convert(char* str, uint8_t* buf) {
	if (starts_with(str, "nop")) {
		buf[0] = 0x01;
		buf[1] = 0x00;
	} else if (starts_with(str, "prnt")) {
		buf[0] = 0x01;
		buf[1] = 0x01;
	} else if (starts_with(str, "exit")) {
		buf[0] = 0x01;
		buf[1] = 0x02;
	} else {
		fprintf(stderr, "unknown opcode! (%s)", str);
		exit(EXIT_FAILURE);
	}
}

static bool starts_with(const char* item, const char* match) {
	uint32_t i = 0;
	while (match[i] != 0) {
		if (item[i] == 0 || item[i] != match[i])
			return false;
		++i;
	}
	return true;
}
