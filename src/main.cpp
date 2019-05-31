#include <iostream>
#include "Display.hpp"
#include "GL/glew.h"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "FileLoader.hpp"
#include "PathKeeper.hpp"

#define WIDTH 800
#define HEIGHT 600

#undef main

int main(int ac, char *av[]) {

	try {
        std::string exePath(av[0]);
        std::string exeFolder(exePath.substr(0, exePath.find_last_of("\\/") + 1));
        PATHKEEPER.setBinFolder(exeFolder);
        std::string modelPath = PATHKEEPER.getBinFolder() + "stls/bunny.stl";
		FileLoader fl;
		fl.loadAsciiStl(modelPath);
		std::vector<Vertex> t = fl.getVertices();
		Display d(WIDTH, HEIGHT, "3D Viewer");
		Mesh m(t);
		Shader shader(PATHKEEPER.getBinFolder() + "shaders/basicShader");
		Camera cam(glm::vec3(0, 0, -25.0), 70.0f, static_cast<float>(WIDTH)/static_cast<float>(HEIGHT), 0.01f, 1000.0f);
		Transform transform(glm::vec3(0,0,0),glm::vec3(-90,0,0));
		while (d.getIsRunning())
		{
			d.clear(0.1f,0.1f,0.2f,1.0f);
			shader.Bind();
			shader.update(transform, cam);
			m.draw();
			d.update(transform, fl);
		}
	} catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}