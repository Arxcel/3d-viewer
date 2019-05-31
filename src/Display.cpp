//
// Created by Arxcel on 4/18/18.
//
#include "Display.hpp"
#include "GL/glew.h"
#include <iostream>

Display::Display(int wW, int wH, std::string const &name)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

bool Display::getIsRunning() const {
	return isRunning;
}

Display::~Display() {
	SDL_GL_DeleteContext(_glc);
	SDL_DestroyWindow(_w);
	SDL_Quit();
}

void Display::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


static void			pos_object(int key,  Transform &t)
{
	if (key == SDLK_w)
		t.getPos().z += 0.3512;
	else if (key == SDLK_s)
		t.getPos().z -= 0.3512;
	else if (key == SDLK_a)
		t.getPos().x += 0.3512;
	else if (key == SDLK_d)
		t.getPos().x -= 0.3512;
	else if (key == SDLK_q)
		t.getPos().y += 0.3512;
	else if (key == SDLK_e)
		t.getPos().y -= 0.3512;
	else if (key == SDLK_SPACE)
	{
		t.setPos(glm::vec3(0,0,0));
		t.setRot(glm::vec3(0,0,0));
		t.setScale(glm::vec3(1,1,1));
	}
}

static void			rot_object(int key,  Transform &t)
{
	if (key == SDLK_i)
		t.getRot().x += 0.1;
	else if (key == SDLK_k)
		t.getRot().x -= 0.1;
	else if (key == SDLK_j)
		t.getRot().y += 0.1;
	else if (key == SDLK_l)
		t.getRot().y -= 0.1;
	else if (key == SDLK_u)
		t.getRot().z += 0.1;
	else if (key == SDLK_o)
		t.getRot().z -= 0.1;
}

void		Display::key_down(int key, Transform &t, FileLoader &fl)
{
	if (key == SDLK_ESCAPE)
		isRunning = false;
	else if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d
			 || key == SDLK_q || key == SDLK_e || key == SDLK_SPACE)
	{
		pos_object(key, t);
	}
	else if (key == SDLK_i || key == SDLK_k || key == SDLK_j || key == SDLK_l
			 || key == SDLK_u || key == SDLK_o)
	{
		rot_object(key, t);
	}
	else if (key == SDLK_z)
	{
		fl.generateTriangles();
		fl.createHisto();
	}
}

void Display::update(Transform &t, FileLoader &fl) {
	SDL_GL_SwapWindow(_w);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			isRunning = false;
		else if (e.type == SDL_KEYDOWN)
			key_down(e.key.keysym.sym, t, fl);	}
}