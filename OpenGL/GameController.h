#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "WindowController.h"
#include "Camera.h"

class GameController : public Singleton<GameController>
{
public:
	//Contrstuctors/Destructors
	GameController();
	virtual ~GameController() { }

	// Methods
	void Initialize();
	void RunGame();

	// Accessors
	glm::vec3 GetSpherePos() { return m_spherePos; } 
	glm::vec3 GetTeapotPos() { return m_teapotPos; }

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSimple;
	Camera m_camera;
	vector<Mesh> m_meshBoxes;
	glm::vec3 m_spherePos;
	glm::vec3 m_teapotPos;
};
#endif // !GAME_CONTROLLER_H

