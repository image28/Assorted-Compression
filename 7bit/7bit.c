// 7bit Text Compressor
// By Kevin Macey

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "defines.h"
#include "bitfile-0.4/bitfile.h"

MAIN;
	ARG_CHECK(1);

	INPUT_FILE;
	bit_file_t *output;
	OUTFILE(".7bit");

	UINT outbyte=0;
	UINT inbyte=0;

	ULONG filesize=0;
	ULONG position=0;

	UINT d=0;
	UCHAR bin[8];
	UCHAR buffer[32];
	UINT bitpos=0;

	if ( ( input=fopen(argv[1],"r") ) == NULL ) exit(-1);
	output = BitFileOpen(outfile,BF_WRITE);

	FILESIZE;

	while ( position < filesize )
	{
		bin[0]='\0'; outbyte='\0';
		READ;

		inbyte <<= 1;

		BitFilePutBits(output,&inbyte,7);

		// write last bit to output 2
		position++;
	END;

	CLOSE(input);
	BitFileClose(output);

	RET;
END;
