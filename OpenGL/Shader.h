#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"

class Shader
{
public:
	//Constructors/Destructors
	Shader();
	virtual ~Shader() { };

	// Accessors
	GLuint GetProgramID() { return m_programID; }
	GLuint GetAttrVertices() { return m_attrVertices; }
	GLuint GetAttrColors() { return m_attrColors; }
	GLuint GetAttrNormals() { return m_attrNormals; }
	GLuint GetattrTangents() { return m_attrTangents; }
	GLuint GetattrBitangents() { return m_attrBitangents; }
	GLuint GetAttrTexCoords() { return m_attrTexCoords; }
	GLuint GetAttrWVP() { return m_attrWVP; }

	// Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	void SetTextureSampler(const char* _name, GLuint _texUnit, int _texUnitID, int _value);
	void SetFloat(const char* _name, float _value);
	void SetVec3(const char* _name, glm::vec3 _value);
	void SetMat4(const char* _name, glm::mat4 _value);
	void SetInt(const char* _name, int _value);

private:
	// Methods
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	// Members
	GLuint m_programID;  // ID of the shader program
	GLuint m_attrVertices; // Handle for the attribute vertex buffer
	GLuint m_attrColors; // Handle for colors
	GLuint m_attrNormals; 
	GLuint m_attrTangents;
	GLuint m_attrBitangents;
	GLuint m_attrTexCoords; // Handle for Texture coordinates
	GLuint m_attrWVP;
	GLint m_result;
	int m_infoLogLength;
};
#endif // !Shader_H


