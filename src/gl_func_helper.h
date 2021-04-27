#ifndef __GL_FUNCTION__CALL__
#define __GL_FUNCTION__CALL__
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


/**
 * @brief 检测GLFW创建窗口是否成功
*/
bool GLFWwindowTest(GLFWwindow*);

/**
 * @brief 初始化 glad
*/
bool GladInit();

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

/**
 * @brief 输入处理
*/
void GLProcessInput(GLFWwindow* window);

/**
 * @brief 检测着色器编译错误  
*/
int CompileShaderTest(unsigned int shader_id);

void GLInfo();

class Shader
{
public:
	unsigned int ID;
	// constructor generates the shader on the fly
	Shader(const char* vertexPath, const char* fragmentPath);

	// activate the shader
	void Use();

	// utility uniform functions
	void SetBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void SetInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void SetFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

private:
	// utility function for checking shader compilation/linking errors.
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif//__GL_FUNCTION__CALL__