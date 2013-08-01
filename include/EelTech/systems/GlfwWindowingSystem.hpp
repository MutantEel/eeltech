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
#include <Artemis/Entity.hpp>
#include <GLEW/GLEW.h>
#include <GLFW/glfw3.h>
#include <list>


namespace eeltech
{
	
	class WindowingComponent : public artemis::Component
	{
		public:
		
			WindowingComponent();
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
		
			ARTEMIS_SERIALIZATION_SETUP(WindowingComponent)
		
			ARTEMIS_SERIALIZE_START
			ARTEMIS_SERIALIZE(title)
			ARTEMIS_SERIALIZE(width)
			ARTEMIS_SERIALIZE(height)
			ARTEMIS_SERIALIZE(fsaa)
			ARTEMIS_SERIALIZE(fullscreen)
			ARTEMIS_SERIALIZE(cursorVisible)
			ARTEMIS_SERIALIZE_END
		
			ARTEMIS_DESERIALIZE_START
			ARTEMIS_DESERIALIZE(title, String, "untitled")
			ARTEMIS_DESERIALIZE(width, Int, 800)
			ARTEMIS_DESERIALIZE(height, Int, 600)
			ARTEMIS_DESERIALIZE(fsaa, Int, 0)
			ARTEMIS_DESERIALIZE(fullscreen, Bool, false)
			ARTEMIS_DESERIALIZE(cursorVisible, Bool, false)
			ARTEMIS_DESERIALIZE_END
		
			template <typename c>
			static c* getInputFromHandle(GLFWwindow* handle)
			{
				if(!handle)
				{
					return NULL;
				}
				
				void* userPtr = glfwGetWindowUserPointer(handle);
				if(!userPtr)
				{
					return NULL;
				}
				
				artemis::Entity* ent = static_cast<artemis::Entity*>(userPtr);
				
				
				if(ent)
				{
					c* comp = dynamic_cast<c*>(ent->getComponent<c>());
					
					if(comp)
					{
						return comp;
					}
				}
				
				return NULL;
			}
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
