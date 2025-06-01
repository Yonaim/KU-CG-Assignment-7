#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

static GLuint compileShader(GLenum type, const char *src)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint ok;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		char buf[512];
		glGetShaderInfoLog(shader, 512, nullptr, buf);
		std::cerr << "Shader compilation failed:\n" << buf << std::endl;
	}
	return shader;
}

GLuint createProgram(const std::string &vsPath, const std::string &fsPath)
{
	auto readFile = [](const std::string &p) {
		std::ifstream     ifs(p);
		std::stringstream ss;
		ss << ifs.rdbuf();
		return ss.str();
	};
	const std::string vsSrc = readFile(vsPath);
	const std::string fsSrc = readFile(fsPath);

	GLuint vs = compileShader(GL_VERTEX_SHADER, vsSrc.c_str());
	GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSrc.c_str());

	GLuint prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return prog;
}
