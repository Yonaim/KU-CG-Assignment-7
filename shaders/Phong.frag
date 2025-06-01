#version 330 core
// ─────────────────────────────────────────────────────────────
//  Fragment Shader: Phong Shading
// ─────────────────────────────────────────────────────────────
out vec4 FragColor;

in vec3 FragPos; // world position of the fragment
in vec3 Normal;  // world normal of the fragment

uniform vec3 uLightPos; // position of the light source (world)
uniform vec3 uViewPos;  // position of the camera (world)

// Light properties
uniform vec3 uLightAmbient;
uniform vec3 uLightDiffuse;
uniform vec3 uLightSpecular;

// Material properties
uniform vec3  uMatAmbient;
uniform vec3  uMatDiffuse;
uniform vec3  uMatSpecular;
uniform float uMatShininess;

// Gamma correction
uniform float uGamma;

void main()
{
	vec3 N = normalize(Normal);
	vec3 L = normalize(uLightPos - FragPos);
	vec3 V = normalize(uViewPos - FragPos);

	// 1) Ambient
	vec3 ambient = uLightAmbient * uMatAmbient;

	// 2) Diffuse (Lambert)
	float diff    = max(dot(N, L), 0.0);
	vec3  diffuse = uLightDiffuse * (diff * uMatDiffuse);

	// 3) Specular (Phong)
	vec3  R        = reflect(-L, N); // reflect light vector
	float spec     = pow(max(dot(V, R), 0.0), uMatShininess);
	vec3  specular = uLightSpecular * (spec * uMatSpecular);

	vec3 color = ambient + diffuse + specular;
	FragColor  = vec4(pow(color, vec3(1.0 / uGamma)), 1.0);
}
