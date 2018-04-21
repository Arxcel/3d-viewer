//
// Created by Arxcel on 4/21/18.
//

#include "FileLoader.hpp"


static inline unsigned int findNextChar(unsigned int start, const char* str, unsigned int length, char token);
static inline double parseSTLFloat(const std::string& token, unsigned int start, unsigned int end);
static inline void trim_left(std::string &src);
FileLoader::FileLoader(){
}

FileLoader::~FileLoader()
{
}


void FileLoader::loadAsciiStl(std::string const & filename) {
	std::ifstream file(filename);
	std::string line;
	std::string res;
	glm::vec3 n;

	if (file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			trim_left(line);
			const char lineCStr = line.c_str()[0];
			switch(lineCStr)
			{
				case 'f':
					n = parseVec3(line);
					break;
				case 'v':
					_vertices.push_back(Vertex(parseVec3(line), n));
					break;
				default: break;
			};
		}
	} else {
		throw Vertex::CustomException("File loading failed.");

	}
}

static inline void trim_left(std::string &src)
{
	char *tmp = const_cast<char *>(src.c_str());
	for (; *tmp == ' '; tmp++)
	{
		if (*tmp == '\0')
			break ;
	}
	std::string res(tmp);
	src = res;
}

glm::vec3 FileLoader::parseVec3(std::string const &v) {
	unsigned int tokenLength = v.length();
	const char* tokenString = v.c_str();

	unsigned int vertIndexStart = 0;

	while(vertIndexStart < tokenLength)
	{
		if((tokenString[vertIndexStart] >= 48 && tokenString[vertIndexStart] <= 57)
		   || tokenString[vertIndexStart] == 45
				|| tokenString[vertIndexStart] == 43)
			break;
		vertIndexStart++;
	}

	unsigned int vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	double x = parseSTLFloat(v, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	double y = parseSTLFloat(v, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	double z = parseSTLFloat(v, vertIndexStart, vertIndexEnd);
	return glm::vec3(x, y, z);
}

static inline unsigned int findNextChar(unsigned int start, const char* str, unsigned int length, char token)
{
	unsigned int result = start;
	while(result < length)
	{
		result++;
		if(str[result] == token)
			break;
	}

	return result;
}

static inline double parseSTLFloat(const std::string& token, unsigned int start, unsigned int end)
{
	std::string s;
	s = token.substr(start, end - start);
	double d = strtod(s.c_str(), nullptr);
	return d;
}

std::vector<Vertex> FileLoader::getVertices() const
{
	return _vertices;
}

std::vector<Triangle> FileLoader::getTriangles() const
{
	return _triangles;
}

void	FileLoader::generateTriangles()
{
	int tr = 0;
	std::vector<Vertex> ver;
	glm::vec3 xy(0,0,1);
	for(unsigned int i = 0; i < _vertices.size(); i++)
	{
		Vertex v = _vertices.at(i);
		ver.push_back(v);
		tr++;
		if (tr == 3)
		{
			Triangle t;
			t._vertices = ver;
			ver.clear();
			tr = 0;
			glm::vec3 n = *v.getNorm();
			t._angle = acos(glm::dot(n, xy)) * 180 / M_PI;
			float a = glm::distance(*t._vertices.at(0).getPos(),*t._vertices.at(1).getPos());
			float b = glm::distance(*t._vertices.at(1).getPos(),*t._vertices.at(2).getPos());
			float c = glm::distance(*t._vertices.at(0).getPos(),*t._vertices.at(2).getPos());
			float s=(a+b+c)/2;
			t._area = sqrt(s*(s-a)*(s-b)*(s-c));
			_triangles.push_back(t);
		}
	}
}
