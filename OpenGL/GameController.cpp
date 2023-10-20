#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshBox = { };
	m_meshLight = { };
}

void GameController::Initialize()
{
	// Create a default window
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, " Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// Create a default perspectice camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	// Show the C++/CLI tool window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();

	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	//m_shaderDiffuse = Shader();
	//m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	// Create Meshes
	m_meshLight = Mesh();
	m_meshLight.Create(&m_shaderColor);
	m_meshLight.SetPosition({ 1, 0.5f, 0.5f });
	m_meshLight.SetScale({ 1.0f, 1.0f, 1.0f });

	//m_meshBox = Mesh();
	//m_meshBox.Create(&m_shaderDiffuse);
	//m_meshBox.SetLightColor({ 0.5f, 0.9f, 0.5f });
	//m_meshBox.SetLightPosition({ m_meshLight.GetPosition()});
	//m_meshBox.SetCameraPosition(m_camera.GetPosition());

	do
	{
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form Events

		GLfloat loc = glGetUniformLocation(m_shaderColor.GetProgramID(), "YChannel");
		glUniform1f(loc, (float)OpenGL::ToolWindow::YChannel);
		loc = glGetUniformLocation(m_shaderColor.GetProgramID(), "UChannel");
		glUniform1f(loc, (float)OpenGL::ToolWindow::UChannel);
		loc = glGetUniformLocation(m_shaderColor.GetProgramID(), "VChannel");
		glUniform1f(loc, (float)OpenGL::ToolWindow::VChannel);
		loc = glGetUniformLocation(m_shaderColor.GetProgramID(), "RenderInvertColorsChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderInvertColorsChannel);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		//m_meshBox.Render(m_camera.GetProjection() * m_camera.GetView());
		m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed

	m_meshLight.Cleanup();
	//m_meshBox.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}