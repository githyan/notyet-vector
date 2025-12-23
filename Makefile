CC = cc
CFLAGS = -pedantic -Wall -Wno-deprecated-declarations -Os -g -fsanitize=address
TARGET = vector
SRC = main.c vector.c
OBJ = ${SRC:.c=.o}
VFLAGS = --leak-check=full --show-leak-kinds=all

all: $(TARGET)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	./$(TARGET)

valgrind:
	${CC} -g ${SRC} -o ${TARGET}
	valgrind ${VFLAGS} ./${TARGET}

# all:
# 	${CC} -o ${TARGET} ${OBJ}
#
# .c.o:
# 	${CC} -c ${CFLAGS} $<

# vector: ${OBJ}
	# ${CC} -o $@ ${OBJ}


clean:
	rm -rf $(TARGET) ${OBJ}

.PHONY: $(TARGET) all clean valgrind
