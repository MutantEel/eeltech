//
//  Model.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <eeltech/graphics/Material.hpp>
#include <eeltech/graphics/VertexArray.hpp>
#include <eeltech/graphics/Mesh.hpp>
#include <eeltech/graphics/Uniform.hpp>
#include <glm/glm.hpp>

#include <vector>



namespace eeltech
{

/**
 * A class that holds all data to render an object
 */
class Model
{
  public:
    
    /**
     * A default constructor
     */
    Model();

    /**
     * A default destructor
     */
    ~Model();

    /**
     * draw the model
     */
    void draw();

    /**
     * sets the mesh of the model
     * @param the model's new mesh
     */
    void setMesh(Mesh* mesh);

    /**
     * sets the material of the model
     * @param the model's new material
     */
    void setMaterial(Material* material);

    /**
     * sets a uniform on the model
     * @param the uniform to set
     */
    void setUniform(Uniform& uniform);

    /**
     * @return the current mesh
     */
		Mesh* getMesh();
	
  protected:

    Material* material;   /**< the model's material     */
    Mesh* mesh;           /**< the model's mesh					*/
    VertexArray vao;			/**< the vertex array         */
};

  
} /* eeltech */

#endif  /* _MODEL_HPP_ */

