//
// Created by Arxcel on 4/19/18.
//

#ifndef BASIC_RAY_TRACER_TEXTURE_HPP
#define BASIC_RAY_TRACER_TEXTURE_HPP

#include "glew.h"
#include <string>

class Texture {
public:
	Texture(std::string const &filename);
	virtual ~Texture();
	void Bind(unsigned int unit);
private:
	Texture(Texture const &) {};
	Texture &operator=(Texture const &){ return *this;}

	GLuint _texture;
};


#endif //BASIC_RAY_TRACER_TEXTURE_HPP
