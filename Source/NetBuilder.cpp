/**
*    Net Builder
*                      
* Copyright (c) 2013 
*
*              Strobs Canardly Systems
*
*                                  ScS
**/

#include "Common.hpp"

namespace Designer {

	cNetBuilder::cNetBuilder() {

		mRenderer = new Renderer::cOpenGl();
	}

	cNetBuilder::~cNetBuilder() {

		delete mRenderer;
	}

	void cNetBuilder::Run() {

	}
}
