#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "unit_sphere.h"

#include <string>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "Renderparams.h"

GLuint vao = 0, vbo = 0, ebo = 0; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
GLuint prog = 0; // GLSL program ID

RenderParams params;

void setupOpenGL();
void setupSphereBuffers();
void setRenderParams();
void renderLoop(GLFWwindow *win);
void cleanup();
GLuint createProgram(const std::string &vsPath, const std::string &fsPath);
GLuint compileShader(GLenum type, const char *src);


int main()
{
	setupOpenGL();
	create_unit_sphere();
	setupSphereBuffers();
	prog = createProgram("shaders/Phong.vert", "shaders/Phong.frag");
	setRenderParams();

	GLFWwindow *win = glfwGetCurrentContext();
	renderLoop(win);

	cleanup();
	return 0;
}

void renderLoop(GLFWwindow *win)
{
	auto loc
		= [&](const char *name) { return glGetUniformLocation(prog, name); };
	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(prog);

		glUniformMatrix4fv(loc("uModel"), 1, GL_FALSE,
						   glm::value_ptr(params.model));
		glUniformMatrix4fv(loc("uView"), 1, GL_FALSE,
						   glm::value_ptr(params.view));
		glUniformMatrix4fv(loc("uProj"), 1, GL_FALSE,
						   glm::value_ptr(params.proj));
		glUniform3fv(loc("uViewPos"), 1, glm::value_ptr(params.eye));
		glUniform3fv(loc("uLightPos"), 1, glm::value_ptr(params.lightPos));
		glUniform3fv(loc("uLightAmbient"), 1,
					 glm::value_ptr(glm::vec3(params.ambient_intensity)));
		glUniform3fv(loc("uLightDiffuse"), 1,
					 glm::value_ptr(params.lightColor));
		glUniform3fv(loc("uLightSpecular"), 1,
					 glm::value_ptr(params.lightColor));
		glUniform3fv(loc("uMatAmbient"), 1, glm::value_ptr(params.mat_ka));
		glUniform3fv(loc("uMatDiffuse"), 1, glm::value_ptr(params.mat_kd));
		glUniform3fv(loc("uMatSpecular"), 1, glm::value_ptr(params.mat_ks));
		glUniform1f(loc("uMatShininess"), params.mat_shininess);
		glUniform1f(loc("uGamma"), params.gamma);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, gNumTriangles * 3, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(win);
	}
}

void cleanup()
{
	glDeleteProgram(prog);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	free_sphere();
	glfwTerminate();
}
