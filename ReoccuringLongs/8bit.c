// Decompresses the 01 and 7bit file
// By Kevin Macey

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "defines.h"
#include "pack.h"

// predefine
int decompress(UCHAR infile[MAX], UCHAR outfile[MAX]);

typedef struct number
{
	UINT number;
	ULONG replong;
};

// PROGRAM MAIN
MAIN;
	// ARGUMENT CHECK
	ARGCHECK(1);

	// run recursive decompress of file
	decompress(argv[1], argv[2]);

	// run unpack on file
	// unpack(argv[1]);

	RET;
END;


int decompress(UCHAR infile[MAX], UCHAR outfile[MAX])
{
	// FILE VARABLES
	OUTPUT_FILE;
	INPUT_FILE;
	FILE *input2;
	
	strcpy(outfile, infile);
	outfile[strlen(outfile)-5]='\0';
	strcat(outfile,".decomp");

	struct number unused[65535];
	UINT records=0;
	UINT inint=0;
	ULONG inlong=0;
	UINT number=0;
	UINT done=0;



	FILES;
	
	// VARABLES	
	UINT zero=0;
	UINT count=0;

	// unpack
	unpack(infile);

	// OPEN THE FILES
	input2=fopen("temp2","r");
	input=fopen("temp1","r");
	FOO(outfile);

	// Read in unused bytecode table
	while ( ! feof(input2) )
	{
		// read one record
		fread(&unused[records],sizeof(number),1,input2);
		records++;
	}

	// MAIN FILE LOOP
	FILELOOP;
		// read in an int
		fread(&inint,2,1,input);

		// if unused bytecode in table
		while ( ( count < records ) || ( ! done ) )
		{
			if ( inint == unused[count].number )
				done=1;

			count++;
		}

		if ( done )
		{
			fwrite(&unused[count-1].replong,4,1,output);
		}else{
		// if an unused bytecode
			// write the long 
		// if not an unused byte
			// read next 2 bytes
			fseek(input,-2,SEEK_CUR);
			fread(&inlong,4,1,input);
			// write the long
			fwrite(&inlong,4,1,output);
		}

		END;

	// CLOSE ALL FILES
	CLOSE(input);
	CLOSE(output);
	CLOSE(input2);

	RET;
END;

