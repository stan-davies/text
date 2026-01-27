CMD = gcc
SRC = main.c text/text.c sdl-util/sdl-util.c rend/rend.c font/font.c cycl/cycl.c logw/logw.c keys/keys.c font/writer/writer.c
OBJ = $(SRC:.c=.o)
INC = -I .
FLG = `pkg-config --cflags --libs sdl3 sdl3-ttf`
OUT = txt

all : ${OBJ}
	${CMD} $^ ${INC} ${FLG} -Wall -pedantic -Wextra -o ${OUT}

${OBJ} : %.o: %.c
	${CMD} ${INC} ${FLG} -Wall -pedantic -Wextra -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm ${OUT}
