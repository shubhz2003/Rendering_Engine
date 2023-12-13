#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderPost = { };
	m_shaderFont = { };
	m_shaderSkybox = { };
	m_camera = { };
	m_meshes.clear();
	m_spherePos = { 0.0f, 0.0f, 0.0f };
	m_fighterPos = { 0.0f, 0.0f, -1.0f };
	m_fighterScale = { 0.001f, 0.001f, 0.001f };
	m_fighterRotate = { 0.0f, 0.0f, 0.0f };
	leftButtonPressed = false;
	lastX = 0.0f;
	lastY = 0.0f;
}

double xPos = 0.0f;
double yPos = 0.0f;
glm::vec3 targetPos;
float speedFactor;
static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &xPos, &yPos);

		float x = (xPos / width) * 2.0f - 1.0f;
		float y = 1.0 - (yPos / height) * 2.0f;
		targetPos = glm::vec3(x, y, 0.0f);
	}
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
	glfwSetMouseButtonCallback(WindowController::GetInstance().GetWindow(), mouse_callback);
}

void GameController::RunGame()
{
	// Show the C++/CLI window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();

#pragma region SetupShaders
	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader(); // value object. It's cretaed on stack. No need for 'new'
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
	m_shaderPost = Shader();
	m_shaderPost.LoadShaders("PostProcessor.vertexshader", "PostProcessor.fragmentshader");
#pragma endregion SetupShaders

#pragma region CreateMeshes
	//Create meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	m.SetPosition(m_spherePos);
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.005f, 0.005f, 0.005f });
	Mesh::Lights.push_back(m);

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.ase");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetScale(m_fighterScale);
	fighter.SetPosition(m_fighterPos);

	Mesh astroid = Mesh();
	astroid.Create(&m_shaderDiffuse, "../Assets/Models/Astroid.ase", 100);
	astroid.SetCameraPosition(m_camera.GetPosition());
	astroid.SetScale({ 0.05f, 0.05f, 0.05f });
	astroid.SetPosition({ 0.0f, 0.0f, 0.0f });

	Skybox skybox = Skybox();
	skybox.Create(&m_shaderSkybox, "../Assets/Models/SkyBox.obj",
		{	"../Assets/Textures/Skybox/right.jpg",
			"../Assets/Textures/Skybox/left.jpg",
			"../Assets/Textures/Skybox/top.jpg",
			"../Assets/Textures/Skybox/bottom.jpg",
			"../Assets/Textures/Skybox/front.jpg",
			"../Assets/Textures/Skybox/back.jpg"
		});

#pragma endregion CreateMeshes

	m_postProcessor = PostProcessor();
	m_postProcessor.Create(&m_shaderPost);

#pragma region FontSetup

	Fonts f = Fonts();
	string mousePosition = "";
	f.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts fpsFont = Fonts();
	double lastTime = glfwGetTime();
	int fps = 0;
	string fpsS = "0";
	fpsFont.Create(&m_shaderFont, "arial.ttf", 100);

#pragma endregion FontSetup

	glm::vec3 spherePos = GetSpherePos();
	glm::vec3 fighterPos = GetFighterPos();

