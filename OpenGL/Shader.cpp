#include "Shader.h"

Shader::Shader()
{
	m_programID = 0;
	m_attrVertices = 0;
	m_attrColors = 0;
	m_attrNormals = 0;
	m_attrTexCoords = 0;
	m_attrWVP = 0; // probably better to set the val to -1
	m_result = GL_FALSE;
	m_infoLogLength = 0;
}

void Shader::Cleanup()
{
	glDeleteProgram(m_programID);
}

void Shader::SetTextureSampler(const char* _name, GLuint _texUnit, int _texUnitID, int _value)
{
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1)
	{
		glActiveTexture(_texUnit);
		glBindTexture(GL_TEXTURE_2D, _value);
		glUniform1i(loc, _texUnitID);
	}
}

void Shader::SetFloat(const char* _name, float _value)
{
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1)
	{
		glUniform1f(loc, _value);
	}
	// Todo:: Add debug code to print error like File not Found
}

void Shader::SetVec3(const char* _name, glm::vec3 _value)
{
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1)
	{
		glUniform3fv(loc, 1, &_value[0]);
	}
	// Todo:: Add debug code to print error like File not Found
}

void Shader::SetMat4(const char* _name, glm::mat4 _value)
{
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &_value[0][0]);
	}
	// Todo:: Add debug code to print error like File not Found
}

void Shader::SetInt(const char* _name, int _value)
{
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1)
	{
		glUniform1i(loc, _value);
	}
}

void Shader::LoadAttributes()
{
	m_attrVertices = glGetAttribLocation(m_programID, "vertices"); // Get a handle for the vertex buffer
	m_attrColors = glGetAttribLocation(m_programID, "colors"); // Get a handle for the colors buffer
	m_attrNormals = glGetAttribLocation(m_programID, "normals"); // Get a handle for the normal buffer
	m_attrTexCoords = glGetAttribLocation(m_programID, "texCoords"); // Get a handle for the texCoords buffer
	m_attrWVP = glGetUniformLocation(m_programID, "WVP"); // Get a handle for WVP matrix
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0)
	{
		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(0, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
	GLuint shaderID = glCreateShader(_type); // Create the shader

	// Read the Shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(_filePath, std::ios::in); // Specifying input
	M_ASSERT(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", _filePath));
	std::string Line = "";
	while (getline(shaderStream, Line))
		shaderCode += "\n" + Line;
	shaderStream.close();

	// Compile Shader
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	// Chaeck Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, shaderID);

	// Attach shader to program
	glAttachShader(m_programID, shaderID);

	return shaderID;
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	m_programID = glCreateProgram(); // Create the shader program
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER); // Load vertex shader
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER); // Load fragment shader
	glLinkProgram(m_programID); // Link the program(to see if the shaders exist)

	// Check the program
	glGetProgramiv(m_programID, GL_LINK_STATUS, &m_result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, m_programID);

	//Free resources
	glDetachShader(m_programID, vertexShaderID);
	glDetachShader(m_programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttributes();
}