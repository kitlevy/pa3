APP = fp_analyzer
CC = gcc
FLAGS = -Wall -Werror -std=c99

all:${APP}_f ${APP}_d

${APP}_f: ${APP}.c main.c
	${CC} ${FLAGS} $^ -o $@

${APP}_d: ${APP}.c main.c
	${CC} ${FLAGS} -DDOUBLE $^ -o $@

clean:
	rm ${APP}_f ${APP}_d
