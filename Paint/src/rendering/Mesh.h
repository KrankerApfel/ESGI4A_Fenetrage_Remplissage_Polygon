#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "../../../stdafx.h"
#include "Shader.h"
using namespace std;


struct Vertex {
	glm::vec3 Position{};
	glm::vec3 Normal{};
	glm::vec2 TexCoords{};
	glm::vec3 Tangent{};
	glm::vec3 Bitangent{};
};

class Mesh {

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	unsigned int VAO;

	Mesh(const vector<Vertex> vertices, const vector<unsigned int> indices);
	void draw(Shader& shader);

private:
	unsigned int VBO, EBO;
	void initRenderingData();
};
