//
//  FileSystem.hpp
//  EelTech
//
// Created by Sean on 7/31/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _FILESYSTEM_HPP_
#define _FILESYSTEM_HPP_

#include <string>
#include <list>

namespace eeltech
{

namespace FileSystem
{

/**
 * struct to hold information on a file returned from a directory listing
 */
struct FileListItem
{
  std::string path; /**< the absolute path to the file or directory */
  bool isDirectory; /**< if the item is a directory                 */
  signed long long modTime; /**< the last time the file has been modified in seconds since epoch (Jan 1, 1970), -1 if can't be determined */
};


/**
  * initializes the file system for use
  * @param argv0 from main(argc, argv);
  * @return if the initialization was successful
  **/
bool init(char* argv0);

/**
  * cleans up the file system
  */
void shutdown();
  
/**
  * mounts a path or file to a specific location
  * @param the path to mount
  * @param the place to mount the path to
  * @param if the path should be appended or prepended
  * @return if the mounting was successful
  */
bool mount(std::string path, std::string mountPoint, bool append);


/**
 * sets the directory to write to
 * @param the directory to write to
 */
bool setWriteDirectory(std::string path);

/**
 * makes a directory
 * @param the path to the directory
 */
bool makeDirectory(std::string path);

/**
 * deletes a file or directory
 * @param the file or directory to delete
 */
bool remove(std::string path);

/**
 * is the path a directory?
 * @param the file or directory test
 */
bool isDirectory(std::string path);

/**
 * gets the last time the file was modified
 * @param the file or directory to get the modification time from
 */
signed long long lastModificationTime(std::string path);

/**
 * lists files in a directory
 * @param the directory to list
 */
std::list<FileListItem> listFiles(std::string path);

/**
  * gets the last error that occured
  * @return the string of the last error
  */
std::string getLastError();

}


}

#endif

