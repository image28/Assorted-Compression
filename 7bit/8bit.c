// 8bit, 7bit Text Decoder
// By Kevin Macey

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "bitfile-0.4/bitfile.h"

#include "defines.h"

MAIN;
	ARG_CHECK(1);
	OUTPUT_FILE;

	bit_file_t *input;

	OUTFILE(".8bit");
	FILES;


	UINT bitpos=0;
	UCHAR buffer[64];
	UCHAR binary[8];
	UINT e=0;

	input= BitFileOpen(argv[1],BF_READ);
	if ( ( output=fopen(outfile,"w") ) == NULL ) exit(-2);

	while ( BitFileGetBits(input,&outbyte,7) != EOF )
	{
			outbyte >>= 1;

			// write
			WRITE;			

	END;
			

	BitFileClose(input);
	CLOSE(output);
	
	RET;
END;
