CC=gcc

TARGET=main.c
TARGETNAME=main

compile: $(TARGET)
	$(CC) -Wall -o $(TARGETNAME)  $(TARGET) src/window.c -Isrc
