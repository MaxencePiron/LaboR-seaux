# cphex\makefile

LIBS=
all: admin cli ser udplib.o LibSerMP.o

LibSerMP.o: LibSerMP.c LibSerMP.h data.h
	echo "compilation de LibSerMP"
	cc -c LibSerMP.c

admin: data.h admin.c LibSerMP.o
	echo "Compilation de admin"
	cc -o admin admin.c LibSerMP.o

udplib.o: ../udplib/udplib.h ../udplib/udplib.c
	echo "Compilation de udplib.o"
	cc -c ../udplib/udplib.c

cli: cli.c RequeteMP.h data.h udplib.o
	echo "Compilation de client"
	cc -o cli cli.c udplib.o $(LIBS)

ser: ser.c RequeteMP.h data.h udplib.o LibSerMP.o
	echo "Compilation de serveur"
	cc -o ser ser.c udplib.o LibSerMP.o $(LIBS)


clean:
	rm -f *.o core o

clobber:	clean
	rm admin