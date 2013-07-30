//
//  Uniform.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _UNIFORM_HPP_
#define _UNIFORM_HPP_

#include <eeltech/graphics/ShaderProgram.hpp>

namespace eeltech
{

namespace uniformType
{
  enum Type
  {
    UInt,
    Int,
    Float,
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
 * A class that defines a uniform used in a shader
 */
class Uniform
{
  public:
    
    /**
     * A default constructor
	   * @param location of the uniform
     * @param the type of uniform
     * @param the number of elements in one object, not used for matricies
     * @param the number of objects in the data
     * @param the data for uniform, a copy will be made so delete yours when your done
     * @param if the matrix should be transposed, only used for matricies
     */
    Uniform(const char* location, uniformType::Type type, int elementCount, int numItems, void* data, bool transpose = true);

    /**
     * A default destructor
     */
    ~Uniform();

    /**
     * applys the uniform to the shader
     */
    void apply(ShaderProgram* program);

  protected:
	  const char* location;	  /**< the location of the uniform                                  */
    uniformType::Type type; /**< the type of uniform                                          */
    int elementCount;       /**< number of elements in one object, not used for matricies     */
    int numItems;           /**< the number of objects in the data                            */
    void* data;             /**< the data for uniform                                         */
    bool transpose;         /**< if the matrix should be transposed, only used for matricies  */
};

  
} /* eeltech */

#endif  /* _UNIFORM_HPP_ */

