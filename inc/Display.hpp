//
// Created by Arxcel on 4/18/18.
//

#ifndef BASIC_RAY_TRACER_DISPLAY_HPP
#define BASIC_RAY_TRACER_DISPLAY_HPP

#include <string>
#include "SDL.h"

class Display {

public:
	Display(int width, int height, std::string const &name);
	virtual ~Display();
	void Update();
	bool getIsRunning() const;
	void Clear(float r, float g, float b, float a);
private:
	Display(Display const &) {};
	Display &operator=(Display const &){ return *this;};
	SDL_Window		*_w;
	SDL_GLContext	_glc;
	bool			isRunning;
};


#endif //BASIC_RAY_TRACER_DISPLAY_HPP
