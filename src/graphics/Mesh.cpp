//
//  Mesh.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//


#include <eeltech/graphics/Mesh.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

namespace eeltech
{


Mesh::Mesh()
{
  vertData = NULL;
}


Mesh::~Mesh()
{
  if(vertData)
  {
    free(vertData);
  }
}


void Mesh::setVerts(void* newVertData, int vertDataSize, buffer::Type type)
{
  if(type == buffer::Dynamic)
  {
    if(vertData)
    {
      free(vertData);
    }
    vertData = (float*)malloc(vertDataSize);
    memcpy(vertData, newVertData, vertDataSize);
  }

  vertBuffer.create(newVertData, vertDataSize, type, buffer::Array);
}


void Mesh::setIndices(void* idxData, int idxDataSize, buffer::Type type)
{
  idxBuffer.create(idxData, idxDataSize, type, buffer::ElementArray);
}


void Mesh::setNumElements(int numElements)
{
  this->numElements = numElements;
}


void Mesh::setDrawType(mesh::DrawType type)
{
  drawType = type;
}


void Mesh::bind()
{
  vertBuffer.bind();
  idxBuffer.bind();
}


void Mesh::unbind()
{
  vertBuffer.unbind();
  idxBuffer.unbind();
}


void Mesh::addAttribute(ArrayAttribute attribute)
{
  attributes.push_back(attribute);
}


void Mesh::updateVertices(void* data, int length)
{
	vertBuffer.update(data, length);
}
	
	
void Mesh::updateIndices(void* data, int length)
{
	idxBuffer.update(data,length);
}
	
	
void* Mesh::getVertData(int* length)
{
	(*length) = vertBuffer.getLength();
	return vertBuffer.getData();
}
	
	
void* Mesh::getIndexData(int* length)
{
	(*length) = idxBuffer.getLength();
	return idxBuffer.getData();
}


mesh::DrawType Mesh::getDrawType()
{
	return drawType;
}
	

int Mesh::getNumElement()
{
	return numElements;
}
	

} /* eeltech */

