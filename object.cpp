#include "object.h"


void object::drawObj(){

glewInit();

	GLuint VertexVBOID;
  glGenBuffers(1, &VertexVBOID);
  glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
  glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*indexed_vertices.size())+(sizeof(glm::vec3)*indexed_normals.size())+(sizeof(glm::vec2)*indexed_uvs.size()),0, GL_STATIC_DRAW);
  
  glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(glm::vec3)*indexed_vertices.size()), &indexed_vertices[0].x);                             // copy vertices starting from 0 offest
  
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*indexed_vertices.size(), sizeof(glm::vec3)*indexed_normals.size(), &indexed_normals[0].x);                // copy normals after vertices

  glBufferSubData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*indexed_vertices.size())+(sizeof(glm::vec3)*indexed_normals.size()), sizeof(glm::vec2)*indexed_uvs.size(), &indexed_uvs[0].x);




	GLuint IndexVBOID;
  glGenBuffers(1, &IndexVBOID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*indices.size(), &this->indices[0], GL_STATIC_DRAW);




// Define this somewhere in your header file
  #define BUFFER_OFFSET(i) ((char*)(i))
  


  glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3),0);    // The starting point of the VBO, for the vertices

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(glm::vec3),(char*)(sizeof(glm::vec3)*indexed_vertices.size()));      // The starting point of normals, 12 bytes away


  glClientActiveTexture(GL_TEXTURE0);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, sizeof(glm::vec3),(char*)(sizeof(glm::vec3)*indexed_vertices.size())+(sizeof(glm::vec3)*indexed_normals.size()) ); // The starting point of texcoords, 24 bytes away






 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, BUFFER_OFFSET(0)); 


}

void object::import(char *path){

	bool res = loadAssImp(path, this->indices, this->indexed_vertices, this->indexed_uvs, this->indexed_normals);
}