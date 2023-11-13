#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

// Include standard headers
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

// Windows specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

// Open GL/Helper headers
#include <GL/glew.h> // Include GLEW
#include <GLFW/glfw3.h> // Include GLFW
#include <glm/glm.hpp> // Include GLM
#include <glm/ext.hpp> // Open Experimental to_string
#include <glm/gtx/string_cast.hpp> // Override cast for the experimental to_string
#include <glm/gtc/matrix_transform.hpp> // View / Projection

// Font includes
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Singleton.h"
#include "Resolution.h"

#define GLM_ENABLE_EXPERIMENTAL

using namespace std;

#endif // !STANDARD_INCLUDES_H