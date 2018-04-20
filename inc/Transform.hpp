//
// Created by Arxcel on 4/20/18.
//

#ifndef BASIC_RAY_TRACER_TRANSFORM_HPP
#define BASIC_RAY_TRACER_TRANSFORM_HPP

#include "glm.hpp"

class Transform
{
public:
	Transform(glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3(), glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f)) :
	_pos(pos), _rot(rot), _scale(scale)
	{};
	glm::vec3 getPos() const { return _pos;}
	glm::vec3 getRot() const { return _rot;}
	glm::vec3 getScale() const { return _scale;}

private:
	glm::vec3 _pos;
	glm::vec3 _rot;
	glm::vec3 _scale;

};
#endif //BASIC_RAY_TRACER_TRANSFORM_HPP
