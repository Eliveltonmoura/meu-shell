# Makefile para o shell sh238p
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -g
TARGET = sh238p
SRC = sh238p.c
ZIPNAME = homework2.zip

.PHONY: all clean run zip

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	-rm -f $(TARGET) *.o

zip: $(SRC)
	@rm -f $(ZIPNAME)
	@zip -r $(ZIPNAME) $(SRC)
	@echo "Criado $(ZIPNAME) contendo $(SRC)"
