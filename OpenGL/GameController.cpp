#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderPost = { };
	m_camera = { };
	m_meshes.clear();
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.") // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0, 0, 0, 1); // Black background 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create a default perspective camera
	Resolution r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.m_width, r.m_height);
	m_camera = Camera(r);
}

void GameController::RunGame()
{
#pragma region SetupShaders
	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader(); // value object. It's cretaed on stack. No need for 'new'
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
	m_shaderPost = Shader();
	m_shaderPost.LoadShaders("PostProcessor.vertexshader", "PostProcessor.fragmentshader");
#pragma endregion SetupShaders

#pragma region CreateMeshes
	//Create meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	m.SetPosition({ 0.0f, 0.0f, 0.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.005f, 0.005f, 0.005f });
	Mesh::Lights.push_back(m);

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.ase");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetScale({ 0.001f, 0.001f, 0.001f });
	fighter.SetPosition({ 0.0f, 0.0f, -1.0f });
	m_meshes.push_back(fighter);

#pragma endregion CreateMeshes

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);
	m_postProcessor = PostProcessor();
	m_postProcessor.Create(&m_shaderPost);

	double lastTime = glfwGetTime();
	int fps = 0;
	string fpsS = "0";
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		//m_postProcessor.Start();
		for (unsigned int count = 0; count < m_meshes.size(); count++)
		{
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		for (int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0)
		{
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime = currentTime;
		}
		//m_postProcessor.End();
		f.RenderText(fpsS, 100, 100, 0.5, { 1.0, 1.0, 0.0 });

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed (a non-zero value means the window is closed)



	for (int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}

	for (unsigned int count = 0; count < m_meshes.size(); count++)
	{
		m_meshes[count].Cleanup();
	}
	f.Cleanup();
	m_postProcessor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderPost.Cleanup();
}