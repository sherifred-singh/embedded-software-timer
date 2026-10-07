CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude -O2
SRC = src/soft_timer.c tests/test_timer.c
TARGET = test_timer

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o *.exe
