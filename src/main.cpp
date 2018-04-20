#include <iostream>
#include "../inc/Display.hpp"
#include "glew.h"
#include "../inc/Mesh.hpp"
#include "../inc/Shader.hpp"
#include "../inc/Texture.hpp"
int main() {
	Display d(800, 600, "3D Viewer");

	Vertex array[] = {Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0, 0.0)),
					  Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5, 1.0)),
					  Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0, 0.0))};
	Mesh m(array, sizeof(array) / sizeof(array[0]));
	Shader shader("./shaders/basicShader");
	Texture tex("./shaders/texture.jpg");
	while (d.getIsRunning())
	{
		d.Clear(0.1f,0.0f,0.0f,1.0f);
		shader.Bind();
		tex.Bind(0);
		m.draw();
		d.Update();
	}
	return 0;
}