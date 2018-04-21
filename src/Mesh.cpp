//
// Created by Arxcel on 4/19/18.
//

#include "Mesh.hpp"
#include <vector>

Mesh::Mesh(std::vector<Vertex> &vs)
{
	_drawCount = vs.size();
	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	std::vector<glm::vec3> positions;

	positions.reserve(vs.size());

	for (unsigned int i = 0; i < vs.size(); i++)
	{
		positions.push_back(*vs.at(i).getPos());
	}
	glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, vs.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Mesh::draw() {
	glBindVertexArray(_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, _drawCount);
	glBindVertexArray(0);
}