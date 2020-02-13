.PHONY: all clean

all: vm hex2bin

vm: vm.c
	cc -g -o $@ $<

hex2bin: hex2bin.c
	cc -g -o $@ $<
	
clean:
	rm -f hex2bin
	rm -f vm