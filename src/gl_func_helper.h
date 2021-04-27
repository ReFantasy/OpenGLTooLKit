#ifndef __GL_FUNCTION__CALL__
#define __GL_FUNCTION__CALL__
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

#endif//__GL_FUNCTION__CALL__