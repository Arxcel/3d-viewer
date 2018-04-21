//
// Created by Arxcel on 4/21/18.
//

#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include "Vertex.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
class FileLoader {
public:
	FileLoader();
	void loadAsciiStl(std::string const & filename);
	virtual ~FileLoader();
	std::vector<Vertex> getVertices() const;
private:
	void parseFile(std::string const &l);
	void parseTriangle(std::string const &t);
	glm::vec3 parseVec3(std::string const &v);
	std::vector<Vertex> _vertices;
};


#endif
