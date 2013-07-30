//
//  ShaderProgram.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _SHADER_PROGRAM_HPP_
#define	_SHADER_PROGRAM_HPP_


#include <eeltech/graphics/Shader.hpp>


namespace eeltech
{

namespace uniform
{
  enum MatrixType
  {
    Matrix2,
    Matrix4,
    Matrix2x3,
    Matrix3x2,
    Matrix2x4,
    Matrix4x2,
    Matrix3x4,
    Matrix4x3,
  };
}
	

/**
 * A shader program is a set of shaders, usualy a vertex and fragment shader
 */
class ShaderProgram
{
  public:
	
  	/**
  	 * A default constructor
  	 */
  	ShaderProgram();
  	
  	/**
  	 * A default destructor
  	 */
  	~ShaderProgram();
  	
  	/**
     * Adds a shader to the set for use.
  	 * @param the shader to add to the set
     */
  	void addShader(Shader* shader);
  	
  	/**
      * Removes a shader from the set.
  	  * @param the shader to remove from the set
      */
  	void removeShader(Shader* shader);

  	/**
      * After all shaders have been added, link needs to be called.
			* @return if the link succeeded 
      */
  	bool link();
  	
  	/**
      * Sets the current shader set to use
      */
  	void bind();
  	
  	/**
      * Unbinds the current shader
      */
  	static void unbind();

    /**
     * Gets the id of the uniform from the name
     */
    unsigned int getUniformId(const char* uniform);

    /**
     * Get the id of the attribute from the name
     */
    unsigned int getAttributeId(const char* attribute);

    /**
     * sets the uniform values for the program for float data (1-4 items in the array)
     */
    void setUniform(unsigned int location, int elementCount, int numItems, float* data);

    /**
     * sets the uniform values for the program for int data (1-4 items in the array)
     */
    void setUniform(unsigned int location, int elementCount, int numItems, int* data);

    /**
     * sets the uniform values for the program for unsigned int data (1-4 items in the array)
     */
    void setUniform(unsigned int location, int elementCount, int numItems, unsigned int* data);
   
    /**
     * sets the uniform values for the program for matrix data
     */ 
    void setUniformMatrix(unsigned int location, uniform::MatrixType type, int numItems, float* data, bool transpose = true);

  protected:

    unsigned int glId;	/**< Holds the opengl shader program id        */
};

	
} /* eeltech */

#endif	/* _SHADER_PROGRAM_HPP_ */

