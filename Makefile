CC=gcc
CFLAGS=-O3

build:
	$(CC) -o otp otp.c $(CFLAGS)

.PHONY : clean
clean:
	rm *.o