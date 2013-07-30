//
//  Mesh.hpp
//  EelTech
//
// Created by Sean on 7/29/13.
// Copyright 2013 Mutant Eel. All rights reserved.
//

#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <eeltech/graphics/Buffer.hpp>
#include <eeltech/graphics/VertexArray.hpp>
#include <eeltech/graphics/ArrayAttribute.hpp>
#include <vector>


namespace eeltech
{

namespace mesh
{
  enum DrawType
  {
    Strip = GL_TRIANGLE_STRIP,
    Triangles = GL_TRIANGLES,
    Fan = GL_TRIANGLE_FAN,
		LineLoop = GL_LINE_LOOP,
  };
}

/**
 * A class that holds geometry data
 */
class Mesh
{
  public:

    /**
     * A default constructor
     */
    Mesh();

    /**
     * A default destructor
     */
    ~Mesh();

    /**
     * sets the vertex buffer data
     * @param the data for the vertices
     * @param the size of the vert data
     * @param the type of vertex buffer
     */
    void setVerts(void* vertData, int vertDataSize, buffer::Type type = buffer::Static);


    /**
     * sets the index buffer data
     * @param the data for the indices
     * @param the size of the indices data
     * @param the type of index buffer
     */
    void setIndices(void* idxData, int idxDataSize, buffer::Type type = buffer::Static);

    /**
     * sets the number of elements are in the mesh
     * @param number of elements in the mesh
     */
    void setNumElements(int numElements);

    /**
     * sets the method on how to draw the elements
     * @param draw method for the elements
     */
    void setDrawType(mesh::DrawType type);

    /**
     * binds the mesh for use
     */
    void bind();

    /**
     * unbinds the mesh for use
     */
    void unbind();

    /**
     * adds an attribute
     * @param the attribute to add
     */
    void addAttribute(ArrayAttribute attribute);


    void updateVertices(void* data, int length);
	
		void updateIndices(void* data, int length);

    std::vector<ArrayAttribute> attributes; /**< vertex array Attributes              */

		void* getVertData(int* length);
	
		void* getIndexData(int* length);

		mesh::DrawType getDrawType();
	
		int getNumElement();

  protected:

    int numElements;                        /**< number of elements in the mesh								*/
    mesh::DrawType drawType;                /**< how to draw the elements in the mesh					*/
    Buffer vertBuffer;                      /**< the vertex buffer														*/
    Buffer idxBuffer;                       /**< the index buffer															*/
    float* vertData;                        /**< stores the vert data if the type is dynamic	*/
};


} /* eeltech */

#endif  /* _MESH_HPP_ */

