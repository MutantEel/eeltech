//
//  Material.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#include <eeltech/graphics/Material.hpp>


namespace eeltech
{
 

TextureMaterial::TextureMaterial(Texture* texture, int textureUnit) : texture(texture), textureUnit(textureUnit)
{
}


void TextureMaterial::bind()
{
	if(texture)
	{
		texture->bind(textureUnit);
	}
	else
	{
		Texture::unbind(textureUnit);
	}
}


void TextureMaterial::unbind()
{
	Texture::unbind(textureUnit);
}


	



Material::Material()
{
}


Material::~Material()
{
}


void Material::bind()
{
  Texture::setBlendMode(blendMode);
  program->bind();

  for(std::vector<TextureMaterial>::iterator itr = textures.begin(); itr != textures.end(); itr++)
  {
    itr->bind();
  }
}


void Material::unbind()
{
  for(std::vector<TextureMaterial>::iterator itr = textures.begin(); itr != textures.end(); itr++)
  {
    itr->unbind();
  }

  program->unbind();
}

  
} /* eeltech */

