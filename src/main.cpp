#include <iostream>
#include "../inc/Display.hpp"
#include "glew.h"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

int main() {
	Display d(800, 600, "3D Viewer");

	Vertex array[] = {Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0, 0.0)),
					  Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5, 1.0)),
					  Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0, 0.0))};
	Mesh m(array, sizeof(array) / sizeof(array[0]));
	Shader shader("./shaders/basicShader");
	Texture tex("./shaders/texture.jpg");
	Transform transform;
	while (d.getIsRunning())
	{
		d.Clear(0.1f,0.1f,0.1f,1.0f);
		shader.Bind();
		tex.Bind(0);
		shader.update(transform);
		m.draw();
		d.Update();
	}
	return 0;
}