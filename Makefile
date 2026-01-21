CMD = gcc
SRC = main.c text/text.c sdl-util/sdl-util.c
OBJ = $(SRC:.c=.o)
INC = -I .
FLG = `pkg-config --cflags --libs sdl3`
OUT = txt

all : ${OBJ}
	${CMD} $^ ${INC} ${FLG} -Wall -pedantic -Wextra -o ${OUT}

${OBJ} : %.o: %.c
	${CMD} ${INC} ${FLG} -Wall -pedantic -Wextra -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm ${OUT}
