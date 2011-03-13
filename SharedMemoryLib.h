#ifdef __MSC_VER

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H


// ------------------------------------------------------
// SharedMemoryLib.h
// Shared memory functions HEADERS
// ------------------------------------------------------

void CreateSharedMemoryArea(void);
void OpenSharedMemory(void);
void DestroySharedMemoryArea (void);
void WriteOnSharedMemory(int data, int position);
void ReadFromSharedMemory(int *data, int position);
#endif
#endif
