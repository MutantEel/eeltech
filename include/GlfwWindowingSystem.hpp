//
//  GlfwWindowingSystem.h
//  EelTech
//
//  Created by Sean on 7/27/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#ifndef EelTech_GlfwWindowingSystem_h
#define EelTech_GlfwWindowingSystem_h

#include <Artemis/EntityProcessingSystem.hpp>
#include <Artemis/ComponentMapper.hpp>
#include <GLEW/GLEW.h>
#include <GLFW/glfw3.h>
#include <list>


namespace eeltech
{
	
	class WindowingComponent : public artemis::Component
	{
		public:
		
			WindowingComponent(std::string title, float width, float height, int fsaa = 0, bool fullscreen = false, bool cursorVisible = true);
		
			bool isOpen;
			std::string title;
			float width;
			float height;
			int fsaa;
			bool fullscreen;
			bool cursorVisible;
			GLFWwindow* handle;
			bool closeRequested;
			bool shouldClose;
	};
	
	
	class DisplayMode
	{
		public:
			int width;
			int height;
			int redBits;
			int greenBits;
			int blueBits;
	};
	
	
  class GlfwWindowingSystem : public artemis::EntityProcessingSystem
	{
		public:
			GlfwWindowingSystem();
			virtual ~GlfwWindowingSystem();
		
			virtual void initialize();
		
			std::list<DisplayMode> displayModes();
    
			DisplayMode desktopDisplayMode();

		protected:
			artemis::ComponentMapper<WindowingComponent> windowingMapper;
		
			virtual void processEntity(artemis::Entity& e);
			virtual void begin();
		
			virtual void removed(artemis::Entity& e);
			virtual void added(artemis::Entity& e);
		
			void updateTitle(artemis::Entity& e);
			
			bool show(artemis::Entity& e);
		
			void swapBuffers(artemis::Entity& e);
		
			void makeActiveContext(artemis::Entity& e);
			
			void resize(artemis::Entity& e);
			
			void updateCursorVisiblity(artemis::Entity& e);

		
			static void closeRequested(GLFWwindow* handle);
		
			bool glewInitialized;
	};
	
	
}

#endif
