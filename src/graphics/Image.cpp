//
//  Image.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//


#include <eeltech/graphics/Image.hpp>

#include <SOIL/SOIL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


namespace eeltech
{

 
Image::Image() : width(0), height(0), channels(0), data(NULL)
{
}


Image::~Image()
{
  if(data)
  {
    SOIL_free_image_data(data);
  }
}


bool Image::load(const char* const data, int size, bool alpha)
{
  this->data = SOIL_load_image_from_memory((const unsigned char*)data, size, &width, &height, &channels, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
  return this->data != 0;
}


int Image::getWidth()
{
  return width;
}


int Image::getHeight()
{
  return height;
}


int Image::getChannels()
{
  return channels;
}


unsigned char* Image::getData()
{
  return data;
}

  
} /* eeltech */

