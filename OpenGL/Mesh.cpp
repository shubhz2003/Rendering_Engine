#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_world = glm::mat4(1.0f);
}

Mesh::~Mesh()
{
}


void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;

	// Player Triangle
	m_vertexData = { 
		/* Position   /		/    RGBA Color    */
		-1.0f, -1.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,

		0.5f, 5.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		2.5f, 3.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 3.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		4.0f, 5.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		6.0f, 4.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		5.0f, 7.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		-6.0f, 3.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-3.5f, 5.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-3.5f, 2.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		-3.0f, 5.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, 6.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-1.5f, 4.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		-7.5f, 3.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-6.0f, 3.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-8.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		6.0f, 0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		6.5f, -1.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		5.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		4.0f, -5.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		6.0f, -4.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		5.0f, -7.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		2.0f, -7.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		4.0f, -6.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		3.0f, -9.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		-5.0f, -6.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-7.0f, -5.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-6.0f, -8.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,

		-2.0f, -7.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-4.0f, -6.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-3.0f, -9.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
	};

	// Tried Randomizing the NPC triangles to render and have m_colorNPC to change the color of NPCs
	//float _point = static_cast<float>(((rand() % 9) + 2) * sign);

	//m_vertexData = {
	//	/* Position   /						/    RGBA Color    */
	//	 _point, _point, 0.0f,				0.0f, m_colorNPC[1], m_colorNPC[0], 1.0f,
	//	 _point + 2.0f, _point,	0.0f,		0.0f, m_colorNPC[1], m_colorNPC[0], 1.0f,
	//	 _point + 1.0f, _point + 2.0f,0.0f,	0.0f, m_colorNPC[1], m_colorNPC[0], 1.0f
	//};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	//m_indexData = {
	//	0, 6, 1, 0, 11, 6, 1, 4, 0, 1, 8, 4,
	//	1, 10, 8, 2, 5, 3, 2, 9, 5, 2, 11, 9,
	//	3, 7, 2, 3, 10, 7, 4, 8, 5, 4, 9, 0,
	//	5, 8, 3, 5, 9, 4, 6, 10, 1, 6, 11, 7,
	//	7, 10, 6, 7, 11, 2, 8, 10, 3, 9, 11, 0
	//};

	//glGenBuffers(1, &m_indexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);

}

void Mesh::Render(glm::mat4 _wvp)
{
	//HandleInput(window, position, rotation);
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
	//m_world = glm::rotate(m_world, 0.01f, { 0, 1, 0 }); // Y-axis rotation
	m_world = glm::translate(m_world, { 0 , 0.01, 0 }); // Triangle moves!!
	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer); // Bind the index buffer
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 7);
	//glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	

	// providing default values and having a variable to access each of the values
	glm::vec3 position(0.0f);
	glm::vec3 rotation(0.0f);
	glm::vec3 scale(1.0f);

	m_world = glm::translate(m_world, position);
	m_world = glm::rotate(m_world, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_world = glm::rotate(m_world, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_world = glm::rotate(m_world, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_world = glm::scale(m_world, scale);


	// Tried having movement for the player triangle
	if (GLFW_KEY_ESCAPE == GLFW_KEY_DOWN)
	{
		glfwTerminate();
	}
	else if (GLFW_KEY_W == GLFW_KEY_DOWN)
	{
		m_world += glm::translate(m_world, { 0, 1, 0 });
		_wvp *= m_world;
	}
	else if (GLFW_KEY_A == GLFW_KEY_DOWN)
	{
		m_world += glm::translate(m_world, { -1, 0, 0 });
		_wvp *= m_world;
	}
	else if (GLFW_KEY_S == GLFW_KEY_DOWN)
	{
		m_world += glm::translate(m_world, { 0, -1, 0 });
		_wvp *= m_world;
	}
	else if (GLFW_KEY_D == GLFW_KEY_DOWN)
	{
		m_world += glm::translate(m_world, { 1, 0, 0 });
		_wvp *= m_world;
	}
	else
	{
		return;
	}
	
	// Tried to render the NPCs and update them with rotation again
	//const int NUM_NPC = 10;
	//const float MIN_X = 2.0f;
	//const float MAX_X = 10.0f;
	//const float MIN_Y = -10.0f;
	//const float MAX_Y = -2.0f;
	//const float NPC_SPEED = 1.0f;

	//// Update NPC triangles
	//for (int i = 0; i < NUM_NPC; ++i) {
	//	glm::Vector2f npcPos = npcTriangles[i].getPosition();
	//	glm::Vector2f playerPos = playerTriangle.getPosition();
	//	float dist = distance(npcPos, playerPos);

	//	// Always face the player
	//	float angle = std::atan2(playerPos.y - npcPos.y, playerPos.x - npcPos.x) * 180 / M_PI;
	//	npcTriangles[i].setRotation(angle);

	//	// Move NPCs based on distance
	//	if (dist < 10) {
	//		// Move away from player
	//		glm::Vector2f direction = npcPos - playerPos;
	//		direction /= dist;
	//		npcTriangles[i].move(direction * NPC_SPEED);
	//	}
	//	else if (dist > 11) {
	//		// Move closer to player
	//		glm::Vector2f direction = playerPos - npcPos;
	//		direction /= dist;
	//		npcTriangles[i].move(direction * NPC_SPEED);
	//	}

	//	// Tagged triangles are blue
	//	if (taggedTriangles[i]) {
	//		npcTriangles[i].setFillColor(sf::Color::Blue);
	//	}
	//}

	//// Rendering
	//window.clear();
	//window.draw(playerTriangle);
	//for (int i = 0; i < NUM_NPC; ++i) {
	//	window.draw(npcTriangles[i]);
	//}
	//window.display();
}



// Tried having movement for the player triangle
void Mesh::HandleInput(GLFWwindow* _window, glm::vec3& _position, glm::vec3& _rotation)
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_position.y += 0.01f;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_position.y -= 0.01f;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_position.x -= 0.01f;
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_position.x += 0.01f;
	}
	if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		_rotation.y -= 1.0f;
	}
	if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
	{
		_rotation.y += 1.0f;
	}
}

// Tried updating the NPC Triangle movements
//// Function to update NPC positions
//void updateNPCTriangles() {
//	float distanceThreshold = 10.0f;
//	float moveSpeed = 1.0f;
//
//	for (int i = 0; i < 10; i++) {
//		float dx = playerX - npcTriangles[i].x;
//		float dy = playerY - npcTriangles[i].y;
//		float distance = std::sqrt(dx * dx + dy * dy);
//
//		if (distance < distanceThreshold) {
//			// Move away from the player
//			npcTriangles[i].x -= moveSpeed * (dx / distance);
//			npcTriangles[i].y -= moveSpeed * (dy / distance);
//		}
//		else if (distance > (distanceThreshold + 1.0f)) {
//			// Move closer to the player
//			npcTriangles[i].x += moveSpeed * (dx / distance);
//			npcTriangles[i].y += moveSpeed * (dy / distance);
//		}
//	}
//}
