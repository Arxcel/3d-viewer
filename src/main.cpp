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

int main() {

	FileLoader fl;
	fl.loadAsciiStl("./stls/box_1x1x1.stl");
	std::cout << "file loaded " << std::endl;
	std::vector<Vertex> t = fl.getVertices();
	Display d(WIDTH, HEIGHT, "3D Viewer");
	Mesh m(t);
	Shader shader("./shaders/basicShader");
	Camera cam(glm::vec3(0, 0, -10), 70.0f, static_cast<float>(WIDTH)/static_cast<float>(HEIGHT), 0.01f, 1000.0f);
	Transform transform;
	unsigned int counter = 0;
	fl.generateTriangles();
	std::vector<Triangle> tr = fl.getTriangles();
		for (unsigned int i = 0 ; i < tr.size(); i++)
		{
			std::cout << "Triangle " << i << ": " << std::endl << "area: " << tr.at(i)._area << std::endl
					  << "angle: " << tr.at(i)._angle << std::endl;
//			std::cout << tr.at(i)._vertices.size() << std::endl;
		}


	while (d.getIsRunning())
	{
		d.Clear(0.1f,0.1f,0.2f,1.0f);
		shader.Bind();
		shader.update(transform, cam);
		m.draw();
		d.Update(transform);
		counter+=200;
	}
	return 0;
}