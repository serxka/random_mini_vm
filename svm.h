#ifndef SVM_H
#define SVM_H

// STANDARD HEADERS
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SYSTEM HEADERS
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// MACROS
#define MIN(x, y) ((x) < (y) ? (x) : (y))

// CONSTANT VALUES
#define VM_ADDR_LIMIT (1u << 16)

// STRUCTURES
struct registers {
	uint16_t pc, sp; // Programme counter, stack pointer
	uint16_t flags; // Flags and shit
	uint16_t r0, r1, r2, r3, r4, rnil; // General purpose registers 0-4 and nil
};

struct programme {
	uint8_t *mem; // 2^16
	struct registers regs;
};

// FUNCTION PROTOTYPES
void run(struct programme prog);

#endif // SVM_H
