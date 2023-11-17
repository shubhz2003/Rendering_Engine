#ifndef TEXTURE_H
#define TEXTURE_H

#include "StandardIncludes.h"

class Texture
{
public:
	//Contructors / Destructors
	Texture();
	virtual ~Texture() { }

	// Accessors
	GLuint GetTexture() { return m_texture; }

	// Methods
	void LoadTexture(string _fileName);
	void Cleanup();

private:
	// Members
	int m_width;
	int m_height;
	int m_channels;
	GLuint m_texture;

	// Methods
	bool EndsWith(const std::string& _str, const std::string& _suffix);
};
#endif // !TEXTURE_H


