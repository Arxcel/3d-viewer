//
// Created by Arxcel on 4/19/18.
//

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "glm/glm.hpp"
#include <exception>
#include <string>

class Vertex {
public:
	Vertex () {
		pos = glm::vec3(0,0,0);
		normale = glm::vec3(0,0,0);
	};
	Vertex(glm::vec3 const &pos, glm::vec3 const & normale)
	{
		this->pos = pos;
		this->normale = normale;
	}
	glm::vec3 *getPos()  { return &pos;};
	glm::vec3 *getNorm()  { return &normale;}
	class CustomException : public std::exception
	{
	public:
		CustomException(std::string const &text) {this->text = text;};
		virtual const char* what() const throw() {
			std::string res;
			res = "Exception: " + text;
			return (res.c_str());};
		std::string text;
		~CustomException() throw() {};
	};
private:
	glm::vec3 pos;
	glm::vec3 normale;
};


#endif //VERTEX_HPP
