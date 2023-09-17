#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"

class GameController : public Singleton<GameController>
{
public:
	//Contrstuctors/Destructors
	GameController();
	virtual ~GameController() { }

	// Methods
	void Initialize();
	void RunGame();

private:
	Shader m_shader;
	Mesh m_mesh;
};
#endif // !GAME_CONTROLLER_H

