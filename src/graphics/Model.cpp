//
//  Model.cpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#include <eeltech/graphics/Model.hpp>
#include <iostream>

namespace eeltech
{


Model::Model()
{
}


Model::~Model()
{
	
}

   
void Model::draw()
{
  material->bind();
  vao.bind();
  
  glDrawElements(mesh->getDrawType(), mesh->getNumElement(), GL_UNSIGNED_SHORT, (void*)0);

  vao.unbind();
  material->unbind();
}


void Model::setMesh(Mesh* mesh)
{
  material->program->bind();
  vao.bind();
  mesh->bind();
  
  for(std::vector<ArrayAttribute>::iterator itr = mesh->attributes.begin(); itr != mesh->attributes.end(); itr++)
  {
    itr->enable(&vao, material->program, true);
  }

  vao.unbind();
  material->program->unbind();

  this->mesh = mesh;
}


void Model::setMaterial(Material* material)
{
  this->material = material;
}

    
void Model::setUniform(Uniform& uniform)
{
  material->program->bind();
  vao.bind();
  uniform.apply(material->program);
  vao.unbind();
  material->program->unbind();
}

	
Mesh* Model::getMesh()
{
	return mesh;
}

	
} /* eeltech */

