//
// Created by Arxcel on 4/18/18.
//

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include "SDL.h"
#include "Transform.hpp"
#include "FileLoader.hpp"

class FileLoader;
class Transform;
class Display {

public:
	Display(int width, int height, std::string const &name);
	virtual ~Display();
	void update(Transform &t, FileLoader &fl);
	bool getIsRunning() const;
	void clear(float r, float g, float b, float a);
	void key_down(int key, Transform &t, FileLoader &fl);
private:
	Display(Display const &) {};
	Display &operator=(Display const &){ return *this;};
	SDL_Window		*_w;
	SDL_GLContext	_glc;
	bool			isRunning;
};


#endif //DISPLAY_HPP
