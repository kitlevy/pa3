FLAGS = -Wall -Werror -std=c99

all: fp_analyzer_f fp_analyzer_d

fp_analyzer_f: fp_analyzer.c main.c
	gcc ${FLAGS} $^ -o $@

fp_analyzer_d: fp_analyzer.c main.c
	gcc ${FLAGS} -DDOUBLE $^ -o $@

clean:
	rm fp_analyzer_f fp_analyzer_d
