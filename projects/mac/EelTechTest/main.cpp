//
//  main.m
//  EelTechTest
//
//  Created by Sean on 7/27/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/GlfwWindowingSystem.hpp>
#include <Artemis/SystemManager.hpp>
#include <Artemis/Entity.hpp>

int main(int argc, char *argv[])
{
	artemis::World world;
	artemis::SystemManager* sm = world.getSystemManager();
	
	eeltech::GlfwWindowingSystem* winsys = (eeltech::GlfwWindowingSystem*)sm->setSystem(new eeltech::GlfwWindowingSystem());
	artemis::EntityManager* em = world.getEntityManager();
	
	sm->initializeAll();
	
	artemis::Entity& window = em->create();
	
	window.addComponent(new eeltech::WindowingComponent("Eel Tech Test", 800, 600));
	window.refresh();
	
	artemis::Entity& window2 = em->create();
	
	window2.addComponent(new eeltech::WindowingComponent("Eel Tech Test 2", 640, 480));
	window2.refresh();
	
	while(true)
	{
		world.loopStart();
		world.setDelta(0.0016f);
		winsys->process();
	}
	
	return 0;
}
