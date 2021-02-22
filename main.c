#include "svm.h"

static uint8_t *load_file(const char *fname);

int main(int argc, char *argv[]) {
	// Check we have a file to load
	if (argc < 2) {
		fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Load the programme
	struct programme prog = {0};
	prog.mem = load_file(argv[1]);

	// Run the programmme
	run(prog);

	exit(EXIT_SUCCESS);
}

static uint8_t *load_file(const char *fname) {
	// Open the binary programme and get it's size
	int bin_fd = open(fname, O_RDONLY);
	if (bin_fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	struct stat s;
	fstat(bin_fd, &s);

	// Create the VM memory
	uint8_t *mem = calloc(VM_ADDR_LIMIT, sizeof(uint8_t));
	if (mem == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	// Read the programme into start of VM memory
	size_t amount_to_read = MIN(s.st_size, VM_ADDR_LIMIT);
	ssize_t num = read(bin_fd, mem, amount_to_read);
	if (num < 0 || num != amount_to_read) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	close(bin_fd);

	return mem;
}
