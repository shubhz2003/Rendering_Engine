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
	GLuint GetAttrWVP() { return m_attrWVP; }

	// Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();

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
	GLuint m_attrWVP;
	GLint m_result;
	int m_infoLogLength;
};
#endif // !Shader_H


