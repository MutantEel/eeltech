//
//  Texture.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#include <eeltech/graphics/Texture.hpp>

#include <iostream>
#include <GLEW/GLEW.h>


namespace eeltech
{
 

Texture::Texture()
{
  glGenTextures(1, &glId);
}

Texture::~Texture()
{
  glDeleteTextures(1, &glId);
}

bool Texture::load(Image* image, bool clampToEdge, filter::Filter filterMode)
{
  return load(image->getData(), image->getWidth(), image->getHeight(), image->getChannels(), clampToEdge, filterMode);
}


bool Texture::load(unsigned char* imageData, int width, int height, int channels, bool clampToEdge, filter::Filter filterMode)
{
  glGetError(); // clear the previous errors

  glBindTexture(GL_TEXTURE_2D, glId);
  
  GLint minFilter = GL_LINEAR;
  GLint maxFilter = GL_LINEAR;
  
  switch(filterMode)
  {
    case filter::LinearMipmapLinear :
      minFilter = GL_LINEAR_MIPMAP_LINEAR;
      break;
    case filter::LinearMipmapNearest :
      minFilter = GL_LINEAR_MIPMAP_NEAREST;
      maxFilter = GL_NEAREST;
      break;
    case filter::Nearest:
      minFilter = GL_NEAREST;
      maxFilter = GL_NEAREST;
      break;
    case filter::NearestMipmapNearest:
      minFilter = GL_NEAREST_MIPMAP_NEAREST;
      maxFilter = GL_NEAREST;
      break;
    case filter::NearestMipmapLinear:
      minFilter = GL_NEAREST_MIPMAP_LINEAR;
      break;
    default:
      break;
  }
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
  
  if(clampToEdge)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }
    
  // set texture content
  glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA8 : GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);

  this->width = width;
  this->height = height;

  return glGetError() == 0;
}


unsigned int Texture::getId()
{
  return glId;
}

	
void Texture::bind(unsigned int textureUnit)
{
  activateTextureUnit(textureUnit);
  glBindTexture(GL_TEXTURE_2D, glId);
}

	
void Texture::unbind(unsigned int textureUnit)
{
  activateTextureUnit(textureUnit);
  glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::setBlendMode(blendmode::Mode mode)
{
  switch(mode)
  {
    case blendmode::None:
      glDisable(GL_BLEND);
      break;
    case blendmode::SourceAlpha:
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      break;
  }
}


int Texture::getWidth()
{
    return width;
}


int Texture::getHeight()
{
    return height;
}


void Texture::activateTextureUnit(unsigned int textureUnit)
{
  int unitId = GL_TEXTURE0;

  switch(textureUnit)
  {
    case 0:
      unitId = GL_TEXTURE0;
      break;
    case 1:
      unitId = GL_TEXTURE1;
      break;
    case 2:
      unitId = GL_TEXTURE2;
      break;
    case 3:
      unitId = GL_TEXTURE3;
      break;
    case 4:
      unitId = GL_TEXTURE4;
      break;
    case 5:
      unitId = GL_TEXTURE5;
      break;
    case 6:
      unitId = GL_TEXTURE6;
      break;
    case 7:
      unitId = GL_TEXTURE7;
      break;
    case 8:
      unitId = GL_TEXTURE8;
      break;
    case 9:
      unitId = GL_TEXTURE9;
      break;
    case 10:
      unitId = GL_TEXTURE10;
      break;
    case 11:
      unitId = GL_TEXTURE11;
      break;
    case 12:
      unitId = GL_TEXTURE12;
      break;
    case 13:
      unitId = GL_TEXTURE13;
      break;
    case 14:
      unitId = GL_TEXTURE14;
      break;
    case 15:
      unitId = GL_TEXTURE15;
      break;
    default:
#ifdef DEBUG
      std::cout << "warning activating texture unit " << textureUnit << " is out of range 0-15, activating 0 instead!!";
#endif
      break;
  }

  glActiveTexture(unitId);
}

  
} /* eeltech */
