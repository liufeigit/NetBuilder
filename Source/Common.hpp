/**
*    Net Builder
*                      
* Copyright (c) 2013 
*
*              Strobs Canardly Systems
*
*                                  ScS
**/

// OpenGL
#define GL3_PROTOTYPES 1
#include <gl.h>
#include "GL/glew.h"
#include "GL/wglew.h"
#pragma comment(lib, "glew32.lib")

// STL
#include <iostream>
#include <string>
#include <vector>

// NetBuilder
#include "Renderer\Renderer.hpp"

#include "NetBuilder.hpp"


int main() {

	cNetBuilder *NetBuilder = new cNetBuilder();

	NetBuilder->Run();

}