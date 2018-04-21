//
// Created by Arxcel on 4/19/18.
//

#ifndef MESH_HPP
#define MESH_HPP
#include "Vertex.hpp"
#include "glew.h"
#include <string>
#include <vector>
class Vertex;
class Mesh {
public:
	Mesh(std::vector<Vertex> &vs);
	virtual ~Mesh();
	void draw();
private:
	Mesh(Mesh const &) {};
	Mesh &operator=(Mesh const &){ return *this;}
	enum{
		POSITION_VB,
		NORMAL_VB,
		NUM_BUFFERS
	};
	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers[NUM_BUFFERS];
	unsigned int _drawCount;

};


#endif //MESH_HPP
