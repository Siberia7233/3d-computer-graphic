#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//绘制场景
void renderScene()
{
	glClearColor(0.3f, 0.6f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glRotatef(0.1, 0.0f, 0.0f, 1.0f);		
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(0.0, 0.5, 0.0);
	glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, -0.5, 0.0);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	glFlush();
}
//处理用户输入
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
//改变窗口大小
void changeSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
//主函数
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(2000, 1500, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, changeSize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		renderScene();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}








////#include <头文件>
//int main()
//{
//	// （1）建立渲染窗口
//	// （2）进入渲染循环
//	while (true) {
//		// （2.1）处理用户输入
//		// （2.2）渲染场景		
//	}
//	// （3）销毁窗口，结束程序
//}
