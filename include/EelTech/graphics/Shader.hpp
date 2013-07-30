//
//  Shader.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _SHADER_HPP_
#define	_SHADER_HPP_

#include <GLEW/GLEW.h>

namespace eeltech
{
    
namespace shader
{
    
typedef enum
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
}Type;
    
    
} /* shader */


    
/**
 * A shader (GLSL program)
 */
class Shader
{
  public:
		
    /**
     * A default constructor
     */
    Shader();


    /**
     * A default destructor
     */
    ~Shader();

    /**
     * Trys to load a shader from source
     * source - the source code of the shader
     * type - the type of the shader
     * @return if the shader loaded successfully
     */
    bool create(const char* source, shader::Type type);
		
    /**
     * Gets the type of the shader
     * @return type of the shader
     */
    shader::Type getType();

    /**
     * Gets the id of the shader
     */
    unsigned int getId();

	protected:
		
		  unsigned int glId;  /**< Holds the opengl shader id     */
		  shader::Type type;  /**< Holds the type of the shader   */
};

	
} /* eeltech */

#endif	/* _SHADER_HPP */

