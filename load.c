#include "svm.h"

uint8_t *load_file(const char *fname) {
	// Open the binary programme
	int bin_fd = open(fname, O_RDONLY);
	if (bin_fd < 0) {
		perror("Opening file");
		exit(EXIT_FAILURE);
	}
	// Get file infomation (file size)
	struct stat s;
	fstat(bin_fd, &s);

	// Map file into memory
	uint8_t *bin = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, bin_fd, 0);
	if (bin == MAP_FAILED) {
		perror("Mapping file");
		exit(EXIT_FAILURE);
	}

	// Create the VM memory
	uint8_t *mem = calloc(VM_ADDR_LIMIT, sizeof(uint8_t));
	if (mem == NULL) {
		perror("Calloc");
		exit(EXIT_FAILURE);
	}

	// Copy the mapped programme into start of VM memory
	memcpy(mem, bin, s.st_size);

	// Close file and mmap
	munmap(bin, s.st_size);
	close(bin_fd);

	return mem;
}
