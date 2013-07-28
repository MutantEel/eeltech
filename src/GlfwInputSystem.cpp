//
//  GlfwInputSystem.c
//  EelTech
//
//  Created by Sean on 7/28/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/GlfwInputSystem.hpp>
#include <Artemis/ImmutableBag.hpp>

namespace eeltech
{
	
	GlfwInputSystem::GlfwInputSystem()
	{
		addComponentType<InputComponent>();
		addComponentType<WindowingComponent>();
	}

	
	GlfwInputSystem::~GlfwInputSystem()
	{
		
	}
	
	
	void GlfwInputSystem::initialize()
	{
		inputMapper.init(*world);
		windowingMapper.init(*world);
	}
	
	
	void GlfwInputSystem::processEntity(artemis::Entity& e)
	{
		InputComponent* comp = inputMapper.get(e);
		
		//update mouse buttons
		if(!comp->pressedMouseButtons.isEmpty())
		{
			//move pressed buttons to held state
			comp->heldMouseButtons += comp->pressedMouseButtons;
			comp->pressedMouseButtons.clear();
		}
		
		//remove released buttons
		comp->releasedMouseButtons.clear();
		
		
		//update keyboard keys
		if(!comp->pressedKeys.isEmpty())
		{
			//move pressed keys to held state
			comp->heldKeys += comp->pressedKeys;
			comp->pressedKeys.clear();
		}
		
		//remove released keys
		comp->releasedKeys.clear();
	}
		
	
	void GlfwInputSystem::added(artemis::Entity& e)
	{
		GLFWwindow* handle = windowingMapper.get(e)->handle;
		
		if(handle)
		{
			glfwSetMouseButtonCallback(handle, &GlfwInputSystem::MouseButtonEventCallback);
			glfwSetCursorPosCallback(handle, &GlfwInputSystem::MousePositionEventCallback);
			glfwSetScrollCallback(handle, &GlfwInputSystem::MouseWheelPositionEventCallback);
			glfwSetKeyCallback(handle, &GlfwInputSystem::KeyEventCallback);
		}
		else
		{
			std::cout << "Failed to initialize input component, window handle is invalid" << std::endl;
		}
	}

	
	void GlfwInputSystem::MouseButtonEventCallback(GLFWwindow* windowHandle, int button, int action, int modifierKeys)
	{
		InputComponent* comp = WindowingComponent::getInputFromHandle<InputComponent>(windowHandle);
		if(!comp)
		{
			return;
		}
		
		if(action == GLFW_PRESS)
		{
			comp->pressedMouseButtons.add(button);
		}
		else if(action == GLFW_RELEASE)
		{
			comp->pressedMouseButtons.remove(button);
			comp->heldMouseButtons.remove(button);
			comp->releasedMouseButtons.add(button);
		}
	}
	
	
	void GlfwInputSystem::MousePositionEventCallback(GLFWwindow* windowHandle, double x, double y)
	{
		InputComponent* comp = WindowingComponent::getInputFromHandle<InputComponent>(windowHandle);
		if(!comp)
		{
			return;
		}
		
		comp->mousePosition[0] = (int)x;
		comp->mousePosition[1] = (int)y;
	}
	
	
	void GlfwInputSystem::MouseWheelPositionEventCallback(GLFWwindow* windowHandle, double x, double y)
	{
		InputComponent* comp = WindowingComponent::getInputFromHandle<InputComponent>(windowHandle);
		if(!comp)
		{
			return;
		}
		
		comp->mousePosition[0] = (int)x;
		comp->mousePosition[1] = (int)y;
	}
	
	
	void GlfwInputSystem::KeyEventCallback(GLFWwindow* windowHandle, int key, int scancode, int action, int mod)
	{
		InputComponent* comp = WindowingComponent::getInputFromHandle<InputComponent>(windowHandle);
		if(!comp)
		{
			return;
		}
		
		if(action == GLFW_PRESS)
		{
			comp->pressedKeys.add(key);
		}
		else if(action == GLFW_RELEASE)
		{
			comp->pressedKeys.remove(key);
			comp->heldKeys.remove(key);
			comp->releasedKeys.add(key);
		}
	}
}

