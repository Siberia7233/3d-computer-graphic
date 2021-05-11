#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

class Shader {
	public:
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		void use();
private:
	unsigned int _id;
};
#endif