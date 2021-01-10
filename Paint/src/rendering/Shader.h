#pragma once
#include "../../../stdafx.h"



class Shader {

private:
	GLuint programId;

	GLuint compile(std::string shader, GLenum type);
	void linkProgramme(GLuint vertexShaderId, GLuint fragmentShaderId);
	void compileStatus(GLuint shaderId);
	void linkStatus();

public:
	Shader(std::string vertex_path, std::string fragment_path);
	void use();
	GLuint getProgramId() { return programId; }

	void setFloat(const char* key, GLfloat value) { glUniform1f(glGetUniformLocation(programId, key), value); }
};