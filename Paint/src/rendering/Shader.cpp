#include "../../../stdafx.h"
#include "../io/file.h"
#include "Shader.h"

GLuint Shader::compile(std::string shader, GLenum type)
{
	GLuint id = glCreateShader(type);
	const char* shaderCode = shader.c_str();

	glShaderSource(id, 1, &shaderCode, NULL);
	glCompileShader(id);

	this->compileStatus(id);

	return id;
}

void Shader::linkProgramme(GLuint vertexShaderId, GLuint fragmentShaderId)
{
	programId = glCreateProgram();
	if (programId == 0 || programId == GL_INVALID_OPERATION)
		printf("SHADER : not able to create the shader object properly.\n Program ID : %d", programId);
	vertId = vertexShaderId;
	fragId = fragmentShaderId;
	glAttachShader(programId, vertId);
	glAttachShader(programId, fragId);
	glLinkProgram(programId);

	this->linkStatus();

}

void Shader::compileStatus(GLuint shaderId)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		spdlog::error("--- SHADER: Shader {} did not compile ! \n===\n%s\n===\n {}", shaderId, infoLog);
	}
	else
	{
		spdlog::info("--- SHADER: Shader {} loaded and compiled proprely\n", shaderId);
	}
}

void Shader::linkStatus()
{
	int success;
	GLint linkStatus;
	char infoLog[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		spdlog::error("--- SHADER: Program linking failed : \n===\n%s\n===\n {}", infoLog);
	}
	else {
		spdlog::info("--- SHADER: Program {} link properly\n", programId);
		glGetProgramiv(programId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			spdlog::error("--- SHADER: Program did not compile : \n===\n%s\n===\n {}", infoLog);
		}
		else
		{
			spdlog::info("--- SHADER: Program {} loaded and compiled proprely.\n", programId);
		}
	}

}

Shader::Shader(std::string vertex_path, std::string fragment_path)
{
	programId = 0;
	GLuint v_id = this->compile(File::read(vertex_path), GL_VERTEX_SHADER);
	GLuint f_id = this->compile(File::read(fragment_path), GL_FRAGMENT_SHADER);
	this->linkProgramme(v_id, f_id);
}

Shader::Shader()
{
	
}

void Shader::use()
{
	glUseProgram(programId);
}

void Shader::terminate()
{
	glDetachShader(programId, vertId);
	glDetachShader(programId, fragId);
	glDeleteShader(vertId);
	glDeleteShader(fragId);
	glDeleteProgram(programId);
}
