
#include<iostream>
// #include<chrono>
// #include<thread>

#include<glad/glad.h>
#include<GLFW/glfw3.h>


#define HEIGHT 800
#define WIDTH 800


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



	GLFWwindow* window1 = glfwCreateWindow(HEIGHT, WIDTH, "OpenGL Playground", NULL, NULL);

	if (window1 == NULL) // checking if the window couldn't be created
	{
		std::cout << "Falied to create new window." << std::endl;
		glfwTerminate(); // terminating glfw
		return -1;
	}

	glfwMakeContextCurrent(window1); // marks the beginning of the window creation


	gladLoadGL();

	glViewport(0, 0, HEIGHT, WIDTH);


	////////////////////////////////////// Shader Work /////////////////////////////
	// GLuint is a custom type defined in OpenGL library
	// this line defines a new shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	glCompileShader(vertexShader);



	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(fragmentShader);



	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	///////////////////////////////////////////////////////////////////////////////

	GLfloat vertices[] =
	{
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f // Lower left corner
		 // Lower right corner
		 // Upper corner
	};


	GLuint VAO, VBO;

	// generate VAO and VBO with only only one object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // specify the color the background
	glClear(GL_COLOR_BUFFER_BIT); // clean the back buffer and assign new color to it
	glfwSwapBuffers(window1); // swap the back and front buffers


	while (!glfwWindowShouldClose(window1)) // infinite loop to keep the window open until close button is pressed
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // specify the color the background
		glClear(GL_COLOR_BUFFER_BIT); // clean the back buffer and assign new color to it

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Drawing the triangle

		glfwSwapBuffers(window1); // swap the back and front buffers


		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window1); // marks the end of window creation
	glfwTerminate(); // terminating glfw

	return 0;
}


