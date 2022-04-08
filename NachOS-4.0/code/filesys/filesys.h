// filesys.h
//	Data structures to represent the Nachos file system.
//
//	A file system is a set of files stored on disk, organized
//	into directories.  Operations on the file system have to
//	do with "naming" -- creating, opening, and deleting files,
//	given a textual file name.  Operations on an individual
//	"open" file (read, write, close) are to be found in the OpenFile
//	class (openfile.h).
//
//	We define two separate implementations of the file system.
//	The "STUB" version just re-defines the Nachos file system
//	operations as operations on the native UNIX file system on the machine
//	running the Nachos simulation.
//
//	The other version is a "real" file system, built on top of
//	a disk simulator.  The disk is simulated using the native UNIX
//	file system (in a file named "DISK").
//
//	In the "real" implementation, there are two key data structures used
//	in the file system.  There is a single "root" directory, listing
//	all of the files in the file system; unlike UNIX, the baseline
//	system does not provide a hierarchical directory structure.
//	In addition, there is a bitmap for allocating
//	disk sectors.  Both the root directory and the bitmap are themselves
//	stored as files in the Nachos file system -- this causes an interesting
//	bootstrap problem when the simulated disk is initialized.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef FS_H
#define FS_H

#include "copyright.h"
#include "sysdep.h"
#include "openfile.h"

const int MAX_OPEN_FILES = 256;
class FileSystem
{
private:
	OpenFile **fileTable;
public:
	FileSystem() {
		fileTable = new OpenFile*[MAX_OPEN_FILES];
	}

	~FileSystem() {
		delete[] fileTable;
	}

	bool Create(char *name)
	{
		int fileDescriptor = OpenForWrite(name);

		if (fileDescriptor == -1)
			return -1;
		Close(fileDescriptor);
		return 0;
	}

	int OpenFileID(char *name)
	{
		int fileDescriptor = OpenForReadWrite(name, FALSE);
		if (fileDescriptor == -1)
			return -1;

		for (int i = 2;i<MAX_OPEN_FILES; i++)
			if(fileTable[i]==NULL) {
			 	fileTable[i]= new OpenFile(fileDescriptor, name);
				return i;
			}
		return -1;
	}
	OpenFile *Open(char *name)
	{
		int fileDescriptor = OpenForReadWrite(name, FALSE);

		if (fileDescriptor == -1)
			return NULL;
		return new OpenFile(fileDescriptor);
	}
	int Close(int id){
		if(fileTable[id]!=NULL){
			delete fileTable[id];
			fileTable[id] = NULL;
			return 1;
		}
		return -1;
	}
	int Read(char *buffer, int size, int fileId) {
		if (fileId < 0 || fileId >= MAX_OPEN_FILES || fileTable[fileId] == NULL) {
			return -1;
		}

		return fileTable[fileId]->Read(buffer, size);
	}

	int Write(char *buffer, int size, int fileId) {
		if (fileId < 0 || fileId >= MAX_OPEN_FILES || fileTable[fileId] == NULL) {
			return -1;
		}

		return fileTable[fileId]->Write(buffer, size);
	}

	int Seek(int pos, int fileId) {
		if (fileId < 2 || fileId >= MAX_OPEN_FILES || fileTable[fileId] == NULL) {
			return -1;
		}

		return fileTable[fileId]->Seek(pos);
	}

	int Remove(char *name) {
		for (int i = 0; i < MAX_OPEN_FILES; i++) {
			if (fileTable[i] == NULL || fileTable[i]->fileName == NULL) {
				continue;
			}
			if (strcmp(name, fileTable[i]->fileName) == 0) {
				return -1;
			}
		}
		
		int res = Unlink(name);
		return res == 0 ? 0 : -1;
	}
};

#endif // FS_H
