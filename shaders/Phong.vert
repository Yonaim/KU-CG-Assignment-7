#version 330 core
// ─────────────────────────────────────────────────────────────
//                Vertex Shader : Phong Shading
// ─────────────────────────────────────────────────────────────

// input: data from vertex buffer
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

// output: data to fragment shader
out vec3 FragPos; // world position of the vertex
out vec3 Normal;  // normal vector in world space

// uniform: data from application
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
	vec4 worldPos = uModel * vec4(aPos, 1.0);
	FragPos       = worldPos.xyz;

	mat3 normalMat = transpose(inverse(mat3(uModel)));
	Normal         = normalize(normalMat * aNormal);

	gl_Position = uProj * uView * worldPos; // to clip space
}
