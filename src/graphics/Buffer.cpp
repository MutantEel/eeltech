//
//  Buffer.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//


#include <eeltech/graphics/Buffer.hpp>

#include <iostream>


namespace eeltech
{


Buffer::Buffer()
{
  bufferWasCreated = false;
  glId = 0;
}


Buffer::~Buffer()
{
  if(glId)
  {
    glDeleteBuffers(1, &glId);
  }
  glId = 0;
}


void Buffer::create(void* data, int length, buffer::Type type, buffer::Target target)
{
  this->target = target;
	this->length = length;

  if(glId)
  {
    glDeleteBuffers(1, &glId);
  }
  glId = 0;

  glGenBuffers(1, &glId);
  glBindBuffer(target, glId);
  glBufferData(target, length, data, type);
  glBindBuffer(target, 0);
	
#ifdef DEBUG
	GLenum error = glGetError();
	if(error != 0)
	{
		std::cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << " GLERROR " << (int)error << std::endl;
	}
#endif
	
  bufferWasCreated = true;
}


void Buffer::update(void* data, int length)
{
	this->length = length;
	
  bind();
  glBufferSubData(this->target, 0, length, data);
  unbind();
}


bool Buffer::wasCreated()
{
  return bufferWasCreated;
}


void Buffer::bind()
{
  glBindBuffer(target, glId);
}


void Buffer::unbind()
{
  glBindBuffer(target, 0);
}


unsigned int Buffer::getId()
{
    return glId;
}
	

void* Buffer::getData()
{
	if(!bufferWasCreated)
	{
		return NULL;
	}
	
	void* data = malloc(length);
	
	bind();
	glGetBufferSubData(target, 0, length, data);
	unbind();
	
	return data;
}
	

int Buffer::getLength()
{
	return length;
}


} /* eeltech */

