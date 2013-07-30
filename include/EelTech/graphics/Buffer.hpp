//
//  Buffer.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#include <GLEW/GLEW.h>

namespace eeltech
{

namespace buffer
{
  enum Type
  {
    Static = GL_STATIC_DRAW,
    Dynamic = GL_DYNAMIC_DRAW,
    Stream = GL_STREAM_DRAW,
  };

  enum Target
  {
    Array = GL_ARRAY_BUFFER,
    ElementArray = GL_ELEMENT_ARRAY_BUFFER,
  };
}


/**
 * A graphics buffer (vbo)
 */
class Buffer
{

  public:

    /**
     * A default constructor
     */
    Buffer();

    /**
     * Default destructor
     */
    ~Buffer();
      
    /**
     * Creates a new buffer for use
     */
    void create(void* data, int length, buffer::Type type, buffer::Target target);

    /**
     * updates the contents of the buffer
     */
    void update(void* data, int length);

    /**
     * @return if the buffer was created
     */
    bool wasCreated();

    /**
     * bind the buffer for use
     */
    void bind();

    /**
     * unbinds the buffer
     */
    void unbind();

    /**
     * gets the id of the buffer
     */    
    unsigned int getId();
	
		/**
		 * reads the data out of the opengl buffer
		 */
		void* getData();
	
		/**
		 * gets the length of the data buffer
		 */
		int getLength();

  private:
		
		int length;
    bool bufferWasCreated;
    unsigned int glId;
    buffer::Target target;
};


} /* eeltech */


#endif  /* _VERTEXBUFFER_HPP */

