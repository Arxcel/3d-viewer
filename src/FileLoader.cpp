//
// Created by Arxcel on 4/21/18.
//

#include "FileLoader.hpp"

FileLoader::FileLoader(){

}
FileLoader::~FileLoader()
{
}

void FileLoader::loadAsciiStl(std::string const & filename) {
	std::ifstream file(filename);
	std::string line;
	std::string res;

	if (file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			res += line + "\n";
		}
	} else {
		throw Vertex::CustomException("File loading failed.");
	}
	parseFile(res);
}

static std::string trim_left(std::string src)
{
	char *tmp = const_cast<char *>(src.c_str());
	for (; *tmp == ' '; tmp++)
	{
		if (*tmp == '\0')
			break ;
	}
	std::string res(tmp);
	src = res;
	return src;
}

void FileLoader::parseFile(std::string const &l)
{
	std::string vStart = "facet";
	std::string vEnd = "endfacet";
	std::string tmp = l;
	size_t start;
	size_t len;
	size_t end;
	while (true)
	{
		if ((start = tmp.find(vStart)) != std::string::npos && (end = tmp.find(vEnd)) != std::string::npos)
		{
			start += vStart.length();
			len = end - start;
			parseTriangle(tmp.substr(start, len));
			tmp = tmp.substr(end + vEnd.length());
		} else {
			break;
		}
	}
}

void FileLoader::parseTriangle(std::string const &t)
{
	glm::vec3 normal(0.0, 0.0, 0.0);
	std::string n = "normal";
	std::string v = "vertex";
	size_t start;
	std::string tmp;
	std::stringstream ss(t);

	while (getline(ss, tmp))
	{
		if ((start = tmp.find(n)) != std::string::npos)
		{
			start += v.length();
			tmp = trim_left(tmp.substr(start));
			normal = parseVec3(tmp);
		}
		else if ((start = tmp.find(v)) != std::string::npos)
		{
			start += v.length();
			tmp = trim_left(tmp.substr(start));
			_vertices.push_back(Vertex(parseVec3(tmp), normal));
		}
	}
}

glm::vec3 FileLoader::parseVec3(std::string const &v) {
	std::stringstream ss(v);
	std::string s;
	glm::vec3 res;
	int i = 0;
	while (getline(ss, s, ' ' )) {
		std::stringstream tmp(s);
		tmp >> res[i];
		i++;
	}
	return res;
}

std::vector<Vertex> FileLoader::getVertices() const
{
	return _vertices;
}

