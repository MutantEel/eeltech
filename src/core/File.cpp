//
//  File.cpp
//  EelTech
//
// Created by Sean on 7/31/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//


#include <EelTech/core/File.hpp>
#include <physfs/physfs.h>
#include <iostream>

namespace eeltech
{

File::File(std::string path) : path(path), handle(NULL)
{
}

 
bool File::exists()
{
  return PHYSFS_exists(path.c_str()) != 0;
}


bool File::openRead()
{
  handle = (PHYSFS_File*)PHYSFS_openRead(path.c_str());

  if(handle == NULL)
  {
#ifdef DEBUG
    std::cout << "couldn't open file: " << path << std::endl;
#endif
  }

  return handle != NULL;
}


bool File::openWrite()
{
  handle = (PHYSFS_File*)PHYSFS_openWrite(path.c_str());
  return handle != NULL;
}


bool File::openAppend()
{
  handle = (PHYSFS_File*)PHYSFS_openAppend(path.c_str());
  return handle != NULL;
}


signed long long File::size()
{
  return PHYSFS_fileLength((PHYSFS_File*)handle);
}


long long int File::read(char* buffer, unsigned int objectSize, unsigned int size)
{
  return PHYSFS_read((PHYSFS_File*)handle, buffer, objectSize, size);
}


signed long long File::write(char* buffer, unsigned int objectSize, unsigned int size)
{
  return PHYSFS_write((PHYSFS_File*)handle, buffer, objectSize, size);
}


bool File::seek(unsigned long long int position)
{
  return PHYSFS_seek((PHYSFS_File*)handle, position) != 0;
}


bool File::is_eof()
{
  return PHYSFS_eof((PHYSFS_File*)handle) == 1;
}


signed long long File::position()
{
  return PHYSFS_tell((PHYSFS_File*)handle);
}


void File::close()
{
  PHYSFS_close((PHYSFS_File*)handle);
}


void File::flush()
{
  PHYSFS_flush((PHYSFS_File*)handle);
}


signed long long File::loadBytes(std::string path, char** buffer)
{
  File f(path);
  
  if(!f.exists())
	{
    std::cout << "couldn't find file: " << path << std::endl;
		*buffer = NULL;
    return 0;
  }

  f.openRead();

  unsigned int fileSize = (unsigned int)f.size();
  *buffer = new char[fileSize];
  f.read(*buffer, 1, fileSize);
  f.close();

  return fileSize;
}


std::string File::loadString(std::string path)
{
  char* data = NULL;
  long long size = loadBytes(path, &data);
	
	if(size == 0)
	{
		return "";
	}
	
  std::string result(data, (size_t)size);
  delete data;
  return result;
}

}
