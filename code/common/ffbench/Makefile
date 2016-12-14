
#   Options for compiling and linking C fbench programs

COPTS = -O3 -lm

PROGRAMS = ffbench

all:	$(PROGRAMS)

ffbench: ffbench.c
	cc ffbench.c -o ffbench $(COPTS)

clean:
	rm -f $(PROGRAMS) *.o *.out core*
