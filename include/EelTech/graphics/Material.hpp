//
//  Material.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <eeltech/graphics/ShaderProgram.hpp>
#include <eeltech/graphics/Texture.hpp>
#include <eeltech/graphics/Uniform.hpp>
#include <vector>

namespace eeltech
{
 

/** 
 * a union of texture and texture unit for (un)bind ing
 */
struct TextureMaterial
{
  Texture* texture;
  int textureUnit;

  /**
   * @param the texture to use
   * @param the texture unit to use
   */
  TextureMaterial(Texture* texture, int textureUnit);

  /**
   * binds the texture 
   */
  void bind();

  /**
   * unbinds the texture 
   */
  void unbind();
};


/**
 * A class that defines a material
 * a material consists of shader program, it's uniforms, textures and a blend mode.
 * uniform memory is handled by the material
 */
class Material
{
  public:
    
    /**
     * A default constructor
     */
    Material();

    /**
     * A default destructor
     */
    ~Material();

    /**
     * binds the material for use
     */
    void bind();

    /**
     * unbinds a the material
     */
    void unbind();

    ShaderProgram* program;																				/**< the shader program to use          */
    std::vector<TextureMaterial> textures;                        /**< the textures to use                */
    blendmode::Mode blendMode;                                    /**< the blend mode to use              */
};

  
} /* eeltech */

#endif  /* _MATERIAL_HPP_ */

