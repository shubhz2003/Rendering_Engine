#include "Mesh.h"
#include "Shader.h"
#include "StandardIncludes.h"
#include <msclr\marshal_cppstd.h>
#include "ASEMesh.h"
#include "ToolWindow.h"
using namespace ASEMeshes;

vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{

	m_shader = nullptr;
	m_textureDiffuse = { };
	m_textureSpecular = { };
	m_textureNormal = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_instanceBuffer = 0;
	m_instanceCount = 1;
	m_enableInstancing = false;
	m_elementSize = 0;
}

Mesh::~Mesh()
{
}

string Mesh::RemoveFolder(string _map)
{
	//Remove directory if present
	const size_t last_slash_idx = _map.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_map.erase(0, last_slash_idx + 1);
	}
	return _map;
}

bool Mesh::EndsWith(std::string const& _fullString, std::string const& _ending)
{
	if (_fullString.length() >= _ending.length())
	{
		return (0 == _fullString.compare(_fullString.length() - _ending.length(), _ending.length(), _ending));
	}
	else
	{
		return false;
	}
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

	if (EndsWith(_file, ".ase"))
	{
		ASEMesh^ meshData = gcnew ASEMesh(_file.c_str());
		meshData->ParseASEFile();
		MeshInfo^ m = meshData->GeoObjects[0]->MeshI;
		Material^ mat = meshData->Materials[meshData->GeoObjects[0]->MaterialID];

		vector<objl::Vector3> tangents;
		vector<objl::Vector3> bitangents;
		vector<objl::Vertex> triangle;
		objl::Vector3 tangent;
		objl::Vector3 bitangent;
		int vCount = 0;
		for (int count = 0; count < m->NumFaces; count++)
		{
			Vec3^ tF = m->TexFaces[count];
			Vec3^ f = m->Faces[count];
			triangle.clear();

			objl::Vertex vert = objl::Vertex();
			vert.Position = objl::Vector3(m->Vertices[(int)f->X]->X, m->Vertices[(int)f->X]->Y, m->Vertices[(int)f->X]->Z);
			vert.Normal = objl::Vector3(m->VertexNormals[vCount]->X, m->VertexNormals[vCount]->Y, m->VertexNormals[vCount]->Z);
			vert.TextureCoordinate = objl::Vector2(m->TexVertices[(int)tF->X]->X, m->TexVertices[(int)tF->X]->Y);
			triangle.push_back(vert);
			vCount++;

			vert = objl::Vertex();
			vert.Position = objl::Vector3(m->Vertices[(int)f->Y]->X, m->Vertices[(int)f->Y]->Y, m->Vertices[(int)f->Y]->Z);
			vert.Normal = objl::Vector3(m->VertexNormals[vCount]->X, m->VertexNormals[vCount]->Y, m->VertexNormals[vCount]->Z);
			vert.TextureCoordinate = objl::Vector2(m->TexVertices[(int)tF->Y]->X, m->TexVertices[(int)tF->Y]->Y);
			triangle.push_back(vert);
			vCount++;

			vert = objl::Vertex();
			vert.Position = objl::Vector3(m->Vertices[(int)f->Z]->X, m->Vertices[(int)f->Z]->Y, m->Vertices[(int)f->Z]->Z);
			vert.Normal = objl::Vector3(m->VertexNormals[vCount]->X, m->VertexNormals[vCount]->Y, m->VertexNormals[vCount]->Z);
			vert.TextureCoordinate = objl::Vector2(m->TexVertices[(int)tF->Z]->X, m->TexVertices[(int)tF->Z]->Y);
			triangle.push_back(vert);
			vCount++;

			CalculateTangents(triangle, tangent, bitangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);

			for (int c = 0; c < 3; c++)
			{
				m_vertexData.push_back(triangle[c].Position.X);
				m_vertexData.push_back(triangle[c].Position.Y);
				m_vertexData.push_back(triangle[c].Position.Z);
				m_vertexData.push_back(triangle[c].Normal.X);
				m_vertexData.push_back(triangle[c].Normal.Y);
				m_vertexData.push_back(triangle[c].Normal.Z);
				m_vertexData.push_back(triangle[c].TextureCoordinate.X);
				m_vertexData.push_back(triangle[c].TextureCoordinate.Y);

				int index = (vCount / 3) - 1;
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);

			}
		}
		m_textureDiffuse = Texture();
		if (mat->Maps[0]->Name == "DIFFUSE")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[0]->TextureFileName);
			m_textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(fn));

		}

		m_textureSpecular = Texture();
		if (mat->Maps[1]->Name == "SPECULAR")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[1]->TextureFileName);
			m_textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(fn));
		}

		m_textureNormal = Texture();
		if (mat->Maps[1]->Name == "BUMP")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[1]->TextureFileName);
			m_textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(fn));
			m_enableNormalMap = true;
		}
		else if (mat->Maps[2]->Name == "BUMP")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[2]->TextureFileName);
			m_textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(fn));
			m_enableNormalMap = true;
		}
	}
	else
	{
		objl::Loader Loader; //Initialize Loader

		M_ASSERT(Loader.LoadFile(_file) == true, "Failed to load mesh."); //Load .obj file

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


		for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			objl::Mesh curMesh = Loader.LoadedMeshes[i];
			vector<objl::Vector3> tangents;
			vector<objl::Vector3> bitangents;
			vector<objl::Vertex> triangle;
			objl::Vector3 tangent;
			objl::Vector3 bitangent;
			for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
			{
				triangle.clear();
				triangle.push_back(curMesh.Vertices[j]);
				triangle.push_back(curMesh.Vertices[j + 1]);
				triangle.push_back(curMesh.Vertices[j + 2]);
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
	}


	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
#pragma endregion LoadMesh

	if (m_enableInstancing)
	{
		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		srand(glfwGetTime()); //initialize random seed
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

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
	m_textureNormal.Cleanup();
}

void Mesh::CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	//calculate tangent/bitangent vectors of both triangles
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


void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //Bind the vertex buffer

	int stride = 8;
	if (m_enableNormalMap)
	{
		stride += 6; // Include tangent and bitangent components
	}

#pragma region BindVertexData
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,                   // size (3 vertices per primitive)
		GL_FLOAT,            // type 
		GL_FALSE,            // normalized?
		stride * sizeof(float),   // stride (8 floats per vertex definition)
		(void*)0);           // array buffer offset 


	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(), // The attribute we want to configure
		3,                   // size ( 3 components per color value)
		GL_FLOAT,            // type 
		GL_FALSE,            // normalized?
		stride * sizeof(float),   // stride (8 floats per vertex definition)
		(void*)(3 * sizeof(float)));           // array buffer offset 

	// 3rd  attribute buffer : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The attribute we want to configure
		2,                   // size ( 2 components per color value)
		GL_FLOAT,            // type 
		GL_FALSE,            // normalized?
		stride * sizeof(float),   // stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float)));           // array buffer offset 
	m_elementSize = 8;
