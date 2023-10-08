#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;

class Mesh
{
public:
	//Constructors/Destructors
	Mesh();
	virtual ~Mesh();

	// Methods
	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp); 
	void HandleInput(GLFWwindow* _window, glm::vec3& _position, glm::vec3& _rotation);
	//void updateNPCTriangles();
	//Technically _wvp is only _vp since world matrix exists in this contextand mesh has its own

private:
	Shader* m_shader;
	GLuint m_vertexBuffer; // GPU buffer
	GLuint m_indexBuffer; // GPU buffer
	std::vector<GLfloat> m_vertexData; // Store vertex data in RAM
	std::vector<GLubyte> m_indexData; // Store index data in RAM
	glm::mat4 m_world;
	std::vector<GLfloat> m_colorNPC;

};

#endif // !MESH_H


