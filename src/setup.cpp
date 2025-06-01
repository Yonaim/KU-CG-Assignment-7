#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "unit_sphere.hpp"
#include "Renderparams.hpp"

extern GLuint vao, vbo, ebo, prog;
extern RenderParams params;

#define WIN_WIDTH  512
#define WIN_HEIGHT 512

void setupOpenGL()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW init fail\n";
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *win
		= glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT,
						   "Assignment 7 - Phong Shading", nullptr, nullptr);
	if (!win)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(win);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW init fail\n";
		exit(-1);
	}
	glEnable(GL_DEPTH_TEST);
}

void setupSphereBuffers()
{
	std::vector<float> vertex_with_normal;
	for (int i = 0; i < gNumVertices; ++i)
	{
		float x = gVertexBuffer[3 * i + 0];
		float y = gVertexBuffer[3 * i + 1];
		float z = gVertexBuffer[3 * i + 2];
		vertex_with_normal.push_back(x);
		vertex_with_normal.push_back(y);
		vertex_with_normal.push_back(z);
		vertex_with_normal.push_back(x);
		vertex_with_normal.push_back(y);
		vertex_with_normal.push_back(z);
	}
	int stride = 6 * sizeof(float);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_with_normal.size() * sizeof(float),
				 vertex_with_normal.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, gNumTriangles * 3 * sizeof(int),
				 gIndexBuffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
						  (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void setRenderParams()
{
	params.eye       = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 center = params.eye - glm::vec3(0, 0, 1);
	glm::vec3 up(0, 1, 0);
	params.view = glm::lookAt(params.eye, center, up);

	float aspect = WIN_WIDTH / WIN_HEIGHT;
	float t = 0.1f, b = -0.1f;
	float r = t * aspect, l = -r;
	float n = 0.1f, f = 1000.0f;
	params.proj = glm::frustum(l, r, b, t, n, f);

	params.model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -7));
	params.model = glm::scale(params.model, glm::vec3(2, 2, 2));

	params.mat_ka        = glm::vec3(0.0f, 1.0f, 0.0f);
	params.mat_kd        = glm::vec3(0.0f, 0.5f, 0.0f);
	params.mat_ks        = glm::vec3(0.5f, 0.5f, 0.5f);
	params.mat_shininess = 32.0f;

	params.lightPos          = glm::vec3(-4.0f, 4.0f, -3.0f);
	params.lightColor        = glm::vec3(1.0f, 1.0f, 1.0f);
	params.ambient_intensity = 0.2f;
	params.gamma             = 2.2f;
}
