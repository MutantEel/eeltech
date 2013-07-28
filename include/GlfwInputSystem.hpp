//
//  GlfwInputSystem.h
//  EelTech
//
//  Created by Sean on 7/28/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#ifndef EelTech_GlfwInputSystem_h
#define EelTech_GlfwInputSystem_h

#include <Artemis/EntityProcessingSystem.hpp>
#include <Artemis/ComponentMapper.hpp>
#include <EelTech/GlfwWindowingSystem.hpp>
#include <GLEW/GLEW.h>
#include <GLFW/glfw3.h>
#include <list>
#include <map>


namespace eeltech
{
	namespace ButtonState
	{
		enum State
		{
			ButtonUp,
			ButtonPressed,
			ButtonHeld,
			ButtonReleased,
		};
	}
	
	
	class InputComponent : public artemis::Component
	{
		public:
		
			int mousePosition[2];
			int mouseWheelPosition[2];
		
			artemis::Bag<int> heldMouseButtons;
			artemis::Bag<int> pressedMouseButtons;
			artemis::Bag<int> releasedMouseButtons;
		
			artemis::Bag<int> heldKeys;
			artemis::Bag<int> pressedKeys;
			artemis::Bag<int> releasedKeys;
		
			//MARK: FEATURE add support for gamepads
	};
	
	
  class GlfwInputSystem : public artemis::EntityProcessingSystem
	{
		public:
			GlfwInputSystem();
			virtual ~GlfwInputSystem();
			
			virtual void initialize();
			
		protected:
			artemis::ComponentMapper<InputComponent> inputMapper;
			artemis::ComponentMapper<WindowingComponent> windowingMapper;
			
			virtual void processEntity(artemis::Entity& e);
			virtual void added(artemis::Entity& e);
		
			static void MouseButtonEventCallback(GLFWwindow* windowHandle, int button, int action, int modifierKeys);
			static void MousePositionEventCallback(GLFWwindow* windowHandle, double x, double y);
			static void MouseWheelPositionEventCallback(GLFWwindow* windowHandle, double xPos, double yPos);
			static void KeyEventCallback(GLFWwindow* windowHandle, int key, int scancode, int action, int mod);
	};
	
	
}

#endif
