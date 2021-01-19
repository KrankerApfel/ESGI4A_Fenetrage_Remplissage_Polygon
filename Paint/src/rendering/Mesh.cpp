#include "Mesh.h"

Mesh::Mesh(const vector<Vertex> _vertices, const vector<unsigned int> _indices) :
	vertices{ _vertices }, indices{ _indices }
{
	initRenderingData();
}

Mesh::Mesh()
{
	this->vertices = vector<Vertex>();
	this->indices = vector<unsigned int>();
}

void Mesh::draw(Shader& shader)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_LINE_LOOP, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::addLastVertexAtPosition(double x, double y)
{
	this->indices.push_back(this->indices.size());
	this->vertices.push_back(Vertex{ glm::vec3(x, y, 0.0f) });
	initRenderingData();
}

void Mesh::removeLastVertex()
{
	this->vertices.pop_back();
	this->indices.pop_back();
	initRenderingData();
}

void Mesh::terminate()
{
	glGenVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}



void Mesh::initRenderingData()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// vertex position attribut
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// vertex normals attribut
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);

	// vertex texture attribut
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}
