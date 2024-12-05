CC = gcc
CFLAGS = -Iinclude -Wall
LDFLAGS = -lqrencode -ldmtx

SRC = src/qrcode.c src/datamatrix.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ) main.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) main.o $(EXEC)

.PHONY: all clean
