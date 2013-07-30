//
//  ShaderProgram.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#include <eeltech/graphics/ShaderProgram.hpp>
#include <GLEW/GLEW.h>
#include <iostream>
#include <fstream>



namespace eeltech
{
    
    
ShaderProgram::ShaderProgram()
{
  glId = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
  glDeleteProgram(glId);
}

  
void ShaderProgram::addShader(Shader* shader)
{
  glAttachShader(glId, shader->getId());
}


void ShaderProgram::removeShader(Shader* shader)
{
  glDetachShader(glId, shader->getId());
}


bool ShaderProgram::link()
{
  glLinkProgram(glId);

  GLint result;

  glGetProgramiv(glId, GL_LINK_STATUS, &result);
  
  if(!result)
  {
#ifdef DEBUG
    std::cout << "Failed to link shader program " << std::endl;

    //show the compile log
    GLint log_length;
    glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &log_length);
    char* log = (char*)malloc(log_length);
    glGetProgramInfoLog(glId, log_length, NULL, log);
    std::cout << log << std::endl;
    free(log);
#endif
    return false;
  }

  return true;
}


void ShaderProgram::bind()
{
  glUseProgram(glId);
}


void ShaderProgram::unbind()
{
  glUseProgram(0);
}


unsigned int ShaderProgram::getUniformId(const char* uniform)
{
  return glGetUniformLocation(glId, uniform);
}


unsigned int ShaderProgram::getAttributeId(const char* attribute)
{
  return glGetAttribLocation(glId, attribute);
}


void ShaderProgram::setUniform(unsigned int location, int elementCount, int numItems, float* data)
{
  switch(elementCount)
  {
    case 1:
      glUniform1fv(location, numItems, (const GLfloat*)data);
      break;
    case 2:
      glUniform2fv(location, numItems, (const GLfloat*)data);
      break;
    case 3:
      glUniform3fv(location, numItems, (const GLfloat*)data);
      break;
    case 4:
      glUniform4fv(location, numItems, (const GLfloat*)data);
      break;
    default:
#ifdef DEBUG
      std::cout << "Passed an invalid element count to uniform, not setting" << std::endl;
#endif
      break;
  }
}


void ShaderProgram::setUniform(unsigned int location, int elementCount, int numItems, int* data)
{
  switch(elementCount)
  {
    case 1:
      glUniform1iv(location, numItems, (const GLint*)data);
      break;
    case 2:
      glUniform2iv(location, numItems, (const GLint*)data);
      break;
    case 3:
      glUniform3iv(location, numItems, (const GLint*)data);
      break;
    case 4:
      glUniform4iv(location, numItems, (const GLint*)data);
      break;
    default:
#ifdef DEBUG
      std::cout << "Passed an invalid element count to uniform, not setting" << std::endl;
#endif
      break;
  }
}


void ShaderProgram::setUniform(unsigned int location, int elementCount, int numItems, unsigned int* data)
{
  switch(elementCount)
  {
    case 1:
      glUniform1uiv(location, numItems, (const GLuint*)data);
      break;
    case 2:
      glUniform2uiv(location, numItems, (const GLuint*)data);
      break;
    case 3:
      glUniform3uiv(location, numItems, (const GLuint*)data);
      break;
    case 4:
      glUniform4uiv(location, numItems, (const GLuint*)data);
      break;
    default:
#ifdef DEBUG
      std::cout << "Passed an invalid element count to uniform, not setting" << std::endl;
#endif
      break;
  }
}


void ShaderProgram::setUniformMatrix(unsigned int location, uniform::MatrixType type, int numItems, float* data, bool transpose)
{
  switch(type)
  {
    case uniform::Matrix2:
      glUniformMatrix2fv(location, numItems, transpose, data);
      break;
    case uniform::Matrix4:
      glUniformMatrix4fv(location, numItems, transpose, data);
      break;
    case uniform::Matrix2x3:
      glUniformMatrix2x3fv(location, numItems, transpose, data);
      break;
    case uniform::Matrix3x2:
      glUniformMatrix3x2fv(location, numItems, transpose, data);
      break;
    case uniform::Matrix2x4:
      glUniformMatrix2x4fv(location, numItems, transpose, data);
      break;
    case uniform::Matrix4x2:
      glUniformMatrix4x2fv(location, numItems, transpose, data);
      break;
    case uniform::Matrix3x4:
      glUniformMatrix3x4fv(location, numItems, transpose, data);
      break;
    case uniform::Matrix4x3:
      glUniformMatrix4x3fv(location, numItems, transpose, data);
      break;
  }
}

} /* eeltech */


