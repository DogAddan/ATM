all:
	gcc -std=gnu99 -Wall -c server.c
	gcc -std=gnu99 -Wall -c tools.c
	gcc -std=gnu99 -Wall -c creacc.c
	gcc -std=gnu99 -Wall -c destory.c
	gcc -std=gnu99 -Wall -c load.c
	gcc -std=gnu99 -Wall -c ulock.c
	gcc -std=gnu99 -Wall -c deposit.c
	gcc -std=gnu99 -Wall -c draw.c
	gcc -std=gnu99 -Wall -c trans.c
	gcc -std=gnu99 -Wall -c query.c
	gcc -std=gnu99 -Wall -c modi.c
	gcc -std=gnu99 -Wall -c main.c
	gcc -std=gnu99 server.o creacc.o destory.o load.o ulock.o deposit.o draw.o  trans.o query.o modi.o main.o tools.o -lpthread -o server
