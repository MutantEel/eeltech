//
//  File.hpp
//  EelTech
//
// Created by Sean on 7/31/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <string>

namespace eeltech
{

class File
{
  public:

    /** 
     * default constructor
     * @param the path to the file
     */
    File(std::string path);

    /**
     * @return if the file exists
     */
    bool exists();

    /**
     * opens the file for reading
     * @return if successful
     */
    bool openRead();

    /**
     * opens the file for writing, erasing the file
     * @return if successful
     */
    bool openWrite();

    /**
     * opens the file for writing, appending to the file
     * @return if successful
     */
    bool openAppend();

    /**
     * get's the size of the file
     */
    signed long long size();

    /**
     * reads from the file
     * @param the buffer to read into
     * @param the size in bytes of the object being read from
     * @param the number of objects to read
     * @return the amount read
     */
    signed long long read(char* buffer, unsigned int objectSize, unsigned int size);

    /**
     * write to the file
     * @param the buffer to read from
     * @param the size in bytes of the object being written to
     * @param the number of objects to write
     * @return the amount written
     */
    signed long long write(char* buffer, unsigned int objectSize, unsigned int size);

    /**
     * seeks to the absolute position in the file from the begining
     * @param the position to seek to
     */
    bool seek(unsigned long long position);

    /**
     * @return if the position is at the end of the file
     **/
    bool is_eof();

    /**
     * @return the position in the file
     **/
    signed long long position();


    /**
     * Closes the file
     */
    void close();

    /**
     * flushes the write buffer if needed
     */
    void flush();

    /**
     * loads a file into a buffer, you are resposible for deleting the buffer
     * @param the path to the file
     * @param a pointer to the buffer to load into
     * @return the size of the buffer
     */
    static signed long long loadBytes(std::string path, char** buffer);

    /**
     * loads a file into a std::string
     * @param the path to the file
     * @return the string
     */
    static std::string loadString(std::string path);

  private:
    void* handle;
    std::string path;
};


}

#endif

