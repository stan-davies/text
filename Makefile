CMD = gcc
SRC = main.c text/text.c
OBJ = $(SRC:.c=.o)
INC = -I .
# FLG = `sdl2-config --cflags --libs`
FLG = 
OUT = txt

all : ${OBJ}
	${CMD} $^ ${INC} ${FLG} -Wall -pedantic -Wextra -o ${OUT}

${OBJ} : %.o: %.c
	${CMD} ${INC} ${FLG} -Wall -pedantic -Wextra -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm ${OUT}
