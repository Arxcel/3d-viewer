//
// Created by Arxcel on 4/19/18.
//

#include "../inc/Mesh.hpp"
#include <vector>

Mesh::Mesh(Vertex *vs, unsigned int numVS, unsigned int *indecies, unsigned int numIn )
{
	_drawCount = numIn;
	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVS);
	texCoords.reserve(numVS);

	for (unsigned int i = 0; i< numVS; i++)
	{
		positions.push_back(*vs[i].getPos());
		texCoords.push_back(*vs[i].getTex());
	}
	glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVS * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVS * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER , numIn * sizeof(indecies[0]), &indecies[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Mesh::draw() {
	glBindVertexArray(_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0);
//	glDrawArrays(GL_TRIANGLES, 0, _drawCount);
	glBindVertexArray(0);
}