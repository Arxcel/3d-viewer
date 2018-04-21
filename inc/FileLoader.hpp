//
// Created by Arxcel on 4/21/18.
//

#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include "Vertex.hpp"

class Triangle {
public:
	Triangle(){
		_vertices.reserve(3);
		_area = 0;
		_angle = 0;
	}
	std::vector<Vertex>		_vertices;
	float 					_area;
	float					_angle;
};

class FileLoader {
public:
	FileLoader();
	void loadAsciiStl(std::string const & filename);
	virtual ~FileLoader();
	std::vector<Vertex> getVertices() const;
	std::vector<Triangle> getTriangles() const;

	glm::vec3 parseVec3(std::string const &v);
	void	generateTriangles();
private:
	std::vector<Vertex>		_vertices;
	std::vector<Triangle>	_triangles;
};


#endif
