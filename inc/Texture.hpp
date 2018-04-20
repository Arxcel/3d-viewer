//
// Created by Arxcel on 4/19/18.
//

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

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


#endif //TEXTURE_HPP
