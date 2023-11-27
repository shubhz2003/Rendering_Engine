#include "Mesh.h"
#include "Shader.h"
#include "OBJ_Loader.h"

vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_textureDiffuse = { };
	m_textureSpecular = { };
	m_textureNormal = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_instanceCount = 1;
	m_enableInstancing = false;
	m_elementSize = 0;
}

Mesh::~Mesh()
{
}


void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
	m_textureNormal.Cleanup();
}

string Mesh::RemoveFolder(string _map)
{
	const size_t last_slash_idx = _map.find_last_of("\\");
	if (std::string::npos != last_slash_idx);
	{
		_map.erase(0, last_slash_idx + 1);
	}

	return _map;
}

void Mesh::CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	// Calculate tangent/bitangent vectors of both triangles
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
	_bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
	_bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}

void Mesh::Create(Shader* _shader, string _file, int _instanceCount)
{
	m_shader = _shader;
	m_instanceCount = _instanceCount;
	if (m_instanceCount > 1)
	{
		m_enableInstancing = true;
	}

#pragma region LoadMesh
	objl::Loader Loader; // Initialize Loader
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed to load mesh."); // Load .obj File
	
	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		vector<objl::Vector3> tangents;
		vector<objl::Vector3> bitangents;
		vector<objl::Vertex> triangle;
		objl::Vector3 tangent;
		objl::Vector3 bitangent;
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j+=3)
		{
			triangle.clear();
			triangle.push_back(curMesh.Vertices[j]);
			triangle.push_back(curMesh.Vertices[j+1]);
			triangle.push_back(curMesh.Vertices[j+2]);
			CalculateTangents(triangle, tangent, bitangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
		}
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);


			if (Loader.LoadedMaterials[0].map_bump != "")
			{
				int index = j / 3;
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);
			}
		}
	}
#pragma endregion LoadMesh

	//Remove Directory if present
	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Kd));
	m_textureSpecular = Texture();
	if (Loader.LoadedMaterials[0].map_Ks != "")
	{
		m_textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Ks));
	}
	m_textureNormal = Texture();
	if (Loader.LoadedMaterials[0].map_bump != "")
	{
		m_textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_bump));
		m_enableNormalMap = true;
	}

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	if (m_enableInstancing)
	{
		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		srand(glfwGetTime()); // initialize random seed
		for (unsigned int i = 0; i < m_instanceCount; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-20 + rand() % 40, -10 + rand() % 20, -10 + rand() % 20));

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					m_instanceData.push_back(model[x][y]);
				}
			}
		}

		glBufferData(GL_ARRAY_BUFFER, m_instanceCount * sizeof(glm::mat4), m_instanceData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer

	int stride = 8;

	if (m_enableNormalMap)
	{
		stride += 6; // Include tangent and bitangent componets
	}

#pragma region BindVertexData
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,						// size
		GL_FLOAT,				// type
		GL_FALSE,				// normalized?
		stride * sizeof(float),	//stride floats per vertex
		(void*)0);				// array bufffer offset

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(), // The attribute we want to configure
		3,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		stride * sizeof(float),			// stride floats per vertex
		(void*)(3 * sizeof(float)));	// array bufffer offset

	// 3rd attribute buffer : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The attribute we want to configure
		2,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		stride * sizeof(float),			// stride floats per vertex
		(void*)(6 * sizeof(float)));	// array bufffer offset
	m_elementSize = 8;
#pragma endregion BindVertexData

#pragma region BindNormalMapData
	if (m_enableNormalMap)
	{
		// 4th attribute buffer : tangent
		glEnableVertexAttribArray(m_shader->GetAttrTangents());
		glVertexAttribPointer(m_shader->GetAttrTangents(), // The attribute we want to configure
			3,								// size
			GL_FLOAT,						// type
			GL_FALSE,						// normalized?
			stride * sizeof(float),			// stride floats per vertex
			(void*)(8 * sizeof(float)));	// array bufffer offset

		// 5th attribute buffer : bitangent
		glEnableVertexAttribArray(m_shader->GetAttrBitangents());
		glVertexAttribPointer(m_shader->GetAttrBitangents(), // The attribute we want to configure
			3,								// size
			GL_FLOAT,						// type
			GL_FALSE,						// normalized?
			stride * sizeof(float),			// stride floats per vertex
			(void*)(11 * sizeof(float)));	// array bufffer offset
		m_elementSize += 6;
	}
#pragma endregion BindNormalMapData

#pragma region BindInstancingData
	if (m_enableInstancing)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer); // Bind the vertex Buffer

		// Set attribute pointers for instance matrix (4 times vec4)
		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix(), // The attribute we want to configure
			4,								// size (4 components)
			GL_FLOAT,						// type
			GL_FALSE,						// normalized?
			sizeof(glm::mat4),				// stride 
			(void*)0);	// instance bufffer offset

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 1, // The attribute we want to configure
			4,								// size (4 components)
			GL_FLOAT,						// type
			GL_FALSE,						// normalized?
			sizeof(glm::mat4),				// stride 
			(void*)(sizeof(glm::mat4)));	// instance bufffer offset

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 2, // The attribute we want to configure
			4,								// size (4 components)
			GL_FLOAT,						// type
			GL_FALSE,						// normalized?
			sizeof(glm::mat4),				// stride 
			(void*)(2 * sizeof(glm::mat4)));	// instance bufffer offset

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 3, // The attribute we want to configure
			4,								// size (4 components)
			GL_FLOAT,						// type
			GL_FALSE,						// normalized?
			sizeof(glm::mat4),				// stride 
			(void*)(3 * sizeof(glm::mat4)));	// instance bufffer offset

		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix(), 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 1, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 2, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 3, 1);
	}
#pragma endregion BindInstancingData
}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _wvp)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _wvp * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);
	m_shader->SetInt("EnableInstancing", m_enableInstancing);

	// Configure Light
	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
		m_shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

		m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 1.0f, 1.0f, 1.0f });
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 3.0f, 3.0f, 3.0f });

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);

		// Configure Material
		m_shader->SetFloat("material.specularStrength", 8);
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
		m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
		m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());
	}
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramID()); // Use our shader
	
	m_rotation.x += 0.01f;

	// Order in which the methods are called matters
	CalculateTransform();
	SetShaderVariables(_wvp);
	BindAttributes();

	if (m_enableInstancing)
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize, m_instanceCount);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize);
	}

	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());

	if (m_enableNormalMap)
	{
		glDisableVertexAttribArray(m_shader->GetAttrTangents());
		glDisableVertexAttribArray(m_shader->GetAttrBitangents());
	}
	if (m_enableInstancing)
	{
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
	}
}