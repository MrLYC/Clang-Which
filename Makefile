SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst %.c, objs/%.o, $(SOURCES))
TARGET=objs/which

CC=gcc -c -g -O2 -Wall -Wextra -I=src
LINK=gcc -o

$(TARGET): build compile link

build:
	mkdir -p objs/src/

compile: $(OBJECTS)

objs/src/%.o: src/%.c
	$(CC) -o $@ $<

link:
	$(LINK) $(TARGET) $(OBJECTS)

.PHONY: build compile link
