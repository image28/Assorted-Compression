#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "defines.h"

int pack(UCHAR file1[MAX], UCHAR file2[MAX], UCHAR outfile[MAX])
{

	// VARABLES
	INPUT_FILE;
	FILE *input2;
	OUTPUT_FILE;
	FILES;

	ULONG count=0;
	UCHAR unused='\0';

	// OPEN THE FILES
	FOI(file1);
	input2= fopen(file2,"rb");
	FOO(outfile);

	ULONG filesize=0;
	FILESIZE;

	// get filesize of input 
	fwrite(&filesize,4,1,output);

	// FIRST FILE LOOP
	while ( ! feof(input) )
	{
		inbyte='\0';
		READ;
		outbyte=inbyte;
		WRITE;
	}

	// SECOND FILE LOOP
	while ( ! feof(input2) )
	{
		inbyte='\0';
		fread(&inbyte,1,1,input2);
		outbyte=inbyte;
		WRITE;
	}


	// CLOSE ALL FILES
	CLOSE(input);
	CLOSE(input2);
	CLOSE(output);

	RET;
END;


int unpack(UCHAR filename[MAX])
{
	// VARABLES
	INPUT_FILE;
	OUTPUT_FILE;
	FILES;
	UCHAR unused='\0';
	inbyte='\0';

	ULONG filesize=0;
	ULONG pos=0;

	// Setup outfile and outfile2 names
	UCHAR outfile[MAX];
	UCHAR outfile2[MAX];
	strcpy(outfile,"temp1");
	strcpy(outfile2,"temp2");

	ULONG count=0;

	// OPEN ALL FILES
	if ( ( input = fopen(filename,"rb") ) == NULL ) exit(-1);
	if ( ( output = fopen(outfile,"wb") ) == NULL ) exit(-2);

	// read filssize
	fread(&filesize,4,1,input);

	// READ FIRST FILE IN PACKAGE
	while ( pos <= filesize )
	{
		inbyte='\0';
		READ;
		outbyte=inbyte;
		WRITE;
		pos++;
	}

	// OPEN NEXT OUTPUT FILE
	CLOSE(output);
	output= fopen(outfile2,"wb");
	
	// wierd black space bug

	while ( ! feof(input) )
	{
		inbyte='\0';
		READ;
		outbyte=inbyte;
		WRITE;
	}


	// CLOSE ALL FILES
	CLOSE(input);
	CLOSE(output);

	RET;
END;
