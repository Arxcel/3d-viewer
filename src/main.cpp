#include <iostream>
#include "Display.hpp"
#include "glew.h"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "FileLoader.hpp"
#define WIDTH 800
#define HEIGHT 600

int main(int ac, char *av[]) {

	try {
		if (ac != 2)
		{
			std::cout << "usage: ./3d_viewer [file.stl]" << std::endl;
			return 0;
		}
		FileLoader fl;
		fl.loadAsciiStl(av[1]);
		std::vector<Vertex> t = fl.getVertices();
		Display d(WIDTH, HEIGHT, "3D Viewer");
		Mesh m(t);
		Shader shader("./shaders/basicShader");
		Camera cam(glm::vec3(0, 0, -25.0), 70.0f, static_cast<float>(WIDTH)/static_cast<float>(HEIGHT), 0.01f, 1000.0f);
		Transform transform;
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