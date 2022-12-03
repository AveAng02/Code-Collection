
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window1 = glfwCreateWindow(720, 480, "OpenGL Playground", NULL, NULL);

	if (window1 == NULL)
	{
		std::cout << "Falied to create new window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window1);

	while (!glfwWindowShouldClose(window1))
	{
		glfwPollEvents();
	}



	glfwDestroyWindow(window1);
	glfwTerminate();

	return 0;
}


