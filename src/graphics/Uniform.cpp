//
//  Uniform.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#include <eeltech/graphics/Uniform.hpp>
#include <cstring>
#include <iostream>

namespace eeltech
{


Uniform::Uniform(const char* location, uniformType::Type type, int elementCount, int numItems, void* data, bool transpose) : location(location), type(type), elementCount(elementCount), numItems(numItems), transpose(transpose)
{
	int size = 0;

	switch(type)
	{
		case uniformType::UInt:
			size = sizeof(unsigned int) * numItems * elementCount;
			break;
		case uniformType::Int:
			size = sizeof(int) * numItems * elementCount;
			break;
		case uniformType::Float:
			size = sizeof(float) * numItems * elementCount;
			break;
		case uniformType::Matrix2:
			size = sizeof(float) * numItems * 2 * 2;
			break;
		case uniformType::Matrix4:
			size = sizeof(float) * numItems * 4 * 4;
			break;
		case uniformType::Matrix2x3:
			size = sizeof(float) * numItems * 2 * 3;
			break;
		case uniformType::Matrix3x2:
			size = sizeof(float) * numItems * 3 * 2;
			break;
		case uniformType::Matrix2x4:
			size = sizeof(float) * numItems * 2 * 4;
			break;
		case uniformType::Matrix4x2:
			size = sizeof(float) * numItems * 4 * 2;
			break;
		case uniformType::Matrix3x4:
			size = sizeof(float) * numItems * 3 * 4;
			break;
		case uniformType::Matrix4x3:
			size = sizeof(float) * numItems * 4 * 3;
			break;
	}

	this->data = new char[size];

	memcpy(this->data, data, size);
}

   
Uniform::~Uniform()
{
	if(data != NULL)
	{
	  switch(type)
    {
	    case uniformType::UInt:
		    delete (unsigned int*)data;
		    break;
	    case uniformType::Int:
		    delete (int*)data;
		    break;
	    case uniformType::Float:
	    case uniformType::Matrix2:
	    case uniformType::Matrix4:
	    case uniformType::Matrix2x3:
	    case uniformType::Matrix3x2:
	    case uniformType::Matrix2x4:
	    case uniformType::Matrix4x2:
	    case uniformType::Matrix3x4:
	    case uniformType::Matrix4x3:
        delete (float*)data;
		    break;
    }
	}
}

void Uniform::apply(ShaderProgram* program)
{
  unsigned int id = program->getUniformId(location);

  switch(type)
	{
		case uniformType::UInt:
			program->setUniform(id, elementCount, numItems, (unsigned int*)data);
			break;
		case uniformType::Int:
			program->setUniform(id, elementCount, numItems, (int*)data);
			break;
		case uniformType::Float:
      program->setUniform(id, elementCount, numItems, (float*)data);
			break;
		case uniformType::Matrix2:
      program->setUniformMatrix(id, uniform::Matrix2, numItems, (float*)data, transpose);
			break;
		case uniformType::Matrix4:
      program->setUniformMatrix(id, uniform::Matrix4, numItems, (float*)data, transpose);
			break;
		case uniformType::Matrix2x3:
      program->setUniformMatrix(id, uniform::Matrix2x3, numItems, (float*)data, transpose);
			break;
		case uniformType::Matrix3x2:
      program->setUniformMatrix(id, uniform::Matrix3x2, numItems, (float*)data, transpose);
			break;
		case uniformType::Matrix2x4:
      program->setUniformMatrix(id, uniform::Matrix2x4, numItems, (float*)data, transpose);
			break;
		case uniformType::Matrix4x2:
      program->setUniformMatrix(id, uniform::Matrix4x2, numItems, (float*)data, transpose);
			break;
		case uniformType::Matrix3x4:
      program->setUniformMatrix(id, uniform::Matrix3x4, numItems, (float*)data, transpose);
			break;
		case uniformType::Matrix4x3:
      program->setUniformMatrix(id, uniform::Matrix4x3, numItems, (float*)data, transpose);
			break;
	}
	
	
#ifdef DEBUG
	GLenum error = glGetError();
	if(error != 0)
	{
		std::cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << " GLERROR " << (int)error << std::endl;
	}
#endif
}
  
} /* eeltech */

