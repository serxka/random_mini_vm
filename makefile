OUTPUT=svm
OBJ=main.o load.o vm.o

CFLAGS=-Wall -Wextra
LDFLAGS=

.PHONY: all clean

all: ${OUTPUT}

${OUTPUT}: ${OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} -o ${OUTPUT} $^

as: assembler.o
	${CC} ${CFLAGS} -o $@ $^

# Clean build files
clean:
	rm -f ${OBJ}
	rm -f ${OUTPUT}
	rm -f as
	rm -f assembler.o
	