#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_camera = { };
	m_meshes.clear();
}

void GameController::Initialize()
{
	// Create a default window
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, " Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Grey background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	srand((unsigned int )time(0));

	// Create a default perspectice camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
#pragma region Setupshaders
	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
#pragma endregion SetupShaders

#pragma region CreateMeshes
	// Create Meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Teapot.obj");
	m.SetPosition({ 0.0f, 0.0f, 0.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.015f, 0.015f, 0.015f });
	Mesh::Lights.push_back(m);

	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj");
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale({ 0.05f, 0.05f, 0.05f });
	box.SetPosition({ 1.0f, 0.0f, 0.0f });
	m_meshes.push_back(box);

#pragma endregion CreateMeshes

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

#pragma region Render
	double lastTime = glfwGetTime();
	int fps = 0;
	string fpsS = "0";
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear the screen
		
		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0)
		{
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime += 1.0;
		}
		f.RenderText(fpsS, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });

		for (unsigned int count = 0; count < m_meshes.size(); count++)
		{
			for (int x = 0; x < 1000; x++)
			{
				m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}	
		}

		for (unsigned int count = 0; count < m_meshes.size(); count++)
		{
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed
#pragma endregion Render

#pragma region Cleanup
	for (int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}

	for (unsigned int count = 0; count < m_meshes.size(); count++)
	{
		m_meshes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderSkybox.Cleanup();
#pragma endregion Cleanup
}