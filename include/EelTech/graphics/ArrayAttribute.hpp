//
//  ArrayAttribute.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//



#ifndef _ARRAY_ATTRIBUTE_HPP_
#define _ARRAY_ATTRIBUTE_HPP_



#include <eeltech/graphics/VertexArray.hpp>
#include <eeltech/graphics/ShaderProgram.hpp>
#include <string>

namespace eeltech
{

/**
 * An attribute defines the parts of a mesh such as vertices, colors
 */
class ArrayAttribute
{

  public:

    /**
     * A default constructor
     */
	ArrayAttribute(std::string id, int size, vertexarray::Type type, int stride, int offset = 0, bool normalized = false);

    /**
     * Default destructor
     */
    ~ArrayAttribute();

    /**
     * Enables or disables an attribute
     */
    void enable(VertexArray* vao, ShaderProgram* program, bool enabled);

	
		std::string getId();
		int getSize();
		int getStride();
		int getOffset();
		vertexarray::Type getType();

  private:

    std::string id;
    int size;
    vertexarray::Type type;
    int stride;
    int offset;
    bool normalized;
    
};


} /* eeltech */


#endif  /* _ARRAY_ATTRIBUTE_HPP_ */

