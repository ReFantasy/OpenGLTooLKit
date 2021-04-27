#include "gl_func_helper.h"
#include <iostream>

bool GLFWwindowTest(GLFWwindow* window)
{
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}

bool GladInit()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int CompileShaderTest(unsigned int shader_id)
{
	int  success;
	char infoLog[1024];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_id, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	
	}

	return success;
}

void GLInfo()
{
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "INFO:Maximum number of vertex attributes supported: " << nrAttributes << std::endl;
}
