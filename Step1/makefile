# cphex\makefile

LIBS=
all:	admin	LibSerMP.o


LibSerMP.o:	LibSerMP.c	LibSerMP.h	data.h	
			echo "Compilation de LibSerMP"
			gcc -c LibSerMP.c

admin:	data.h	admin.c	LibSerMP.o			
		echo "Compilation de admin"
		gcc -o admin	admin.c	LibSerMP.o 


clean:
	rm -f *.o core o

clobber:	clean
	rm admin