//
//  OALSoundSystem.cpp
//  EelTech
//
//  Created by Sean on 8/1/13.
//  Copyright (c) 2013 Mutant Eel. All rights reserved.
//

#include <EelTech/systems/OALSoundSystem.hpp>


namespace eeltech
{
	
	
OALSoundSystem::OALSoundSystem() : device(NULL), context(NULL)
{
	
}


OALSoundSystem::~OALSoundSystem()
{
	if(context)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		context = NULL;
	}
	
	if(device)
	{
		alcCloseDevice(device);
		device = NULL;
	}
}


void OALSoundSystem::initialize()
{
	device = alcOpenDevice(NULL);
	
	if (!device)
	{
#ifdef DEBUG
		std::cout << "Could not open default OpenAL device." << std::endl;
#endif
		return;
	}
	
	context = alcCreateContext(device, NULL);
	
	if (!context)
	{
#ifdef DEBUG
		std::cout << "Failed to create OpenAL context for default device." << std::endl;
#endif
		return;
	}
	
	if (!alcMakeContextCurrent(context))
	{
#ifdef DEBUG
		std::cout << "Failed to set current OpenAL context." << std::endl;
#endif
		return;
	}
	
	if(alGetError() != 0)
	{
#ifdef DEBUG
		std::cout << "Error initializing audio" << std::endl;
#endif
		return;
	}

}
	

void OALSoundSystem::processEntity(artemis::Entity& e)
{
		
}
	
	
void OALSoundSystem::added(artemis::Entity& e)
{
		
}


}
