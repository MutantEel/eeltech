//
//  VertexArray.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//



#ifndef _VERTEX_ARRAY_HPP_
#define _VERTEX_ARRAY_HPP_

#include <eeltech/graphics/Buffer.hpp>

namespace eeltech
{

namespace vertexarray
{
  enum Type
  {
    Byte = GL_BYTE,
    UByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UInt = GL_UNSIGNED_INT,
    Float = GL_FLOAT,
    Double = GL_DOUBLE
  };
}


/**
 * A graphics buffer (vao)
 */
class VertexArray
{

  public:

    /**
     * A default constructor
     */
    VertexArray();

    /**
     * Default destructor
     */
    ~VertexArray();
      
    /**
     * Sets an attribute a new buffer for use
     */
    void setAttribute(int attributeId, int size, vertexarray::Type type, int stride, int offset = 0, bool normalized = false);

    /**
     * Enables or disables an attribute
     */
    void setAttributeEnabled(int attributeId, bool enabled);

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

  private:

    unsigned int glId;
};


} /* eeltech */


#endif  /* _VERTEXBUFFER_HPP */

