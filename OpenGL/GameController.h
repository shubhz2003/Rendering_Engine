#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Camera.h"
#include "PostProcessor.h"

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

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderPost;
	Camera m_camera;
	PostProcessor m_postProcessor;
	vector<Mesh> m_meshes;
	Skybox m_skybox;
	GLuint vao;
	glm::vec3 m_spherePos;
};
#endif // !GAME_CONTROLLER_H

