//
//  main.m
//  EelTechTest
//
//  Created by Sean on 7/27/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/GlfwWindowingSystem.hpp>
#include <EelTech/GlfwInputSystem.hpp>
#include <Artemis/SystemManager.hpp>
#include <Artemis/Entity.hpp>

int main(int argc, char *argv[])
{
	artemis::World world;
	artemis::SystemManager* sm = world.getSystemManager();
	
	eeltech::GlfwWindowingSystem* winSys = (eeltech::GlfwWindowingSystem*)sm->setSystem(new eeltech::GlfwWindowingSystem());
	eeltech::GlfwInputSystem* inputSys = (eeltech::GlfwInputSystem*)sm->setSystem(new eeltech::GlfwInputSystem());
	artemis::EntityManager* em = world.getEntityManager();
	
	sm->initializeAll();
	
	artemis::Entity& window = em->create();
	
	window.addComponent(new eeltech::WindowingComponent("Eel Tech Test", 800, 600));
	window.addComponent(new eeltech::InputComponent());
	window.refresh();
	
	artemis::Entity& window2 = em->create();
	
	window2.addComponent(new eeltech::WindowingComponent("Eel Tech Test 2", 640, 480));
	window.addComponent(new eeltech::InputComponent());
	window2.refresh();
	
	while(true)
	{
		world.loopStart();
		world.setDelta(0.0016f);
		
		inputSys->process();
		winSys->process();
		
		
		
		eeltech::InputComponent* input = static_cast<eeltech::InputComponent*>(window.getComponent<eeltech::InputComponent>());
		
		if(input && !input->pressedKeys.isEmpty())
		{
			for(int i = 0; i < input->pressedKeys.getCount(); i++)
			{
				std::cout << "pressed key " << (char)input->pressedKeys.get(i) << std::endl;
			}
		}
	}
	
	return 0;
}
