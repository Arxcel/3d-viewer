//
// Created by Arxcel on 4/20/18.
//

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Transform
{
public:
	Transform(glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3(), glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f)) :
	_pos(pos), _rot(rot), _scale(scale)
	{};

	glm::mat4 getModel() const
	{
		glm::mat4 translateMatrix = glm::translate(_pos);
		glm::mat4 rotXMatrix = glm::rotate(_rot.x, glm::vec3(1,0,0));
		glm::mat4 rotYMatrix = glm::rotate(_rot.y, glm::vec3(0,1,0));
		glm::mat4 rotZMatrix = glm::rotate(_rot.z, glm::vec3(0,0,1));
		glm::mat4 scaleMatrix = glm::scale(_scale);
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
		return translateMatrix * rotMatrix * scaleMatrix;
	}
	glm::vec3 &getPos()  { return _pos;}
	glm::vec3 &getRot()  { return _rot;}
	glm::vec3 &getScale()  { return _scale;}

	void setPos(glm::vec3 const &pos)  { _pos = pos;}
	void setRot(glm::vec3 const &rot)  { _rot = rot;}
	void setScale(glm::vec3 const &scale)  { _scale = scale;}
private:
	glm::vec3 _pos;
	glm::vec3 _rot;
	glm::vec3 _scale;

};
#endif //TRANSFORM_HPP
