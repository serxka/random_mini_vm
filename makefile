OBJS=main.o svm.o

CFLAGS=-g

.PHONY: all clean

all: svm

svm: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS}

as: assembler.o
	${CC} ${CFLAGS} -o $@ assembler.o


%.o: %.c
	${CC} ${CFLAGS} -c -MD -o $@ $<

clean:
	rm -f $(shell find . -name "*.d") $(shell find . -name "*.o") as svm
