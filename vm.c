#include "svm.h"

void run(struct programme prog) {
	for (int i = 0; i < VM_ADDR_LIMIT; ++i)
		putchar(prog.mem[i]);
}
