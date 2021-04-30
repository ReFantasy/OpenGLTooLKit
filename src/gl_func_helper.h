#ifndef __GL_FUNCTION__CALL__
#define __GL_FUNCTION__CALL__
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include <functional>


/**
 * @brief 检测GLFW创建窗口是否成功
*/
bool GLFWwindowTest(GLFWwindow*);

/**
 * @brief 初始化 glad
*/
bool GladInit();


/**
 * @brief 检测着色器编译错误
*/
int CompileShaderTest(unsigned int shader_id);

void GLInfo();

class GLSLProgram
{
public:
	unsigned int prog_id;

	// construct program from strings
	GLSLProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	// activate the shader
	void Enable() { glUseProgram(prog_id); }
	void Disable() { glUseProgram(0); }

	// utility uniform functions
	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(prog_id, name.c_str()), (int)value);
	}
	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(prog_id, name.c_str()), value);
	}
	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(prog_id, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(prog_id, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(prog_id, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(prog_id, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(prog_id, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(prog_id, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(prog_id, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(prog_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(prog_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(prog_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}


private:
	// utility function for checking shader compilation/linking errors.
	void checkCompileErrors(unsigned int shader, std::string type);
};


unsigned int Load2DTexture(const char* filename);

class Interactor
{
public:
	static std::shared_ptr<Camera> camera;

	static void Init(GLFWwindow* window)
	{
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetKeyCallback(window, key_callback);
	}

private:

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			GetMouseStatus()->mouse_left_button_press = 1;
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			GetMouseStatus()->mouse_left_button_press = 0;
		}
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{

		/*
		 *  鼠标左键按下时，移动鼠标改变视角
		 */
		static bool firstMouse = true;
		static double lastX, lastY;

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		if (GetMouseStatus()->mouse_left_button_press == 1)
		{
			camera->ProcessMouseMovement(xoffset, yoffset);
		}

	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera->ProcessMouseScroll(yoffset);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		/*static float currentFrame ,deltaTime, lastFrame;
		currentFrame = (float)glfwGetTime();
	    deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->ProcessKeyboard(RIGHT, deltaTime);*/
	}


	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
private:
	struct KeyMouseStatus
	{
		int mouse_left_button_press;
	};

	static std::shared_ptr<KeyMouseStatus> GetMouseStatus()
	{
		static std::shared_ptr<KeyMouseStatus> mouse_status_ptr = std::make_shared<KeyMouseStatus>();
		return mouse_status_ptr;
	}

};


#endif//__GL_FUNCTION__CALL__