#pragma endregion BindVertexData

#pragma region BindNormalMapData
	if (m_enableNormalMap)
	{
		//4th attribute buffer : tangent
		glEnableVertexAttribArray(m_shader->GetAttrTangents());
		glVertexAttribPointer(m_shader->GetAttrTangents(), //The attribute we want to configure
			3,             // size (3 components)
			GL_FLOAT,      // type
			GL_FALSE,      // normalized? 
			stride * sizeof(float),    // stride floats per vertex definition
			(void*)(8 * sizeof(float)));  // array buffer offset

		//5th attribute buffer : bitangent
		glEnableVertexAttribArray(m_shader->GetAttrBitangents());
		glVertexAttribPointer(m_shader->GetAttrBitangents(), //The attribute we want to configure
			3,             // size (3 components)
			GL_FLOAT,      // type
			GL_FALSE,      // normalized? 
			stride * sizeof(float),    // stride floats per vertex definition
			(void*)(11 * sizeof(float)));  // array buffer offset
		m_elementSize += 6;
	}
#pragma endregion BindNormalMapData

#pragma region BindInstancingData
	if (m_enableInstancing)
	{

		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer); // Bind the vertex buffer

		// Set attribute for instance matrix (4 times vec4 since its a 4x4 matrix)
		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix(),
			4,             // size (4 components)
			GL_FLOAT,      // type
			GL_FALSE,      // normalized? 
			sizeof(glm::mat4),    // stride
			(void*)0);  // instance buffer offset

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 1,
			4,             // size (4 components)
			GL_FLOAT,      // type
			GL_FALSE,      // normalized? 
			sizeof(glm::mat4),    // stride
			(void*)(sizeof(glm::vec4)));  // instance buffer offset

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 2,
			4,             // size (4 components)
			GL_FLOAT,      // type
			GL_FALSE,      // normalized? 
			sizeof(glm::mat4),    // stride
			(void*)(2 * sizeof(glm::vec4)));  // instance buffer offset

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 3,
			4,             // size (4 components)
			GL_FLOAT,      // type
			GL_FALSE,      // normalized? 
			sizeof(glm::mat4),    // stride
			(void*)(3 * sizeof(glm::vec4)));  // instance buffer offset

		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix(), 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 1, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 2, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 3, 1);
	}
#pragma endregion BindInstancingData

}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);
	m_shader->SetInt("EnableInstancing", m_enableInstancing);

	//Configure light
	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.009f);
		m_shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

		m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { (float)OpenGL::ToolWindow::trackBar_R / 3.0f,
																			(float)OpenGL::ToolWindow::trackBar_G / 3.0f,
																			(float)OpenGL::ToolWindow::trackBar_B / 3.0f });

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
	}


	//Configure material
	m_shader->SetFloat("material.specularStrength", (float)OpenGL::ToolWindow::trackBar_SpecStrength);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
	m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID()); // Use our shader
	m_rotation.x += 0.1f;

	CalculateTransform();
	SetShaderVariables(_pv);
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
