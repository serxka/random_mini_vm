/*
 * opcode length is 16 bits, or 2 bytes
 * there are two registers, the ip and sp, they are 12 bits large.
 *
 *
 * x = ignored
 * N = operand
 * 0x xx : CON = just go to the next instruction
 * 1x xx : ADD = pop two top values on the stack and add them together
 * 2x xx : SUB = pop two values and subtract them and push onto stack, %sp[-1] - %sp[-2]
 * 3N NN : PUSH = push a byte onto the stack
 * AN NN : JMP = set the ip to a value from 0 - 4096
 * Bx xx : PRNT = pop the top value and print it
 * 
 * Fx xx : HALT = halt the cpu
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define exit_perror(x) {perror(x); exit (-1);}

int run (const uint8_t *program);

int main (int argc, char *argv[])
{
	// check we have a file
	if (argc < 2) {
		fprintf(stderr, "Usage: vm [FILE]\n");
		exit (-1);
	}
	
	// open the file
	FILE *fd = fopen(argv[1], "r");
	if (!fd)
		exit_perror ("Error loading program file");
		
	// read the file
	// first get the length of the file
	if (fseek (fd, 0, SEEK_END))
		exit_perror ("Failed to seek file");
	unsigned int program_length = ftell (fd);
	if (fseek (fd, 0, SEEK_SET))
		exit_perror ("Failed to seek file");
	// then calloc
	uint8_t *program_buffer = calloc (program_length, 1);
	if (!program_buffer)
		exit_perror ("Failed to calloc file buffer");
	// then fread
	if (!fread(program_buffer, 1, program_length, fd))
		exit_perror ("Failed to read file");
	// close the file
	fclose (fd);

	// run the file
	int result = run (program_buffer);

	// clean up
	free (program_buffer);

	// exit
	exit (result);
}

// an instruction nicly encoded
typedef struct intruction_struct {
	uint16_t opcode:		 4;
	uint16_t operand:		12;
} instruction_t;

// populate a instruction_t
static inline instruction_t encode_instruction (const uint8_t *value) {
	instruction_t temp;
	temp.opcode = (*value) >> 4;
	temp.operand = (*(value+1)) & 0xFF;
	temp.operand |= (*value) & 0x0F;
	return temp;
}

// opcode enum for readabilty
enum opcodes {
	CON = 0x0,
	ADD = 0x1,
	SUB = 0x2,
	PUSH = 0x3,
	JMP = 0xA,
	PRNT = 0xB,
	HALT = 0xF,
};

//  runs the programme
int run (const uint8_t *program) 
{

	uint16_t ip = 0, sp = 0;
	uint8_t stack[4096];
	for (;;) 
	{
		instruction_t in = encode_instruction (program+(2*ip));
		
		//printf("opcode: 0x%X operand: 0x%X\nsp: %d ip: %d\n\n",  in.opcode, in.operand, sp, ip);
	
		switch (in.opcode)
		{
			case CON: {
				break;
				}
			case ADD: {
				uint8_t result = stack[sp-1] + stack[sp-2];
				stack[--sp] = result;
				break;
				}
			case SUB: {
				uint8_t result = stack[sp-1] - stack[sp-2];
				stack[--sp] = result;
				break;
				}
			case PUSH: {
				stack[sp++] = in.operand;
				break;
				}
			case JMP: {
				ip = in.operand;
				break;
				}
			case PRNT: {
				printf("%c\n", stack[sp--]);
				break;
				}
			case HALT: {
				return 0;
			}
			default: { // invalid opcode
				return -1;
			}
		}
		++ip;
	}
}