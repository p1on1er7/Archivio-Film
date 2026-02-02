CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude
SRC=src/main.c src/studente1.c src/studente2.c src/studente3.c
OUT=film

all: $(OUT)

$(OUT): $(SRC)
    $(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
    rm -f $(OUT)
