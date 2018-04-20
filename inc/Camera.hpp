//
// Created by Arxcel on 4/20/18.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm.hpp"
#include "gtx/transform.hpp"

class Camera {
public:
	Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
	{
		_perspective = glm::perspective(fov, aspect, zNear, zFar);
		_position = pos;
		_forward = glm::vec3(0, 0, 1);
		_up = glm::vec3(0, 1, 0);
	}
	glm::mat4 getViewProjection() const
	{
		return _perspective * glm::lookAt(_position, _position + _forward, _up);
	}
	private:
	glm::mat4 _perspective;
	glm::vec3 _position;
	glm::vec3 _forward;
	glm::vec3 _up;
};

#endif //CAMERA_HPP
