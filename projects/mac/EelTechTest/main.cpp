//
//  main.m
//  EelTechTest
//
//  Created by Sean on 7/27/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/systems/GlfwWindowingSystem.hpp>
#include <EelTech/systems/GlfwInputSystem.hpp>
#include <EelTech/systems/OALSoundSystem.hpp>
#include <Artemis/ComponentRegistry.hpp>
#include <Artemis/SystemManager.hpp>
#include <Artemis/Entity.hpp>
#include <EelTech/core/FileSystem.hpp>
#include <EelTech/core/File.hpp>

int main(int argc, char *argv[])
{
	//register serializable components
	artemis::ComponentRegistry::registerComponent<eeltech::WindowingComponent>();
	artemis::ComponentRegistry::registerComponent<eeltech::InputComponent>();
	
	//setup filesystem
	eeltech::FileSystem::init(argv[0]);
	eeltech::FileSystem::mount("./", "/", true);
	
	//setup component systems
	artemis::World world;
	artemis::SystemManager* sm = world.getSystemManager();
	
	eeltech::GlfwWindowingSystem* winSys = (eeltech::GlfwWindowingSystem*)sm->setSystem(new eeltech::GlfwWindowingSystem());
	eeltech::GlfwInputSystem* inputSys = (eeltech::GlfwInputSystem*)sm->setSystem(new eeltech::GlfwInputSystem());
	eeltech::OALSoundSystem* soundSys = (eeltech::OALSoundSystem*)sm->setSystem(new eeltech::OALSoundSystem());
	artemis::EntityManager* em = world.getEntityManager();
	
	sm->initializeAll();
	
	
	//load data
	std::string testData = eeltech::File::loadString("testData.json");
	
	if(testData.empty())
	{
		std::cout << "failed to load testData.json" << std::endl;
		return 1;
	}
	
	Json::Value root;
	Json::Reader reader;
	reader.parse(testData, root);
	
	em->deserialize(root);
	
	//get the main window that was loaded from data
	artemis::Entity& e = world.getTagManager()->getEntity("Main Window");
	eeltech::InputComponent* inputComp = dynamic_cast<eeltech::InputComponent*>(e.getComponent<eeltech::InputComponent>());
	
	
	//do main loop
	while(true)
	{
		world.loopStart();
		world.setDelta(0.0016f);
		
		inputSys->process();
		winSys->process();
		
		
		if(inputComp && !inputComp->pressedKeys.isEmpty())
		{
			for(int i = 0; i < inputComp->pressedKeys.getCount(); i++)
			{
				std::cout << "pressed key " << (char)inputComp->pressedKeys.get(i) << std::endl;
			}
		}
	}
	
	return 0;
}
