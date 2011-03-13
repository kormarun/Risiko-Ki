#ifdef __MSC_VER

// ------------------------------------------------------
// Shared memory functions
// Sample file to creat a Shared Memory area...
// Author: Marcio Serolli Pinho
// ------------------------------------------------------

//#include <stdafx.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>


#include "SharedMemoryLib.h"

HANDLE hFile;
LPINT hView, aux;     

//--------------------------------------------------------
//
//
//
//--------------------------------------------------------
void CreateSharedMemoryArea()
{

	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, 
		NULL,
		PAGE_READWRITE, 
		0, 
		1024 * 4, 
		"ALongFileName");
	if (hFile == NULL)
	{
		 printf("SHARE MEMORY LIB: Unable to create a file.");
		 exit(1);
	}

	hView = (LPINT) MapViewOfFile(hFile, 
		FILE_MAP_ALL_ACCESS,  
		0,
		0,
		0);
	if (hView == NULL)
	{
		 printf("Unable to create a VIEW.");
		 exit(1);
	}
	printf("SHARE MEMORY LIB: Shared memory has been successfully created....\n");

	aux = hView;

}    
//--------------------------------------------------------
//
//
//
//--------------------------------------------------------
void OpenSharedMemory()
{
   hFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, 
		FALSE,
		"ALongFileName");            
	if (hFile == NULL)
	{
		 printf("SHARE MEMORY LIB: Unable to open the shared area.\n");
		 exit(1);
	}

	hView = (LPINT) MapViewOfFile(hFile, 
		FILE_MAP_ALL_ACCESS, //FILE_MAP_WRITE | FILE_MAP_READ, 
		0,
		0,
		0);
	if (hView == NULL)
	{
		 printf("SHARE MEMORY LIB: Unable to create a VIEW.\n");
		 exit(1);
	}
	printf("SHARE MEMORY LIB: Shared memory has been successfully openned....\n");

	aux = hView;
}
//--------------------------------------------------------
//
//
//
//--------------------------------------------------------
void DestroySharedMemoryArea ()
{

	if (!UnmapViewOfFile(hView)) 
	{ 
       printf("Could not unmap view of file."); 
	} 
	
	CloseHandle(hFile); 
    
	printf("SHARE MEMORY LIB: Shared memory has been successfully destroyed....\n");

	printf("The end.\n");
}
//--------------------------------------------------------
//
//
//
//--------------------------------------------------------
void WriteOnSharedMemory(int data, int position)
{
//	printf("Writing data on the shared area...\n");
	aux[position] = data;
}

//--------------------------------------------------------
//
//
//
//--------------------------------------------------------
void ReadFromSharedMemory(int *data, int position)
{
//	printf("Reading data on the shared area...\n");
	*data = aux[position];
}
#endif
