SOURCES=$(wildcard src/*.c)
REQUIREMENTS=$(patsubst %.h, %.c, $(wildcard src/*/src/*.h))
OBJECTS=$(patsubst %.c, objs/%.o, $(SOURCES) $(REQUIREMENTS))
TARGET=objs/which

CC=gcc -c -g -O2 -Wall -Wextra -I=src
LINK=gcc -o

$(TARGET): build compile link

build:
	mkdir -p $(dir $(OBJECTS))

compile: $(OBJECTS)

objs/src/%.o: src/%.c
	$(CC) -o $@ $<

link:
	$(LINK) $(TARGET) $(OBJECTS)

clean:
	rm -rf objs/

.PHONY: build compile link clean
