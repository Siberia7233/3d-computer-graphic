#include "shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    if (!vShaderFile.is_open() && !fShaderFile.is_open())
    {
        std::cout << "ERROR::HMFSHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    // ��ȡ�ļ��Ļ��嵽��������
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // �ر��ļ�������
    vShaderFile.close();
    fShaderFile.close();
    // ת����������string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    // ������λconst char
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // ������ɫ��
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    // ������ɫ��  ��������ʶ�����󶨣����룩�����루��ɫ��������ȡ������
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Ƭ����ɫ�� ��������ʶ�����󶨣����룩�����루��ɫ��������ȡ������
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // ��ɫ������ ����(��ʾ�����󶨣�����ɫ��id�������ӣ�ȫ�����ӵ���ɫ�������ʶ�ϣ�
    _id = glCreateProgram();
    glAttachShader(_id, vertex);
    glAttachShader(_id, fragment);
    glLinkProgram(_id);
    // ��ӡ���Ӵ�������еĻ���
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    // ʹ����ɫ��
    glUseProgram(_id);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()),(int)value);
}
//ʹ��������Ӧ��ȷ������Ԫ
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
unsigned int Shader::getId()
{
    return _id;
}




