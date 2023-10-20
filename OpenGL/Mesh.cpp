#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_texture = { };
	m_texture2 = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_lightPosition = { 0, 0, 0 };
	m_lightColor = { 1, 1, 1 };
}

Mesh::~Mesh()
{
}


void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	m_texture.Cleanup();
	m_texture2.Cleanup();
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;

	m_texture = Texture();
	m_texture.LoadTexture("../Assets/Textures/Wood.jpg");
	m_texture2 = Texture();
	m_texture2.LoadTexture("../Assets/Textures/Emoji.jpg");

#pragma region VertexData
	m_vertexData = { 
		/* Position */				/* Normals */	/* Texture Coords*/
		-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, // bottom-left
		0.5f, -0.5f, -0.5f,		 0.0f, 1.0f, 0.0f,	 1.0f, 0.0f, // bottom-left
		0.5f, 0.5f, -0.5f,		 1.0f, 0.0f, 0.0f,	 1.0f, 1.0f, // top-right
		0.5f, 0.5f, -0.5f,		 1.0f, 0.0f, 0.0f,	 1.0f, 1.0f, // top-right
		-0.5f, 0.5f, -0.5f,		 1.0f, 1.0f, 1.0f,	 0.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,	 0.0f, 0.0f  //bottom-left

		//-0.5f, -0.5f, 0.5f,		 0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,
		//0.5f, -0.5f, 0.5f,		 0.0f, 0.0f, 1.0f,	 1.0f, 0.0f,
		//0.5f, 0.5f, 0.5f,		 0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		//0.5f, 0.5f, 0.5f,		 0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		//-0.5f, 0.5f, 0.5f,		 0.0f, 0.0f, 1.0f,	 0.0f, 1.0f,
		//-0.5f, -0.5f, 0.5f,		 0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,

		//-0.5f, 0.5f, 0.5f,		 -1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
		//-0.5f, 0.5f, -0.5f,		 -1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		//-0.5f, -0.5f, -0.5f,	 -1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
		//-0.5f, -0.5f, -0.5f,	 -1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
		//-0.5f, -0.5f, 0.5f,		 -1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		//-0.5f, 0.5f, 0.5f,		 -1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,

		//0.5f, 0.5f, 0.5f,		 1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
		//0.5f, 0.5f, -0.5f,		 1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		//0.5f, -0.5f, -0.5f,		 1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
		//0.5f, -0.5f, -0.5f,		 1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
		//0.5f, -0.5f, 0.5f,		 1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		//0.5f, 0.5f, 0.5f,		 1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,

		//-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f, 0.0f,	 0.0f, 1.0f,
		//0.5f, -0.5f, -0.5f,		 0.0f, -1.0f, 0.0f,	 1.0f, 1.0f,
		//0.5f, -0.5f, 0.5f,		 0.0f, -1.0f, 0.0f,	 1.0f, 0.0f,
		//0.5f, -0.5f, 0.5f,		 0.0f, -1.0f, 0.0f,	 1.0f, 0.0f,
		//-0.5f, -0.5f, 0.5f,		 0.0f, -1.0f, 0.0f,	 0.0f, 0.0f,
		//-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f, 0.0f,	 0.0f, 1.0f,

		//-0.5f, 0.5f, -0.5f,		 0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
		//0.5f, 0.5f, -0.5f,		 0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,
		//0.5f, 0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
		//0.5f, 0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
		//-0.5f, 0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,	 0.0f, 0.0f,
		//-0.5f, 0.5f, -0.5f,		 0.0f, 1.0f, 0.0f,	 0.0f, 1.0f
	};
#pragma endregion

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

}

void Mesh::BindAttributes()
{

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		8 * sizeof(float),	// stride (8 floats per vertex definition)
		(void*)0);			// array bufffer offset

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(), // The attribute we want to configure
		3,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		8 * sizeof(float),				// stride (8 floats per vertex definition)
		(void*)(3 * sizeof(float)));	// array bufffer offset

	// 3rd attribute buffer : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The attribute we want to configure
		2,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		8 * sizeof(float),				// stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float)));	// array bufffer offset

	// 4th attribute : WVP
	//m_world = glm::rotate(m_world, 0.01f, { 0, 1, 0 }); // Y-axis rotation
	//_wvp *= m_world;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer

	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());
	glUniform1i(m_shader->GetSampler1(), 0); // Texture unit 0
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2.GetTexture());
	glUniform1i(m_shader->GetSampler2(), 1); // Texture unit 1

}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _wvp)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetVec3("AmbientLight", { 1.0f, 1.0f, 1.0f });
	m_shader->SetVec3("DiffuseColor", { 1.0f, 1.0f, 1.0f });
	m_shader->SetFloat("SpecularStrength", 4);
	m_shader->SetVec3("SpecularColor", { 3.0f, 3.0f, 3.0f });
	m_shader->SetVec3("LightPosition", m_lightPosition);
	m_shader->SetVec3("LightColor", m_lightColor);
	m_shader->SetMat4("WVP", _wvp * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramID()); // Use our shader
	
	//m_rotation.y += 0.005f;

	// Order in which the methods are called matters
	CalculateTransform();
	SetShaderVariables(_wvp);
	BindAttributes();

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 8);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}