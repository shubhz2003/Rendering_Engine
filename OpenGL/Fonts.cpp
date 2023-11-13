#include "Fonts.h"
#include "Shader.h"
#include "WindowController.h"

Fonts::Fonts()
{
	m_shader = nullptr;
	m_library = 0;
	m_face = 0;
	m_vertexBuffer = 0;
	m_orthoProj = { };
}

void Fonts::Create(Shader* _shader, string _name, FT_UInt _size)
{
	m_shader = _shader;

	AllocateBuffers();
	Initialize(_name, _size);
}

void Fonts::AllocateBuffers()
{
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
}

void Fonts::Initialize(string _name, FT_UInt _size)
{
	string fileName = "../Assets/Fonts/" + _name; // Font are just subjectected to copyright*
	Resolution r = WindowController::GetInstance().GetResolution();
	m_orthoProj = glm::ortho(0.0f, (float)r.m_width, 0.0f, (float)r.m_height);

	// Initialize the library and font face
	M_ASSERT(FT_Init_FreeType(&m_library) == false, "Could not init FreeType Library");
	M_ASSERT(FT_New_Face(m_library, fileName.c_str(), 0, &m_face) == false, "Failed to load font");

	//Set font height to variable size (0 to auto-calculate width)
	M_ASSERT(FT_Set_Pixel_Sizes(m_face, 0, _size) == false, "Failed to set character size");

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	CreateCharacters();

	// Free library resources
	FT_Done_Face(m_face);
	FT_Done_FreeType(m_library);
}

void Fonts::CreateCharacters()
{
	// Load First 128 character glyphs into character textures
	for (unsigned char c = 0; c < 128; c++)
	{
		// Load Character glyph
		M_ASSERT(FT_Load_Char(m_face, c, FT_LOAD_RENDER) == false, "Failed to load Glyph");

		// Generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);

		//Set Texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); // To prevent char overlap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = { texture,
								glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
								glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
								(unsigned int)m_face->glyph->advance.x };
		m_characters.insert(std::pair<char, Character>(c, character));
	}

}


void Fonts::RenderText(std::string _text, float _x, float _y, float _scale, glm::vec3 _color)
{
	_y = WindowController::GetInstance().GetResolution().m_height - _y; //Inverting the coordinate axis so text renders from top left to right
	glUseProgram(m_shader->GetProgramID()); // Use our shader
	m_shader->SetVec3("TextColor", _color);
	glUniformMatrix4fv(glGetUniformLocation(m_shader->GetProgramID(), "Projection"), 1, GL_FALSE, glm::value_ptr(m_orthoProj));
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = _text.begin(); c != _text.end(); c++)
	{
		Character ch = m_characters[*c];
		float xpos = _x + ch.Bearing.x * _scale;
		float ypos = _y - (ch.Size.y - ch.Bearing.y) * _scale;
		float w = ch.Size.x * _scale;
		float h = ch.Size.y * _scale;

		// Update vertex Buffer for each character
		float vertices[6][4] = {
			{ xpos,		ypos + h,	0.0f, 0.0f },
			{ xpos,		ypos,		0.0f, 1.0f },
			{ xpos + w,	ypos,		1.0f, 1.0f },

			{ xpos,		ypos + h,	0.0f, 0.0f },
			{ xpos + w,	ypos,		1.0f, 1.0f },
			{ xpos + w,	ypos + h,	1.0f, 0.0f },
		};

		// Render glyph texture over quad
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, ch.TextureID);

		// Update content of vertex buffer memory
		glEnableVertexAttribArray(m_shader->GetAttrVertices());
		glVertexAttribPointer(m_shader->GetAttrVertices(), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Now advace cursors for next glyph ( note that advace is number of 1/64 pixels)
		_x += (ch.Advance >> 6) * _scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/ 64th pixels by 64 to get the amount of pixels
	}

	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glBindTexture(GL_TEXTURE_2D, 0);
}

