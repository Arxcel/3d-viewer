//
// Created by Arxcel on 4/19/18.
//

#include "../inc/Shader.hpp"
#include <fstream>
#include <iostream>

Shader::	Shader(std::string const &filename) {
	_prog = glCreateProgram();
	_shaders[0] = createShader(loadShader(filename + ".vx"), GL_VERTEX_SHADER);
	_shaders[1] = createShader(loadShader(filename + ".ft"), GL_FRAGMENT_SHADER);
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(_prog, _shaders[i]);
	glBindAttribLocation(_prog, 0, "position");
	glBindAttribLocation(_prog, 1, "texCoord");
	glLinkProgram(_prog);
	checkShaderError(_prog, GL_LINK_STATUS, true, "Error: Program linkage failed.");
	glValidateProgram(_prog);
	checkShaderError(_prog, GL_VALIDATE_STATUS, true, "Error: Program validation failed.");

	_uniforms[TRANSFORM_U] = glGetUniformLocation(_prog, "transform");
}

Shader::~Shader() {
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(_prog, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}
	glDeleteProgram(_prog);
}

void Shader::Bind() {
	glUseProgram(_prog);
}

void Shader::update(Transform const &transform, Camera const &cam)
{
	glm::mat4 model= cam.getViewProjection() * transform.getModel();
	glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

GLuint Shader::createShader(std::string const &text, GLenum shaderType) {
	GLuint  shader = glCreateShader(shaderType);
	if (shader == 0)
		std::cerr << "Error: shader creation failed!" << std::endl;
	const GLchar *shaderSourceStrings[1];
	GLint shaderSourceStringsLength[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringsLength[0] = text.length();
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLength);
	glCompileShader(shader);
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed.");
	return shader;
}

std::string Shader::loadShader(std::string const &fname)
{
	std::ifstream file;
	std::string res;
	std::string line;

	file.open(fname);
	if (file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			res += line + "\n";
		}
	} else {
		std::cerr << "Can not open file." << std::endl;
	}
	return res;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string const &errMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);
	if (success == GL_FALSE)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << errMessage << ": '" << error << "'" << std::endl;
	}
}