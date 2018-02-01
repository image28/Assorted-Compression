############################################################################
# Makefile for bitfile/bitfile library and sample
#
#   $Id: Makefile,v 1.1.1.1 2004/02/09 05:31:42 michael Exp $
#   $Log: Makefile,v $
#   Revision 1.1.1.1  2004/02/09 05:31:42  michael
#   Initial release
#
############################################################################

# removed window linux select, and switched sample with mini7bit

CC = c:\mingw\bin\gcc
LD = c:\mingw\bin\gcc
CFLAGS = -O3 -funsigned-char -march=pentium4 -Wall -g -c 
LDFLAGS = -O3 -g -o

all: 7bit.o 7bit.exe 8bit.o 8bit.exe pack.o

7bit.exe: 7bit.o pack.o
	$(LD) $^ $(LDFLAGS) $@

7bit.o: 7bit.c 
	$(CC) $(CFLAGS)$<

8bit.exe: 8bit.o pack.o 
	$(LD) $^ $(LDFLAGS) $@

8bit.o: 8bit.c 
	$(CC) $(CFLAGS)$<

pack.o: pack.c
	$(CC) $(CFLAGS)$<

clean:
		del *.o
		del *.exe
		del ERRORS.TXT
		del *.7bit
		del *.8bit
		del *.01
		del *.decompressed
		del OUT*
		del *.pack

