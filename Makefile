CC = g++
CFLAGS = -Wall -Werror -Wextra -o

run:
	$(CC) $(CFLAGS) main main.cpp

clean:
	rm -rf main