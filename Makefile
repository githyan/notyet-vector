CC = cc
CFLAGS = -pedantic -Wall -Wno-deprecated-declarations -Os 
CDEBUGS = -g -fsanitize=address
TARGET = vector
SRC = main.c vector.c
OBJ = ${SRC:.c=.o}
VFLAGS = --leak-check=full --show-leak-kinds=all

TESTFLAGS = -fprofile-arcs -ftest-coverage
TEST_SRC = unittest/test.c vector.c
TEST_OBJ = test test-test.gcno test-vector.gcno

all: $(TARGET)
	$(CC) $(CFLAGS) $(CDEBUGS) $(SRC) -o $(TARGET)
	./$(TARGET)

valgrind:
	${CC} -g ${SRC} -o ${TARGET}
	valgrind ${VFLAGS} ./${TARGET}

build_test: unittest/test.c vector.c
	$(CC) -Os -g $(TESTFLAGS) -o test $(TEST_SRC)

test: build_test
	./test
	gcov -c -p test-counter
# all:
# 	${CC} -o ${TARGET} ${OBJ}
#
# .c.o:
# 	${CC} -c ${CFLAGS} $<

# vector: ${OBJ}
	# ${CC} -o $@ ${OBJ}


clean:
	rm -rf $(TARGET) ${OBJ} $(TEST_OBJ)

.PHONY: $(TARGET) all clean valgrind test
