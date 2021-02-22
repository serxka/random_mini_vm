#include "svm.h"

static int verify(struct programme *prog);
static uint8_t interp(struct programme prog);

void run(struct programme prog) {
	if(!verify(&prog)) {
		fprintf(stderr, "failed to verify that all opcodes are valid!");
		exit(EXIT_FAILURE);
	}

	interp(prog);
}

// Go through and check the validity of op codes
static int verify(struct programme *prog) {
	// no hahahahaha
}

static inline uint8_t op_len(uint8_t op);

// Interpret the programme
static uint8_t interp(struct programme prog) {
	const static void *op_table[] = { &&op_nop, &&op_print, &&op_end };

	uint8_t *mem = prog.mem;
	uint16_t pc = prog.regs.pc;
	uint8_t op = mem[pc];

	#define DISPATCH_OP() goto *op_table[op]
	#define INC_PC() op = mem[pc += op_len(op)]

	///////////////////////////////////////////
	// INTERPRETER BEGIN
	DISPATCH_OP();
	op_nop:
		INC_PC();
		DISPATCH_OP();
	op_print:
		printf("gamer!\n");
		INC_PC();
		DISPATCH_OP();
	op_end:
		goto exit;
	// INTERPRETER END
	///////////////////////////////////////////


	exit:
		return 0;
}

// takes the opcode and return the amount for pc to be increased
static inline uint8_t op_len(uint8_t op) {
	return (op & 0xC0) ? 2 : 1; // is long op
}
