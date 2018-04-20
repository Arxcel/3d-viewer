#include <iostream>
#include "../inc/Display.hpp"
#include "glew.h"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#define WIDTH 800
#define HEIGHT 600

int main() {
	Display d(WIDTH, HEIGHT, "3D Viewer");

	Vertex array[] = {Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0, 0.0)),
					  Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5, 1.0)),
					  Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0, 0.0))};
	Mesh m(array, sizeof(array) / sizeof(array[0]));
	Shader shader("./shaders/basicShader");
	Texture tex("./shaders/texture.jpg");
	Camera cam(glm::vec3(0,0,-3), 70.0f, static_cast<float>(WIDTH)/static_cast<float>(HEIGHT), 0.01f, 1000.0f);
	Transform transform;
	while (d.getIsRunning())
	{
		d.Clear(0.1f,0.1f,0.1f,1.0f);
		shader.Bind();
		tex.Bind(0);
		shader.update(transform, cam);
		m.draw();
		d.Update();
	}
	return 0;
}