//
//  GlfwWindowingSystem.cpp
//  EelTech
//
//  Created by Sean on 7/27/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/systems/GlfwWindowingSystem.hpp>
#include <Artemis/Entity.hpp>

namespace eeltech
{
	WindowingComponent:: WindowingComponent(std::string title, float width, float height, int fsaa, bool fullscreen, bool cursorVisible) : title(title), width(width), height(height), fsaa(fsaa), fullscreen(fullscreen), cursorVisible(cursorVisible), handle(NULL), isOpen(false), closeRequested(false), shouldClose(false)
	{
	}
	
	
	
	GlfwWindowingSystem::GlfwWindowingSystem() : glewInitialized(false)
	{
		addComponentType<WindowingComponent>();
	}
	
	
	GlfwWindowingSystem::~GlfwWindowingSystem()
	{
		glfwTerminate();
	}
	
	
	void GlfwWindowingSystem::initialize()
	{
		windowingMapper.init(*world);
		
		int init = glfwInit();
		if (!init)
		{
			std::cout << "Unable to Windowing system: " << init << std::endl;
			return;
		}
	}

	
	std::list<DisplayMode> GlfwWindowingSystem::displayModes()
	{
		int foundModes = 0;
		//MARK: FIXME_FEATURE later on we should be able to get display modes for any monitor
		const GLFWvidmode* results = glfwGetVideoModes(glfwGetPrimaryMonitor(), &foundModes);
		
		std::list<DisplayMode> modes;
		
		for(int i = 0; i < foundModes; i++)
		{
			DisplayMode dm;
			dm.width = results[i].width;
			dm.height = results[i].height;
			dm.redBits = results[i].redBits;
			dm.greenBits = results[i].greenBits;
			dm.blueBits = results[i].blueBits;
			
			modes.push_back(dm);
		}
		
		return modes;
	}
	
	
	DisplayMode GlfwWindowingSystem::desktopDisplayMode()
	{
		//MARK: FIXME_FEATURE later on we should be able to get display modes for any monitor
		const GLFWvidmode* result = glfwGetVideoMode(glfwGetPrimaryMonitor());
		
		DisplayMode dm;
		dm.width = result->width;
		dm.height = result->height;
		dm.redBits = result->redBits;
		dm.greenBits = result->greenBits;
		dm.blueBits = result->blueBits;
		
		return dm;
	}
	
	
	void GlfwWindowingSystem::processEntity(artemis::Entity& e)
	{
		if(windowingMapper.get(e)->shouldClose)
		{
			world->getEntityManager()->removeComponent(e, artemis::ComponentTypeManager::getTypeFor<WindowingComponent>());
		}
	}
	
	
	void GlfwWindowingSystem::begin()
	{
		glfwPollEvents();
	}
	
	
	void GlfwWindowingSystem::removed(artemis::Entity& e)
	{
		WindowingComponent* comp = windowingMapper.get(e);
		
		if(comp->isOpen && comp->handle)
		{
			glfwDestroyWindow(comp->handle);
		}
	}
	
	void GlfwWindowingSystem::added(artemis::Entity& e)
	{		
		if(show(e))
		{
			makeActiveContext(e);
			updateCursorVisiblity(e);
		}
	}
	
	
	
	void GlfwWindowingSystem::updateTitle(artemis::Entity& e)
	{
		glfwSetWindowTitle(windowingMapper.get(e)->handle, windowingMapper.get(e)->title.c_str());
	}
	
	
	bool GlfwWindowingSystem::show(artemis::Entity& e)
	{
		GLFWmonitor* monitor = NULL;
	
		WindowingComponent* comp = windowingMapper.get(e);
		
		if(comp->fullscreen)
		{
			monitor = glfwGetPrimaryMonitor();
		}
		
		if(comp->fsaa)
		{
			glfwWindowHint(GLFW_SAMPLES, comp->fsaa);
		}
		
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		
		comp->handle = glfwCreateWindow(comp->width, comp->height, comp->title.c_str(), monitor, NULL);
    
		if(!comp->handle)
		{
			std::cout << "Error: couldn't open window" << std::endl;
			return false;
		}
		
		glfwSetWindowUserPointer(comp->handle, &e);
		glfwSetWindowCloseCallback(comp->handle, &GlfwWindowingSystem::closeRequested);
		
		glfwSwapInterval(1);

		if(!glewInitialized)
		{
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			
			if(GLEW_OK != err)
			{
				std::cout << "Error: " << glewGetErrorString(err) << std::endl;
				return false;
			}
			
			if(!GLEW_VERSION_3_2)
			{
				std::cout << "Error: Your video card does not support OpenGL 3.2." << std::endl;
				return false;
			}
			
			// clear glErrors from glew init (known issue with glew)
			glGetError();
		}
		
		std::cout << "Using OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		
		comp->isOpen = true;
		
		return true;
	}
	
	
	void GlfwWindowingSystem::swapBuffers(artemis::Entity& e)
	{
		glfwSwapBuffers(windowingMapper.get(e)->handle);
	}
	
	
	void GlfwWindowingSystem::makeActiveContext(artemis::Entity& e)
	{
		glfwMakeContextCurrent(windowingMapper.get(e)->handle);
	}
	
	
	void GlfwWindowingSystem::resize(artemis::Entity& e)
	{
		WindowingComponent* comp = windowingMapper.get(e);
		
		if(!comp->handle)
		{
			return;
		}
		
		// Protect against a divide by zero
		if(comp->height == 0)
		{
      comp->height = 1;
		}
				
		glfwSetWindowSize(comp->handle, comp->width, comp->height);
	}
	
	
	void GlfwWindowingSystem::updateCursorVisiblity(artemis::Entity& e)
	{
		WindowingComponent* comp = windowingMapper.get(e);
		
		if(!comp->handle)
		{
			return;
		}
		
		glfwSetInputMode(comp->handle, GLFW_CURSOR, comp->cursorVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
	}

	
	void GlfwWindowingSystem::closeRequested(GLFWwindow* handle)
	{
		WindowingComponent* comp = WindowingComponent::getInputFromHandle<WindowingComponent>(handle);
		if(!comp)
		{
			return;
		}
		
		comp->closeRequested = true;
	}
}
