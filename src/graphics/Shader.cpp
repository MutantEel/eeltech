//
//  Shader.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//


#include <eeltech/graphics/Shader.hpp>
#include <GLEW/GLEW.h>
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef __APPLE__
 #include <malloc.h>
#endif

namespace eeltech
{


Shader::Shader()
{
  glId = 0;
}


Shader::~Shader()
{
  if(glId != 0)
  {
    glDeleteShader(glId);
    glId = 0;
  }
}


bool Shader::create(const char* source, shader::Type type)
{
  if(glId != 0)
  {
    glDeleteShader(glId);
    glId = 0;
  }

  this->type = type;
  GLint result;
  int sourceSize = (int)strlen(source);

  glId = glCreateShader(type);

  glShaderSource(glId, 1, (const GLchar**)&source, &sourceSize);
  glCompileShader(glId);

  glGetShaderiv(glId, GL_COMPILE_STATUS, &result);
  
  if(!result)
  {
#ifdef DEBUG
    std::cout << "Failed to compile shader" << std::endl;
    
    //show the compile log
    GLint log_length;
    glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &log_length);
    char* log = (char*)malloc(log_length);
    glGetShaderInfoLog(glId, log_length, NULL, log);
    std::cout << log << std::endl;
    free(log);
#endif

    glDeleteShader(glId);
    glId = 0;

    return false;
  }
  
  return true;
}

	
shader::Type Shader::getType()
{
  return type;
}


unsigned int Shader::getId()
{
  return glId;
}


} /* eeltech */
