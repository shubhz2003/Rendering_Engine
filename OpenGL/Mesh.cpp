#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_world = glm::mat4(1.0f);
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;

	m_vertexData = { 
		/* Position	   */	/*		RGBA Color		*/
		0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.3f, 1.1f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.4f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.7f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.6f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramID()); // Use our shader

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		7* sizeof(float),	// stride (7 floats per vertex definition)
		(void*) 0);			// array bufffer offset

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), // The attribute we want to configure
		4,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		7 * sizeof(float),				// stride (7 floats per vertex definition)
		(void*)(3 * sizeof(float)));	// array bufffer offset

	// 3rd attribute : WVP
	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_LINES, 0, m_vertexData.size() / 7); 	// Draw Lines
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrColors());
}