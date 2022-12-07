
#include<iostream>
#include<chrono>
#include<thread>


#include<glad/glad.h>
#include<GLFW/glfw3.h>



const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vex3 aPos;\n"
"void main()\n"
"{\n"
"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";




int main()
{
	glfwInit(); // initializing glfw


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // accessing glfw core profiles only 


	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // left corner
		0.5f, 0.5f, 0.0f, // right corner
		0.0f, 0.5f, 0.0f // top corner
	};


	GLFWwindow* window1 = glfwCreateWindow(720, 480, "OpenGL Playground", NULL, NULL);

	if (window1 == NULL)
	{
		std::cout << "Falied to create new window." << std::endl;
		glfwTerminate(); // terminating glfw
		return -1;
	}

	glfwMakeContextCurrent(window1); // marks the beginning of the window creation


	gladLoadGL();

	glViewport(0, 0, 720, 480);


	glClearColor(0.225f, 0.0f, 0.0f, 1.0f); // specify the color the background
	glClear(GL_COLOR_BUFFER_BIT); // clean the back buffer and assign new color to it
	glfwSwapBuffers(window1); // swap the back and front buffers


	while (!glfwWindowShouldClose(window1)) // infinite loop to keep the window open until close button is pressed
	{
		glfwPollEvents();
	}


	glfwDestroyWindow(window1); // marks the end of window creation
	glfwTerminate(); // terminating glfw

	return 0;
}


