#include "Mesh.h"

Mesh::Mesh(const vector<Vertex> _vertices, const vector<unsigned int> _indices) :
	vertices{ _vertices }, indices{ _indices }
{
	initRenderingData();
}

Mesh::Mesh()
{
	vertices = vector<Vertex>();
	indices = vector<unsigned int>();
}

void Mesh::draw(Shader& shader)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_POLYGON, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::addLastVertexAtPosition(double x, double y)
{
	this->indices.push_back(this->indices.size() - 1 );
	this->vertices.push_back(Vertex{ glm::vec3(x, y, 0.0f) });
	initRenderingData();
}

void Mesh::removeLastVertex()
{
	this->vertices.pop_back();
	this->indices.pop_back();
	initRenderingData();
}



void Mesh::initRenderingData()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}
