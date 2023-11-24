# cphex\makefile

LIBS=
all:	cli	ser	udplib.o

udplib.o:	../udplib/udplib.h	../udplib/udplib.c
	echo "Compilation de udplib.o"
	gcc -c ../udplib/udplib.c	

cli:	cli.c	udplib.o
	echo "Compilation de client"
	gcc  -o cli  cli.c udplib.o	$(LIBS)

ser:	ser.c	udplib.o
	echo "Compilation de serveur"
	gcc -o ser  ser.c udplib.o	$(LIBS)

