//
//  VertexArray.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#include <eeltech/graphics/VertexArray.hpp>

namespace eeltech
{

VertexArray::VertexArray()
{
  glGenVertexArrays(1, &glId);
}


VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &glId);
}


void VertexArray::setAttribute(int attributeId, int size, vertexarray::Type type, int stride, int offset, bool normalized)
{
  glEnableVertexAttribArray(attributeId);
  glVertexAttribPointer(attributeId, size, type, normalized, stride, (void*)offset);
}


void VertexArray::setAttributeEnabled(int attributeId, bool enabled)
{
  if(enabled)
  {
    glEnableVertexAttribArray(attributeId);
  }
  else
  {
    glDisableVertexAttribArray(attributeId);
  }
}


void VertexArray::bind()
{
  glBindVertexArray(glId);
}


void VertexArray::unbind()
{
  glBindVertexArray(0);
}


unsigned int VertexArray::getId()
{
  return glId;
}


} /* eeltech */
