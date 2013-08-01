//
//  FileSystem.cpp
//  EelTech
//
// Created by Sean on 7/31/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/core/FileSystem.hpp>
#include <physfs/physfs.h>

namespace eeltech
{

namespace FileSystem
{

bool init(char* argv0)
{
  return PHYSFS_init(argv0) != 0;
}


void shutdown()
{
  PHYSFS_deinit();
}
  

bool mount(std::string path, std::string mountPoint, bool append)
{
  return PHYSFS_mount(path.c_str(), mountPoint.c_str(), append ? 1 : 0) != 0;
}


bool setWriteDirectory(std::string path)
{
  return PHYSFS_setWriteDir(path.c_str()) != 0;
}


bool makeDirectory(std::string path)
{
  return PHYSFS_mkdir(path.c_str()) != 0;
}


bool remove(std::string path)
{
  return PHYSFS_delete(path.c_str()) != 0;
}


bool isDirectory(std::string path)
{
  return PHYSFS_isDirectory(path.c_str()) != 0;
}


signed long long lastModificationTime(std::string path)
{
  return PHYSFS_getLastModTime(path.c_str());
}


std::list<FileListItem> listFiles(std::string path)
{
  std::list<FileListItem> files;

  char** results = PHYSFS_enumerateFiles(path.c_str());

  // make sure to add the seperator
  std::string newPath = path[path.length() - 1] == '/' ? path : path + "/";

  for(char** i = results; *i != NULL; i++)
  {
    FileListItem fli;
    fli.path = newPath + std::string(*i);
    fli.isDirectory = isDirectory(fli.path);
    fli.modTime = lastModificationTime(fli.path);
    files.push_back(fli);
  }

  PHYSFS_freeList(results);

  return files;
}

std::string getLastError()
{
  return std::string(PHYSFS_getLastError());
}


}


}
