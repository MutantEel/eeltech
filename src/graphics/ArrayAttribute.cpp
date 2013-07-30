//
//  ArrayAttribute.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//


#include <EelTech/graphics/ArrayAttribute.hpp>

namespace eeltech
{

ArrayAttribute::ArrayAttribute(std::string id, int size, vertexarray::Type type, int stride, int offset, bool normalized) : id(id), size(size), type(type), stride(stride), offset(offset), normalized(normalized)
{
}


ArrayAttribute::~ArrayAttribute()
{
}


void ArrayAttribute::enable(VertexArray* vao, ShaderProgram* program, bool enabled)
{
  if(enabled)
  {
    vao->setAttribute(program->getAttributeId(id.c_str()), size, type, stride, offset, normalized);
  }
  else
  {
    vao->setAttributeEnabled(program->getAttributeId(id.c_str()), false);
  }
}

	
std::string ArrayAttribute::getId()
{
	return id;
}

	
int ArrayAttribute::getSize()
{
	return size;
}
	
	
int ArrayAttribute::getStride()
{
	return stride;
}
	
	
int ArrayAttribute::getOffset()
{
	return offset;
}
	
vertexarray::Type ArrayAttribute::getType()
{
	return type;
}
	

} /* eeltech */

