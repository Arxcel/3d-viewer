//
// Created by Arxcel on 4/18/18.
//
#include "Display.hpp"
#include "glew.h"
#include <iostream>

Display::Display(int wW, int wH, std::string const &name)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	_w = SDL_CreateWindow(name.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, wW, wH, SDL_WINDOW_OPENGL);
	_glc = SDL_GL_CreateContext(_w);
	glewExperimental = GL_TRUE;
//	glewInit();
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Initialization failed (Glew)!" << std::endl;
	}
	isRunning = true;
}

bool Display::getIsRunning() const {
	return isRunning;
}

Display::~Display() {
	SDL_GL_DeleteContext(_glc);
	SDL_DestroyWindow(_w);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Display::Update() {
	SDL_GL_SwapWindow(_w);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			isRunning = false;
	}
}