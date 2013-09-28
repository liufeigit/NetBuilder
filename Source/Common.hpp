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
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>

// STL
#include <iostream>
#include <string>
#include <vector>

// NetBuilder
#include "Renderer\Renderer.hpp"

#include "NetBuilder.hpp"


int main() {

	Designer::cNetBuilder *NetBuilder = new Designer::cNetBuilder();

	NetBuilder->Run();

}