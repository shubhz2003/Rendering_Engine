#include "Camera.h"

Camera::Camera()
{
	m_projection = { };
	m_view = { };
}

Camera::Camera(Resolution _screenResolution)
{
	// Projection matrix : 45radians Field of View, Variable aspect ratio, display range : 0.1 unit <-> 100units
	m_projection = glm::perspective(glm::radians(45.0f),
		(float)_screenResolution.m_width /
		(float)_screenResolution.m_height,
		0.1f,		// Near Plane
		1000.0f);	// Far Plane
	// Or for an ortho Camera:
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world Coordinates

	// Camera Matrix
	m_view = glm::lookAt(
		glm::vec3(2, 2, 2), // Camera is at (2, 2, 2), in world space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0, -1, 0 to look upside-down
	);
}

Camera::~Camera()
{
}
