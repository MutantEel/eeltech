//
//  Texture.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <eeltech/graphics/Image.hpp>

namespace eeltech
{
 
namespace blendmode
{

enum Mode
{
  None = 0,
  SourceAlpha = 1,
};

}

namespace filter
{
  
enum Filter
{
  Linear = 0,
  Nearest = 1,
  NearestMipmapNearest = 2,
  LinearMipmapNearest = 3,
  NearestMipmapLinear = 4,
  LinearMipmapLinear = 5,
};

}

/**
 * A Texture class, the image loaded into gpu memory
 */
class Texture
{
  public:
    
    /**
     * A default constructor
     */
    Texture();

    /**
     * A default destructor
     */
    ~Texture();

    /**
     * Trys to load a texture from an image
     * @param the image to load
     * @param if the texture should clamp to the edge
     * @param the filter mode for the texture
     * @return if the texture loaded successfully
     */
    bool load(Image* image, bool clampToEdge = false, filter::Filter filterMode = filter::Linear);

    /**
     * Trys to load a texture from a byte array
     * @param the imageData to load
     * @param the width of the image
     * @param the height of the image
     * @param the number of color channels in the image, (3=RGB, 4 = RGBA)
     * @param if the texture should clamp to the edge
     * @param the filter mode for the texture
     * @return if the texture loaded successfully
     */
    bool load(unsigned char* imageData, int width, int height, int channels, bool clampToEdge = false, filter::Filter filterMode = filter::Linear);

    /**
     * Gets the id of texture
     */
    unsigned int getId();

    /**
     * binds the texture
     * The texture unit to bind the texture to (supporting 0-15)
     */
    void bind(unsigned int textureUnit);

    /**
     * unbinds a given texture unit
     * The texture unit to unbind (supporting 0-15)
     */
     static void unbind(unsigned int textureUnit);

     /**
      * sets the blend mode for texturing
      */
     static void setBlendMode(blendmode::Mode mode);

     int getWidth();

     int getHeight();

  protected:

    static void activateTextureUnit(unsigned int textureUnit);
      
    unsigned int glId;
    int width;
    int height;
};

  
} /* eeltech */

#endif  /* _TEXTURE_HPP_ */

