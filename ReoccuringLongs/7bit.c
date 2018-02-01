 // Compresses a File 
// By Kevin Macey

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "defines.h"
#include "pack.h"

int compress(UCHAR infile[MAX]); // , UCHAR outfile[MAX]);
int unused_bytecodes(char filename[MAX],UINT *bytecodes);

typedef struct number 
{
	ULONG number;
	UINT repeat;
	UINT unused;
}test1;

typedef struct writenum
{
	UINT unused;
	ULONG number;
};

MAIN;
	ARGCHECK(1);

	compress(argv[1]); //,argv[1]); //,"empty");

	RET;
END;

int compress(UCHAR infile[MAX])// , UCHAR outfile[MAX])
{

	// FILE VARABLES
	INPUT_FILE;
	OUTPUT_FILE;
	FILE *output2;

	// VARABLES
	ULONG inbyte=0;
	ULONG insize=0;
	ULONG filesize=0;
	ULONG count=0;
	struct number list[65535];
	struct writenum out[65535];
	ULONG pos=0;
	ULONG listpos=0;
	UINT done=0;
//	UINT intcodes=0;
	UINT outint=0;
	UINT unused[65535];
	UINT unused_total=0;

	UINT records;

	UCHAR outfile2[MAX];
	strcpy(outfile2,"temp");

	UCHAR outfile[MAX];
	strcpy(outfile,"temp2");

	UCHAR final[MAX];
	strcpy(final,infile);
	strcat(final,".comp");

	// OPEN FILES
	FOI(infile);
	FOO(outfile);
	output2=fopen(outfile2,"w");

	FILESIZE;

	insize=filesize;


	// change - added unused total 

	// get all unused int codes
	unused_total=unused_bytecodes(infile, &unused);

	// move unused into list
	while ( count < unused_total )
	{
		list[count].unused = unused[count];
		count++;
	}

	printf("%d\n",unused_total);

	// MAIN LOOP
	while ( ! feof(input) ) // position != filesize )
	{
		inbyte=0; 
		// READ AN INT INTO BUFFER
		fread(&inbyte,4,1,input);

		// Find out if it is in the list already
		while ( ( pos < listpos ) && ( ! done ) )
		{
	

			if ( inbyte == list[pos].number )
			{
				//xfxprintf("%d Repeats %d times\n", inbyte, list[pos].repeat);
				list[pos].repeat++;
				// set byte to unused bytecode
				done=1;
			}
			pos++;
		}pos=0;

		// if not found in list
		if ( ! done )
		{
		//	printf("Added: %d\n", inbyte);
			list[listpos].number = inbyte;
			list[listpos].repeat++;
			
			
			// add to list
			listpos++;

		}done=0;

	END;

	RESET;

	FILELOOP;
		fread(&inbyte,4,1,input);

		count=0;done=0;

		while ( ( count < listpos ) && ( ! done ) )
		{
			// if == repeat > amount
			if ( ( list[count].repeat > 5 ) && ( list[count].number == inbyte ) )
			{
				// switch with unused bytecode
				outint=list[count].unused;
				done=1;

			}

			// If unused runs out send error message
			if ( count == unused_total )
			{
				printf("Unused Varables have run out\n");
			}
			// maybe sort numbers that reoccur more as a priority

			count++;

		}

		if ( done )
		{
			// write two bytes
			fwrite(&outint,2,1,output);
		}else{
			// write 4 bytes
			fwrite(&inbyte,4,1,output);
		}


	END;

	count=0;

	while ( count < listpos )
	{
	
		if ( list[count].repeat >= 5 )
		{
			//printf("%d repeated %d times\n",list[count].number, list[count].repeat);

			filesize=filesize - ( list[count].repeat * 2 - 6) ;
			out[count].unused = list[count].unused;
			out[count].number = list[count].number;
			records++;
		}

		count++;
	}

	fwrite(&out,sizeof(struct writenum),records,output2);

//	printf("\n\nOriginal Size: %d\nOutput Size: %d\n", insize, filesize);

	CLOSE(input);
	CLOSE(output);
	CLOSE(output2);

	// Pack to outputs
	pack(outfile,outfile2,final);

	RET;

END;


// FIND ALL UNUSED BYTECODES(INTS) IN A FILE
int unused_bytecodes(char filename[MAX], UINT *unused)
{
	INPUT_FILE;
	UCHAR inbyte;
	UINT bytecode[65535];
	UINT d=0;
	UINT count=0;

	input=fopen(filename,"r") ;

	FILELOOP;
		READ;
		bytecode[inbyte]++;
	END;

	CLOSE(input);

//	printf("UNUSED BYTECODES\n-----------------------\n\n");

	while ( d < 65535 ) 
	{
		if ( bytecode[d] == 0 )
		{
			*(unused+d)=d;
			count++;
//			printf("%d, ",d);
		}
		d++;
	}
//	EL;EL;
	*(unused+d)='\0';

	// return unused null terminated

	return(count);
END;
