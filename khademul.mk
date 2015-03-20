CC = g++

CFLAGS = -Wall

all: khademul

khademul: khademul.cpp 
	${CC} ${CFLAGS} khademul.cpp -o khademul

clean:
	rm -rf \
	khademul