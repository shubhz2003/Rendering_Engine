#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_shaderSimple = { };
	m_camera = { };
	m_meshBoxes.clear();
	m_spherePos = { 0.0f, 0.0f, 0.1f };
	m_teapotPos = { 0.0f, 0.0f, 0.0f };
}

double xpos = 0.0f;
double ypos = 0.0f;
glm::vec3 targetPos;
float speedFactor;
static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		float x = (xpos / width) * 2.0f - 1.0f;
		float y = 1.0 - (ypos / height) * 2.0f;
		targetPos = glm::vec3(x, y, 0.0f);
	}
}


void GameController::Initialize()
{
	// Create a default window
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, " Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int )time(0));

	// Create a default perspectice camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
	glfwSetMouseButtonCallback(WindowController::GetInstance().GetWindow(), mouse_callback);
}

void GameController::RunGame()
{
	// Show the C++/CLI window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();

#pragma region Setupshaders
	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
	m_shaderSimple = Shader();
	m_shaderSimple.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
#pragma endregion SetupShaders

#pragma region CreateMeshes
	// Create Meshes
	Mesh sphereLight = Mesh();
	sphereLight.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	sphereLight.SetPosition(m_spherePos);
	sphereLight.SetColor({ 1.0f, 1.0f, 1.0f });
	sphereLight.SetScale({ 0.01f, 0.01f, 0.01f });
	Mesh::Lights.push_back(sphereLight);

	Mesh teapot = Mesh();
	teapot.Create(&m_shaderDiffuse, "../Assets/Models/Teapot.obj");
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetScale({ 0.025f, 0.025f, 0.025f });
	teapot.SetPosition(m_teapotPos);

	Mesh sphereTextured = Mesh();
	sphereTextured.Create(&m_shaderDiffuse, "../Assets/Models/Sphere.obj");
	sphereTextured.SetCameraPosition(m_camera.GetPosition());
	sphereTextured.SetScale({ 0.03f, 0.03f, 0.03f });
	sphereTextured.SetPosition({ 0.0f, 0.0f, 0.0f });


#pragma endregion CreateMeshes

#pragma region FontSetup
	Fonts f = Fonts();
	std::string mousePosition = "";
	f.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts fpsFont = Fonts();
	std::string fpsString = "0";
	double lastTime = glfwGetTime();
	int fps = 0;
	fpsFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts cubeFont = Fonts();
	std::string cubeCount = "";
	cubeFont.Create(&m_shaderFont, "arial.ttf", 100);
#pragma endregion FontSetup

	glm::vec3 spherePos = GetSpherePos();
	glm::vec3 teapotPos = GetTeapotPos();

#pragma region Render
	do
	{
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear the screen
		
		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0)
		{
			fpsString = "FPS: " + to_string(fps);
			fps = 0;
			lastTime += 1.0;
		}

		if (OpenGL::ToolWindow::moveLight_Channel)
		{

			for (int count = 0; count < Mesh::Lights.size(); count++)
			{
				if (!OpenGL::ToolWindow::resetLight_Btn)
				{
					if (glm::length(targetPos - spherePos) > 0.01f)
					{
						glm::vec3 direction = glm::normalize(targetPos - spherePos);
						speedFactor = glm::length(targetPos) / glm::length(glm::vec3((100.0f, 100.0f, 100.0f)));

						spherePos += direction * speedFactor;
						Mesh::Lights[count].SetPosition(spherePos);
					}
				}
				else
				{
					Mesh::Lights[count].SetPosition({ 0.0f, 0.0f, 0.1f });
					targetPos = { 0.0f, 0.0f, 0.1f };
					spherePos = { 0.0f, 0.0f, 0.1f };
					OpenGL::ToolWindow::resetLight_Btn = false;
				}

				Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}
			teapot.SetShader(&m_shaderDiffuse);
			teapot.Render(m_camera.GetProjection() * m_camera.GetView());
		}
		else if (OpenGL::ToolWindow::colorByPosition_Channel)
		{
			// Added lighting code according to requirements in m_shaderSimple but for some reason I cant figure out how to make it work and it just shows black screen but renders the teapot
			// So showed teapot movement and stuff with shaderDiffuse
			teapot.SetShader(&m_shaderDiffuse);
			if (!OpenGL::ToolWindow::resetTeapot_Btn)
			{

				if (glm::length(targetPos - teapotPos) > 0.01f)
				{
					glm::vec3 direction = glm::normalize(targetPos - teapotPos);
					speedFactor = glm::length(targetPos) / glm::length(glm::vec3((100.0f, 100.0f, 100.0f)));
					teapotPos += direction * speedFactor;
					teapot.SetPosition(teapotPos);
				}
			}
			else
			{
				teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
				targetPos = { 0.0f, 0.0f, 0.0f };
				teapotPos = { 0.0f, 0.0f, 0.0f };
				OpenGL::ToolWindow::resetTeapot_Btn = false;
			}

			teapot.Render(m_camera.GetProjection() * m_camera.GetView());
		}

		else if (OpenGL::ToolWindow::moveCubesToShpere_Channel)
		{
			if (m_meshBoxes.size() == 0)
			{
				cubeCount = "Cubes: ";
			}
			else
			{
				cubeCount = "Cubes: " + to_string(m_meshBoxes.size());
			}
			cubeFont.RenderText(cubeCount, 100, 160, 0.2f, { 1.0f, 1.0f, 0.0f });

			Mesh::Lights[0].Render(m_camera.GetProjection() * m_camera.GetView());

			sphereTextured.Render(m_camera.GetProjection() * m_camera.GetView());

			int state = glfwGetMouseButton(WindowController::GetInstance().GetWindow(), GLFW_MOUSE_BUTTON_LEFT);
			if (state == GLFW_PRESS)
			{

				Mesh box = Mesh();
				box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj");
				box.SetCameraPosition(m_camera.GetPosition());
				box.SetScale({ 0.05f, 0.05f, 0.05f });
				box.SetPosition(
					{ 
						glm::linearRand(-1.0f, 1.0f),
						glm::linearRand(-1.0f, 1.0f),
						glm::linearRand(-1.0f, 1.0f)
					});
				m_meshBoxes.push_back(box);

			}
			for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
			{
				if (glm::length(sphereTextured.GetPosition() - m_meshBoxes[count].GetPosition()) > 0.01f)
				{
					glm::vec3 direction = glm::normalize(sphereTextured.GetPosition() - m_meshBoxes[count].GetPosition());
					glm::vec3 boxPos = m_meshBoxes[count].GetPosition() + direction * 0.001f;
					m_meshBoxes[count].SetPosition(boxPos);
				}
				else
				{
					m_meshBoxes.erase(m_meshBoxes.begin() + count);
				}
			}

			for (unsigned int i = 0; i < m_meshBoxes.size(); i++)
			{
				m_meshBoxes[i].Render(m_camera.GetProjection() * m_camera.GetView());
			}
		}
		fpsFont.RenderText(fpsString, 100, 100, 0.2f, { 1.0f, 1.0f, 0.0f });
		mousePosition = "Mouse Pos: " + to_string((int)xpos) + "   " + to_string((int)ypos);
		f.RenderText(mousePosition, 100, 130, 0.2f, { 1.0f, 1.0f, 0.0f });
		

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

	for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count].Cleanup();
	}
	teapot.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderSimple.Cleanup();	
#pragma endregion Cleanup
}