//
// Created by Arxcel on 4/19/18.
//

#ifndef BASIC_RAY_TRACER_VERTEX_HPP
#define BASIC_RAY_TRACER_VERTEX_HPP

#include "glm.hpp"

class Vertex {
public:
	Vertex(glm::vec3 const &pos, glm::vec2 const & texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}
	glm::vec3 *getPos()  { return &pos;};
	glm::vec2 *getTex()  { return &texCoord;}
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};


#endif //BASIC_RAY_TRACER_VERTEX_HPP