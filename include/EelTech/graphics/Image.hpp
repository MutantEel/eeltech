//
//  Image.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

namespace eeltech
{

/**
 * Image class decompresses common formats and saves information on the image
 */
class Image
{
  public:
    
    /**
     * A default constructor
     */
    Image();

    /**
     * A default destructor
     */
    ~Image();

    /**
     * Trys to load a image from memory
     * @param the raw data of the image
     * @param the size of the data
     * @param if you want to force the image to have alpha or not
     * @return if the image loaded successfully
     */
    bool load(const char* const data, int size, bool alpha = true);

    /**
     * Gets the width of the image
     */
    int getWidth();

    /**
     * Gets the height of the image
     */
    int getHeight();

    /**
     * Gets the number of channels in the image
     */
    int getChannels();

    /**
     * Gets the data of the image
     */
    unsigned char* getData();

  protected:
      
    int width;
    int height;
    int channels;
    unsigned char* data;
};

  
} /* eeltech */

#endif  /* _IMAGE_HPP_ */

