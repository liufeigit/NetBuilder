/**
*    Net Builder
*                      
* Copyright (c) 2013 
*
*              Strobs Canardly Systems
*
*                                  ScS
**/

namespace Designer {

	class cNetBuilder {

	private:
		Renderer::cOpenGl	*mRenderer;


	public:
				 cNetBuilder();
		virtual ~cNetBuilder();

		void	 Run();
	};

}
