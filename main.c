#include "svm.h"

int main (int argc, char **argv) {
	// Check we have a file to load
	if (argc < 2) {
		fprintf(stderr, "Usage: svm [FILE]\n");
		exit (EXIT_FAILURE);
	}

	// Load the programme
	struct programme prog = {0};
	prog.mem = load_file(argv[1]);

	// Run the programmme
	run(prog);

	exit(EXIT_SUCCESS);
}
