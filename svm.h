#ifndef SVM_H
#define SVM_H

// STANDARD HEADERS
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// SYSTEM HEADERS
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

// CONSTANT VALUES
#define VM_ADDR_LIMIT (1u << 16)

// STRUCTURES
struct registers {
	uint16_t pc, sp; // Programme counter, stack pointer
	uint16_t ac, id; // Accumulator, index
	uint16_t r0, r1, r2, r3; // General purpose register 1-4
};

struct programme {
	uint8_t *mem; // 2^16, heap allocated
	struct registers regs;
};

// FUNCTION PROTOTYPES
uint8_t *load_file(const char *fname);
void run(struct programme prog);

#endif // SVM_H
