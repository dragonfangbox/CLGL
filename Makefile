CC=gcc

TARGET=main.c
TARGETNAME=main

compile: $(TARGET)
	$(CC) -g -Wall -o $(TARGETNAME)  $(TARGET) src/window.c src/LL.c -Isrc
