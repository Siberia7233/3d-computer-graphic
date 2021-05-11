
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#define PI 3.1415926535

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void renderPoint();
void renderLine();
void renderTriangle();
void renderQuads();
void renderCircle(double circle_points);

int main() {
	
	glfwInit();

	//create glfw window
	GLFWwindow* window = glfwCreateWindow(1600, 1600, "LearOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	//render loop
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);
		//
		//render
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderPoint();
		renderLine();
		renderTriangle();
		renderQuads();
		renderCircle(1000);
		//

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	
	return 0;

}

//resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//input
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//render line
void renderLine()
{
	glColor3f(0.82f, 0.46f, 0.15f);
	glLineWidth(10);
	
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.25, 0.75, 0.0);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
	glEnd();
}

//render point
void renderPoint()
{
	glColor3f(0.82f, 0.46f, 0.15f);
	glPointSize(30);

	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
		glVertex3f(-0.75, 0.75, 0.0);
		glVertex3f(-0.25, 0.75, 0.0);
		glVertex3f(-0.25, 0.25, 0.0);
		glVertex3f(-0.75, 0.25, 0.0);
	glEnd();
	
}

//render triangle
void renderTriangle() {
	
	glColor3f(0.82f, 0.46f, 0.15f);
	

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.25, 0.0);
		glVertex3f(-0.75, -0.75, 0.0);
		glVertex3f(-0.25, -0.75, 0.0);
	
	glEnd();

}

//render quads
void renderQuads()
{
	glColor3f(0.82f, 0.46f, 0.15f);
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(5);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
		glVertex3f(0.2, -0.75, 0.0);
		glVertex3f(0.4, -0.25, 0.0);
		glVertex3f(0.6, -0.25, 0.0);
		glVertex3f(0.8, -0.75, 0.0);
	glEnd();
	
}

//render circle
void renderCircle(double circle_points) {
	glColor3f(0.82f, 0.46f, 0.15f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circle_points; i++) {
		float angle = (2 * PI / circle_points * i);
		glVertex2f(0.1*cos(angle), 0.1*sin(angle));
	}
	glEnd();
}