#pragma region Render
	do
	{
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI Events

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
					Mesh::Lights[count].SetPosition({0.0f, 0.0f, 0.0f});
					targetPos = { 0.0f, 0.0f, 0.0f };
					spherePos = { 0.0f, 0.0f, 0.0f };
					OpenGL::ToolWindow::resetLight_Btn = false;
				}

				Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}
			fighter.Render(m_camera.GetProjection() * m_camera.GetView());
		}

		else if (OpenGL::ToolWindow::transform_Channel)
		{
			m_camera.SetPosition();

			std::cout << "Camera: " << glm::to_string(m_camera.GetPosition()) << std::endl;

			fighter.SetRotation(m_fighterRotate);

			for (int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].SetPosition({ 0.0f, 0.0f, 2.0f });
			}


			if (OpenGL::ToolWindow::RenderTranslate_Channel)
			{
				if (leftButtonPressed)
				{
					if (glm::length(targetPos - m_fighterPos) > 0.1)
					{
						glm::vec3 direction = glm::normalize(targetPos - m_fighterPos);
						speedFactor = glm::length(targetPos) / glm::length(glm::vec3(100.0f, 100.0f, 100.0f));

						m_fighterPos += direction * speedFactor;
						fighter.SetPosition(m_fighterPos);
					}
				}
			}
			if (OpenGL::ToolWindow::RenderRotate_Channel)
			{
				double mouseX, mouseY;
				glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);

				double deltaX = mouseX - lastX;
				double deltaY = mouseY - lastY;

				int leftState = glfwGetMouseButton(WindowController::GetInstance().GetWindow(), GLFW_MOUSE_BUTTON_LEFT);
				if (leftState == GLFW_PRESS)
				{
					m_fighterRotate.x += static_cast<float>(deltaY) * 0.1f;
					m_fighterRotate.y += static_cast<float>(deltaX) * 0.1f;
				}

				int middleState = glfwGetMouseButton(WindowController::GetInstance().GetWindow(), GLFW_MOUSE_BUTTON_MIDDLE);
				if (middleState == GLFW_PRESS)
				{
					m_fighterRotate.z += static_cast<float>(deltaY) * 0.1f;
				}

				lastX = mouseX;
				lastY = mouseY;

				fighter.SetRotation(m_fighterRotate);
			}

			if (OpenGL::ToolWindow::RenderScale_Channel)
			{
				m_fighterScale = fighter.GetScale();

				double deltaScaleX;
				double deltaScaleY;
				double mouseX, mouseY;
				glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);

				deltaScaleX = mouseX - lastX;
				deltaScaleY = mouseY - lastY;

				int leftState = glfwGetMouseButton(WindowController::GetInstance().GetWindow(), GLFW_MOUSE_BUTTON_LEFT);
				if (leftState == GLFW_PRESS)
				{
					m_fighterScale.x += deltaScaleX * 0.00001f;
					m_fighterScale.y += deltaScaleY * 0.00001f;

				}
				int middleState = glfwGetMouseButton(WindowController::GetInstance().GetWindow(), GLFW_MOUSE_BUTTON_MIDDLE);
				if (middleState == GLFW_PRESS)
				{
					m_fighterScale.z += deltaScaleY * 0.00001f;

				}
				lastX = mouseX;
				lastY = mouseY;
				fighter.SetScale(m_fighterScale);
			}
			if (OpenGL::ToolWindow::resetTransform_Btn)
			{
				m_fighterRotate = { -45.0f, 0.0f, 0.0f };
				fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
				fighter.SetRotation(m_fighterRotate);
				fighter.SetScale({ 0.0008f, 0.0008f, 0.0008f });
				OpenGL::ToolWindow::resetTransform_Btn = false;
			}

			fighter.Render(m_camera.GetProjection() * m_camera.GetView());
		}

		else if (OpenGL::ToolWindow::waterScene_Channel)
		{

		}
		else if (OpenGL::ToolWindow::spaceScene_Channel)
		{
			m_camera.Rotate();
			glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
			skybox.Render(m_camera.GetProjection() * view);
		}
		//m_postProcessor.End();
		fpsFont.RenderText(fpsS, 100, 100, 0.2f, { 1.0, 1.0, 0.0 });
		mousePosition = "Mouse Pos: " + to_string((int)xPos) + "	" + to_string((int)yPos);
		f.RenderText(mousePosition, 100, 130, 0.2f, { 1.0, 1.0, 0.0 });

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed (a non-zero value means the window is closed)

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
	f.Cleanup();
	m_postProcessor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderPost.Cleanup();
#pragma endregion Cleanup
}