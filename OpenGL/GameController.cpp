#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshBoxes.clear();
	m_meshLight = { };
}

void GameController::Initialize()
{
	// Create a default window
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, " Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Grey background
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	srand(time(0));

	// Create a default perspectice camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	// Create Meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Teapot.obj");
	m.SetPosition({ 1.0f, 0.0f, 0.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.005f, 0.005f, 0.005f });
	Mesh::Lights.push_back(m);

	Mesh teapot = Mesh();
	teapot.Create(&m_shaderDiffuse, "../Assets/Models/Teapot.obj");
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetScale({ 0.015f, 0.015f, 0.015f });
	teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshBoxes.push_back(teapot);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
		{
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed

	for (int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}

	for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}